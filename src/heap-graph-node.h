#include <v8.h>
#include <v8-profiler.h>

using namespace v8;

class GraphNode {
  public:
    static Handle<Value> New(const HeapGraphNode* node);

  private:
   static Handle<Value> GetChild(const Arguments& args);
   static Handle<Value> GetRetainedSize(const Arguments& args);
   static Handle<Value> GetRetainer(const Arguments& args);
   static Handle<Value> GetApproximateRetainedSize(Local<String> property, const AccessorInfo& info);
   static Handle<Value> GetChildrenCount(Local<String> property, const AccessorInfo& info);
   static Handle<Value> GetDominatorNode(Local<String> property, const AccessorInfo& info);
   static Handle<Value> GetId(Local<String> property, const AccessorInfo& info);
   static Handle<Value> GetName(Local<String> property, const AccessorInfo& info);
   static Handle<Value> GetPtr(Local<String> property, const AccessorInfo& info);
   static Handle<Value> GetRetainersCount(Local<String> property, const AccessorInfo& info);
   static Handle<Value> GetSelfSize(Local<String> property, const AccessorInfo& info);
   static Handle<Value> GetType(Local<String> property, const AccessorInfo& info);
   static Persistent<ObjectTemplate> node_template_;
   static void Initialize();
};
