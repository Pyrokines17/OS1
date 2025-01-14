#include <dlfcn.h>

int main(void) {
	void* handle;
	void (*hello)();

	handle = dlopen("../4/libdynamic.so", RTLD_LAZY);
	hello = dlsym(handle, "hello_from_dyn_runtime_lib");

	(*hello)();

	dlclose(handle);

	return 0;
}