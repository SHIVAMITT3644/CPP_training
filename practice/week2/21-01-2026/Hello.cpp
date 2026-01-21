#include <iostream>
#include "Hello.h"

using namespace std;

extern "C" void hello() {
    cout << "Hello World" << endl;
}
