#include <v8.h>
#include <v8-profiler.h>

using namespace v8;

class Snapshot {
  public:
    static Handle<Value> New(const HeapSnapshot* snapshot);

  private:
    static Handle<Value> CompareWith(const Arguments& args);
    static Handle<Value> GetRoot(Local<String> property, const AccessorInfo& info);
    static Handle<Value> GetTitle(Local<String> property, const AccessorInfo& info);
    static Handle<Value> GetType(Local<String> property, const AccessorInfo& info);
    static Handle<Value> GetUid(Local<String> property, const AccessorInfo& info);
    static Persistent<ObjectTemplate> snapshot_template_;
    static void Initialize();
};
