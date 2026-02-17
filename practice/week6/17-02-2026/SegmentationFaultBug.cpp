#include <iostream>
#include <cstring>

using namespace std;

class Student {
private:
    char* name;
    int marksCount;
    int* marks;

public:
    Student(const char* n, int count) 
    {
        name = new char[strlen(n) + 1];
        strcpy(name, n);

        marksCount = count;
        marks = new int[marksCount];

        for (int i = 0; i < marksCount; i++) 
        {
            marks[i] = (i + 1) * 10;
        }
    }

    void printAverage() {
        int sum = 0;
        for (int i = 0; i <= marksCount; i++) 
        {   // BUG HERE 
            sum += marks[i];
        }
        cout << "Average: " << sum / marksCount << endl;
    }

    void updateName(const char* newName) 
    {
        // BUG: not reallocating memory properly
        strcpy(name, newName);  // potential overflow
    }

    ~Student() {
        delete[] name;
        delete[] marks;
    }
};

void processStudent(Student* s) 
{
    if (s == nullptr) {
        cout << "Invalid student!" << endl;
    }

    s->printAverage();   // possible null dereference
}

int main() {
    Student* s1 = new Student("Rahul", 5);

    s1->printAverage();

    s1->updateName("VeryVeryLongStudentNameThatWillOverflowMemory");

    delete s1;

    cout << "\nNow testing null pointer case...\n";

    Student* s2 = nullptr;
    processStudent(s2);   // definite segmentation fault here

    return 0;
}