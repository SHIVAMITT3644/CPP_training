#include <iostream>

struct Date {
    int day;
    int month;
    int year;
};


void print(const Date& today) {
    std::cout << today.day << "/" << today.month << "/" << today.year;
}



struct Person
{
    std::string name{};
    int age{};

    void kisses(const Person& person)
    {
        std::cout << name << " give choclate to " << person.name << '\n';
    }
};

int main() {
    Date today {16, 9, 2026};
    print(today);   // object explicitly pass kiya
    std::cout << "\n";

    Person joe{ "Joe", 29 };
    Person kate{ "Kate", 27 };

    joe.kisses(kate);
}