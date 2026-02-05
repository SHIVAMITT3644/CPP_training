#include <bits/stdc++.h>
using namespace std;

class Area {
public:
    
    // Function to add two integers
    void add(int a, int b) {
        cout << "Integer Sum = " << a + b
        << endl;
    }
    
    // Function to add two floating point values
    void add(double a, double b) {
        cout << "Float Sum = " << a + b
        << endl ;
    }
};

int main() {
    Area a1;
    
    // add() called with int values
    a1.add(10, 2);

    // add() called with double value
    a1.add(5.3, 6.7);

    return 0;
}