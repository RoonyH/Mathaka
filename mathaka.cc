#include <nan.h>

using namespace v8;


class MemCounter {
    int count;  // keeps track of allocated memory in bytes
                // TODO: add more variables to track all v8 spaces seperately

  public:
    MemCounter() {count = 0;}

    void add_to_count (int);
    void reset_count ();
    int get_count () {return count;}
};

void MemCounter::add_to_count (int new_mem) {
    count = count + new_mem;
}

void MemCounter::reset_count () {
    count = 0;
}

MemCounter counter; // global, so the callback can access it


void MemAllocateCallback (ObjectSpace objs, AllocationAction action,
                          int size) {

    if(action==kAllocationActionFree){
        size = size * (-1);
    }

    counter.add_to_count(size);
}


NAN_METHOD(InitMemCounter) {
    counter.reset_count();

    V8::AddMemoryAllocationCallback(&MemAllocateCallback, kObjectSpaceAll,
                                    kAllocationActionAll);
    NanReturnUndefined();
}


NAN_METHOD(Memstate) {
  NanScope();
  Local<Number> count = NanNew<Number>(counter.get_count());

  counter.reset_count(); // reset after each call

  NanReturnValue(count);
}


void Init(Handle<Object> exports) {
  exports->Set(NanNew("init"),
               NanNew<FunctionTemplate>(InitMemCounter)->GetFunction());

  exports->Set(NanNew("memstate"), 
               NanNew<FunctionTemplate>(Memstate)->GetFunction());
}


NODE_MODULE(mathaka, Init)
