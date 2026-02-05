#include <iostream>
using namespace std;

class Complex {
public:
    int real, imag;

    // constructor
    Complex(int r = 0, int i = 0) {
        real = r;
        imag = i;
    }

    // operator overloading using member function
    Complex operator+(Complex c) {
        Complex temp;
        temp.real = real + c.real;
        temp.imag = imag + c.imag;
        return temp;
    }

    void display() {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex c1(2, 3);
    Complex c2(4, 5);

    Complex c3 = c1 + c2;   // operator overloading

    c3.display();           // Output: 6 + 8i
    return 0;
}