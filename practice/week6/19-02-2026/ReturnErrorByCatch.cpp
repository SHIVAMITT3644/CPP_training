#include <iostream>
using namespace std;

int divide(int a, int b) {
    try {
        if (b == 0) {
            throw runtime_error("Division by zero");
        }
        return a / b;
    }
    catch (runtime_error &e) {  
        cout << "Error: " << e.what() << endl;
        return -1;   // Error code returned to caller
    }
}

int main() {
    int result = divide(10, 0);
    cout << "Result: " << result << endl;
    return 0;
}
