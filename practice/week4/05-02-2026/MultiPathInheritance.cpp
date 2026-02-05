#include <iostream>
using namespace std;

class A {
public:
int a;
    void show() {
        cout << "Class A" << endl;
    }
};

class B : public virtual A {
};

class C : public virtual A {
};

class D : public B, public C {
};

int main() {
    D obj;
    obj.show();
    obj.B::show(); 
    obj.C::show();
    return 0;
}