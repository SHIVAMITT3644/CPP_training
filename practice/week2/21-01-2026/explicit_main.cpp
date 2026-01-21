#include <iostream>
#include <dlfcn.h>
using namespace std;

int main() {

    void* handle = dlopen("./libhello.so", RTLD_LAZY);
    if (!handle) {
        cerr << "Error loading library" << endl;
        return 1;
    }

    void (*hello)();
    hello = (void (*)()) dlsym(handle, "hello");

    if (!hello) {
        cerr << "Error finding symbol" << endl;
        return 1;
    }

    hello();

    dlclose(handle);
    return 0;
}
