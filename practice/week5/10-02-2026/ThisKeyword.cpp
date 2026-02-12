#include <iostream>
using namespace std;

class Student {
    int id;

public:
    // Constructor
    Student(int id) {
        this->id = id;   // left: data member, right: parameter
    }

    void show() {
        cout << "ID: " << id << endl;
    }
};

int main() {
    Student s(101);
    s.show();
    return 0;
}