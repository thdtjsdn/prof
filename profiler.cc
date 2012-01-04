#include <v8.h>
#include <v8-profiler.h>
#include <node.h>

using namespace v8;
using namespace node;

static Handle<Value> FindSnapshot(const Arguments& args) {
  HandleScope scope;

  return scope.Close(String::New(""));
}

static Handle<Value> GetSnapshot(const Arguments& args) {
  HandleScope scope;

  return scope.Close(String::New(""));
}

static Handle<Value> GetSnapshotsCount(const Arguments& args) {
  HandleScope scope;

  return scope.Close(Integer::New(HeapProfiler::GetSnapshotsCount()));
}

static Handle<Value> TakeSnapshot(const Arguments& args) {
  HandleScope scope;

  return scope.Close(String::New(""));
}

extern "C" void init(Handle<Object> target) {
  HandleScope scope;

  NODE_SET_METHOD(target, "findSnapshot",   FindSnapshot);
  NODE_SET_METHOD(target, "getSnapshot",    GetSnapshot);
  NODE_SET_METHOD(target, "snapshotCount",  GetSnapshotsCount);
  NODE_SET_METHOD(target, "takeSnapshot",   TakeSnapshot);
}
