#include <iostream>
#include <exception>

using namespace std;

int main()
{
    set_terminate([](){
        cout << "set_terminate exception handler" << flush;
        abort();
    });

    throw 1;
    return 0;
}