#include "graph_node.h"
#include "graph_edge.h"

using namespace v8;

Persistent<ObjectTemplate> GraphNode::node_template_;

void GraphNode::Initialize() {
  node_template_ = Persistent<ObjectTemplate>::New(ObjectTemplate::New());

  node_template_->Set(String::New("getChild"), FunctionTemplate::New(GraphNode::GetChild));
  node_template_->Set(String::New("getRetainer"), FunctionTemplate::New(GraphNode::GetRetainer));
  node_template_->Set(String::New("getRetainedSize"), FunctionTemplate::New(GraphNode::GetRetainedSize));
  node_template_->SetAccessor(String::New("approximateRetainedSize"), GraphNode::GetApproximateRetainedSize);
  node_template_->SetAccessor(String::New("childrenCount"), GraphNode::GetChildrenCount);
  node_template_->SetAccessor(String::New("dominatorNode"), GraphNode::GetDominatorNode);
  node_template_->SetAccessor(String::New("id"), GraphNode::GetId);
  node_template_->SetAccessor(String::New("name"), GraphNode::GetName);
  node_template_->SetAccessor(String::New("ptr"), GraphNode::GetPtr);
  node_template_->SetAccessor(String::New("retainersCount"), GraphNode::GetRetainersCount);
  node_template_->SetAccessor(String::New("size"), GraphNode::GetSelfSize);
  node_template_->SetAccessor(String::New("type"), GraphNode::GetType);
  node_template_->SetInternalFieldCount(1);
}

Handle<Value> GraphNode::GetChild(const Arguments& args) {
  HandleScope scope;
  Handle<Object> self = args.This();

  if (args.Length() < 1) {
    return ThrowException(Exception::Error(String::New("No index specified")));
  } else if (!args[0]->IsInt32()) {
    return ThrowException(Exception::Error(String::New("Argument must be integer")));
  }

  int32_t index = args[0]->Int32Value();
  void* ptr = self->GetPointerFromInternalField(0);
  const HeapGraphEdge* edge = static_cast<HeapGraphNode*>(ptr)->GetChild(index);

  return scope.Close(GraphEdge::New(edge));
}

Handle<Value> GraphNode::GetRetainer(const Arguments& args) {
  HandleScope scope;
  Handle<Object> self = args.This();

  if (args.Length() < 1) {
    return ThrowException(Exception::Error(String::New("No index specified")));
  } else if (!args[0]->IsInt32()) {
    return ThrowException(Exception::Error(String::New("Argument must be integer")));
  }

  int32_t index = args[0]->Int32Value();
  void* ptr = self->GetPointerFromInternalField(0);
  const HeapGraphEdge* edge = static_cast<HeapGraphNode*>(ptr)->GetRetainer(index);

  return scope.Close(GraphEdge::New(edge));
}

Handle<Value> GraphNode::GetRetainedSize(const Arguments& args) {
  HandleScope scope;
  Handle<Object> self = args.This();

  void* ptr = self->GetPointerFromInternalField(0);
  int32_t size = static_cast<HeapGraphNode*>(ptr)->GetRetainedSize(true);

  return scope.Close(Integer::New(size));
}

Handle<Value> GraphNode::GetApproximateRetainedSize(Local<String> property, const AccessorInfo& info) {
  HandleScope scope;
  Local<Object> self = info.Holder();

  void* ptr = self->GetPointerFromInternalField(0);
  int32_t size = static_cast<HeapGraphNode*>(ptr)->GetRetainedSize(false);

  return scope.Close(Integer::New(size));
}

Handle<Value> GraphNode::GetChildrenCount(Local<String> property, const AccessorInfo& info) {
  HandleScope scope;
  Local<Object> self = info.Holder();

  void* ptr = self->GetPointerFromInternalField(0);
  int32_t count = static_cast<HeapGraphNode*>(ptr)->GetChildrenCount();

  return scope.Close(Integer::New(count));
}

Handle<Value> GraphNode::GetDominatorNode(Local<String> property, const AccessorInfo& info) {
  HandleScope scope;
  Local<Object> self = info.Holder();

  void* ptr = self->GetPointerFromInternalField(0);
  const HeapGraphNode* node = static_cast<HeapGraphNode*>(ptr)->GetDominatorNode();

  return scope.Close(GraphNode::New(node));
}

Handle<Value> GraphNode::GetId(Local<String> property, const AccessorInfo& info) {
  HandleScope scope;
  Local<Object> self = info.Holder();

  void* ptr = self->GetPointerFromInternalField(0);
  uint64_t id = static_cast<HeapGraphNode*>(ptr)->GetId();

  return scope.Close(Integer::NewFromUnsigned(id));
}

Handle<Value> GraphNode::GetName(Local<String> property, const AccessorInfo& info) {
  HandleScope scope;
  Local<Object> self = info.Holder();

  void* ptr = self->GetPointerFromInternalField(0);
  Handle<String> title = static_cast<HeapGraphNode*>(ptr)->GetName();

  return scope.Close(title);
}

Handle<Value> GraphNode::GetPtr(Local<String> property, const AccessorInfo& info) {
  HandleScope scope;
  Local<Object> self = info.Holder();

  void* ptr = self->GetPointerFromInternalField(0);
  uint64_t id = reinterpret_cast<uint64_t>(ptr);

  return scope.Close(Integer::NewFromUnsigned(id));
}

Handle<Value> GraphNode::GetRetainersCount(Local<String> property, const AccessorInfo& info) {
  HandleScope scope;
  Local<Object> self = info.Holder();

  void* ptr = self->GetPointerFromInternalField(0);
  int32_t count = static_cast<HeapGraphNode*>(ptr)->GetRetainersCount();

  return scope.Close(Integer::New(count));
}

Handle<Value> GraphNode::GetSelfSize(Local<String> property, const AccessorInfo& info) {
  HandleScope scope;
  Local<Object> self = info.Holder();

  void* ptr = self->GetPointerFromInternalField(0);
  int32_t count = static_cast<HeapGraphNode*>(ptr)->GetSelfSize();

  return scope.Close(Integer::New(count));
}

Handle<Value> GraphNode::GetType(Local<String> property, const AccessorInfo& info) {
  HandleScope scope;
  Local<Object> self = info.Holder();

  void* ptr = self->GetPointerFromInternalField(0);
  int32_t type = static_cast<int32_t>(static_cast<HeapGraphNode*>(ptr)->GetType());

  Local<String> t;
  switch(type) {
    case 1: //HeapGraphNode::kArray :
    t = String::New("Array");
    break;
    case 2: //HeapGraphNode::kString :
    t = String::New("String");
    break;
    case 3: //HeapGraphNode::kObject :
    t = String::New("Object");
    break;
    case 4: //HeapGraphNode::kCode :
    t = String::New("Code");
    break;
    case 5: //HeapGraphNode::kClosure :
    t = String::New("Closure");
    break;
    case 6: //HeapGraphNode::kRegExp :
    t = String::New("RegExp");
    break;
    case 7: //HeapGraphNode::kHeapNumber :
    t = String::New("HeapNumber");
    break;
    default:
    t = String::New("Hidden");
    break;
  }

  return scope.Close(t);
}

Handle<Value> GraphNode::New(const HeapGraphNode* node) {
  HandleScope scope;

  if (node_template_.IsEmpty()) {
    GraphNode::Initialize();
  }

  if(!node) {
    return Undefined();
  } else {
    Local<Object> obj = node_template_->NewInstance();
    obj->SetPointerInInternalField(0, const_cast<HeapGraphNode*>(node));
    return scope.Close(obj);
  }
}
