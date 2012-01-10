#include <v8.h>
#include <v8-profiler.h>

using namespace v8;

class GraphEdge {
 public:
   static Handle<Value> New(const HeapGraphEdge* edge);

 private:
   static Handle<Value> GetFromNode(Local<String> property, const AccessorInfo& info);
   static Handle<Value> GetName(Local<String> property, const AccessorInfo& info);
   static Handle<Value> GetToNode(Local<String> property, const AccessorInfo& info);
   static Handle<Value> GetType(Local<String> property, const AccessorInfo& info);
   static Persistent<ObjectTemplate> edge_template_;
   static void Initialize();
};
