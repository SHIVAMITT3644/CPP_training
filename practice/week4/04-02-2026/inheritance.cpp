#include <iostream>
#include <string>
using namespace std;


class BasicPerson
{
protected:
    string name;
    int age;
    float weight;

public:
    BasicPerson(string, int, float);
};


class PersonalDetails
{
protected:
    string religion;
    string caste;

public:
    PersonalDetails(string, string);
};

class Student : public BasicPerson
{
public:
    Student(string, int, float);
    void showStudent();
};


class Company : public BasicPerson, public PersonalDetails
{
public:
    Company(string, int, float, string, string);
    void showDetails();
};



BasicPerson::BasicPerson(string name, int age, float weight)
{
    this->name = name;
    this->age = age;
    this->weight = weight;
}

PersonalDetails::PersonalDetails(string religion, string caste)
{
    this->religion = religion;
    this->caste = caste;
}

Student::Student(string name, int age, float weight)
    : BasicPerson(name, age, weight)
{
}

Company::Company(string name, int age, float weight,
                 string religion, string caste)
    : BasicPerson(name, age, weight),
      PersonalDetails(religion, caste)
{
}



void Student::showStudent()
{
    cout << "Name   : " << name << endl;
    cout << "Age    : " << age << endl;
    cout << "Weight : " << weight << endl;
}

void Company::showDetails()
{
    cout << "Name     : " << name << endl;
    cout << "Age      : " << age << endl;
    cout << "Weight   : " << weight << endl;
    cout << "Religion : " << religion << endl;
    cout << "Caste    : " << caste << endl;
}



int main()
{
    Student s("Nikita", 20, 55.0);
    Company c("Shivam", 22, 65.5, "Hindu", "Rajput");

    cout << "Student Details:\n";
    s.showStudent();

    cout << "\nCompany Details:\n";
    c.showDetails();

    return 0;
}