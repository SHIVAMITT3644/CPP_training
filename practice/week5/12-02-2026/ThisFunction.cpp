#include <iostream>
using namespace std;

class Student {
private:
    int rollNo;

public:
    void setData(int rollNo) 
    {
        this->rollNo = rollNo; 
    }  

    void display() 
    {
        cout << "Roll Number: " << rollNo << endl;
    }
};

int main() {
    Student s1;
    s1.setData(101);
    s1.display();

    return 0;
}