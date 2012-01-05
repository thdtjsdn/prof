#include <unistd.h>
#include "snapshot.h"
#include "graph_node.h"

class FileOutputStream : public OutputStream {
  private:
    FILE *out;

  public:
    FileOutputStream(FILE *out) {
      this->out = out;
    }

    void EndOfStream() {
      fflush(out);
    }

    OutputStream::WriteResult WriteAsciiChunk(char *data, int size) {
      int rv;

      rv = write(fileno(out), data, size);

      if (rv != size)
        return OutputStream::kAbort;

      return OutputStream::kContinue;
    }
};

Persistent<ObjectTemplate> Snapshot::snapshot_template_;

void Snapshot::Initialize() {
  snapshot_template_ = Persistent<ObjectTemplate>::New(ObjectTemplate::New());

  snapshot_template_->Set(String::New("delete"), FunctionTemplate::New(Snapshot::Delete));
  snapshot_template_->Set(String::New("getNode"), FunctionTemplate::New(Snapshot::GetNode));
  snapshot_template_->Set(String::New("getNodeById"), FunctionTemplate::New(Snapshot::GetNodeById));
  snapshot_template_->Set(String::New("serialize"), FunctionTemplate::New(Snapshot::Serialize));
  snapshot_template_->SetAccessor(String::New("nodes"), Snapshot::GetNodesCount);
  snapshot_template_->SetAccessor(String::New("root"), Snapshot::GetRoot);
  snapshot_template_->SetAccessor(String::New("title"), Snapshot::GetTitle);
  snapshot_template_->SetAccessor(String::New("type"), Snapshot::GetType);
  snapshot_template_->SetAccessor(String::New("uid"), Snapshot::GetUid);
  snapshot_template_->SetInternalFieldCount(1);
}

Handle<Value> Snapshot::Delete(const Arguments& args) {
  HandleScope scope;
  Handle<Object> self = args.This();

  void* ptr = self->GetPointerFromInternalField(0);
  static_cast<HeapSnapshot*>(ptr)->Delete();
}

Handle<Value> Snapshot::GetNode(const Arguments& args) {
  HandleScope scope;
  Handle<Object> self = args.This();

  if (args.Length() < 1) {
    return ThrowException(Exception::Error(String::New("No index specified")));
  } else if (!args[0]->IsInt32()) {
    return ThrowException(Exception::TypeError(String::New("Argument must be an integer")));
  }

  int32_t index = args[0]->Int32Value();
  void* ptr = self->GetPointerFromInternalField(0);
  const HeapGraphNode* node = static_cast<HeapSnapshot*>(ptr)->GetNode(index);

  return scope.Close(GraphNode::New(node));
}

Handle<Value> Snapshot::GetNodeById(const Arguments& args) {
  HandleScope scope;
  Handle<Object> self = args.This();

  if (args.Length() < 1) {
    return ThrowException(Exception::Error(String::New("No id specified")));
  } else if (!args[0]->IsInt32()) {
    return ThrowException(Exception::TypeError(String::New("Argument must be an integer")));
  }

  int32_t id = args[0]->Int32Value();
  void* ptr = self->GetPointerFromInternalField(0);
  const HeapGraphNode* node = static_cast<HeapSnapshot*>(ptr)->GetNodeById(id);

  return scope.Close(GraphNode::New(node));
}

Handle<Value> Snapshot::Serialize(const Arguments& args) {
  HandleScope scope;
  Handle<Object> self = args.This();
  bool customFile = args[0]->IsString();
  FILE *file = stdout;

  if (customFile) {
    String::AsciiValue fileName(args[0]);
    file = fopen(*fileName, "w");
  }

  FileOutputStream *stream = new FileOutputStream(file);
  void* ptr = self->GetPointerFromInternalField(0);
  static_cast<HeapSnapshot*>(ptr)->Serialize(stream, HeapSnapshot::kJSON);

  if (customFile) {
    fclose(file);
  }
}

Handle<Value> Snapshot::GetNodesCount(Local<String> property, const AccessorInfo& info) {
  HandleScope scope;
  Local<Object> self = info.Holder();

  void* ptr = self->GetPointerFromInternalField(0);

  return scope.Close(Integer::New(static_cast<HeapSnapshot*>(ptr)->GetNodesCount()));
}

Handle<Value> Snapshot::GetRoot(Local<String> property, const AccessorInfo& info) {
  HandleScope scope;
  Local<Object> self = info.Holder();

  void* ptr = self->GetPointerFromInternalField(0);
  const HeapGraphNode* node = static_cast<HeapSnapshot*>(ptr)->GetRoot();

  return scope.Close(GraphNode::New(node));
}

Handle<Value> Snapshot::GetTitle(Local<String> property, const AccessorInfo& info) {
  HandleScope scope;
  Local<Object> self = info.Holder();

  void* ptr = self->GetPointerFromInternalField(0);
  Handle<String> title = static_cast<HeapSnapshot*>(ptr)->GetTitle();

  return scope.Close(title);
}

Handle<Value> Snapshot::GetType(Local<String> property, const AccessorInfo& info) {
  HandleScope scope;
  Local<Object> self = info.Holder();
  Local<String> t;

  void* ptr = self->GetPointerFromInternalField(0);
  HeapSnapshot::Type type = static_cast<HeapSnapshot*>(ptr)->GetType();

  if (type == HeapSnapshot::kFull) {
    t = String::New("Full");
  } else {
    t = String::New("Unknown");
  }

  return scope.Close(t);
}

Handle<Value> Snapshot::GetUid(Local<String> property, const AccessorInfo& info) {
  HandleScope scope;
  Local<Object> self = info.Holder();

  void* ptr = self->GetPointerFromInternalField(0);
  uint32_t uid = static_cast<HeapSnapshot*>(ptr)->GetUid();

  return scope.Close(Integer::NewFromUnsigned(uid));
}

Handle<Value> Snapshot::New(const HeapSnapshot* snapshot) {
  HandleScope scope;

  if (snapshot_template_.IsEmpty()) {
    Snapshot::Initialize();
  }

  if (!snapshot) {
    return Undefined();
  } else {
    Local<Object> obj = snapshot_template_->NewInstance();
    obj->SetPointerInInternalField(0, const_cast<HeapSnapshot*>(snapshot));

    return scope.Close(obj);
  }
}
