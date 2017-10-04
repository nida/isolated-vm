#include "shareable_isolate.h"
#include <v8-platform.h>

using namespace std;
using namespace v8;

namespace ivm {

// Template specializations for IsolateSpecific<FunctionTemplate>
template<>
MaybeLocal<FunctionTemplate> ShareableIsolate::IsolateSpecific<FunctionTemplate>::Deref() const {
  return Deref<FunctionTemplate, decltype(ShareableIsolate::specifics_ft), &ShareableIsolate::specifics_ft>();
}

template<>
void ShareableIsolate::IsolateSpecific<FunctionTemplate>::Reset(Local<FunctionTemplate> handle) {
	Reset<FunctionTemplate, decltype(ShareableIsolate::specifics_ft), &ShareableIsolate::specifics_ft>(handle);
}

// Static variable declarations
thread_local ShareableIsolate* ShareableIsolate::current;
size_t ShareableIsolate::specifics_count = 0;
thread_pool_t ShareableIsolate::thread_pool(8);
uv_async_t ShareableIsolate::root_async;
std::thread::id ShareableIsolate::default_thread;
int ShareableIsolate::uv_refs = 0;
std::map<Isolate*, ShareableIsolate*> ShareableIsolate::isolate_map;
std::mutex ShareableIsolate::lookup_mutex;

}
