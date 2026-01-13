#include <iostream>
using namespace std;

void rotateClockwise(string &name);

int main()
{
    int noOfTimes;
    string name = "in time tec jaipur";

    cout << "Enter number of time you want to rotate a string" << endl;
    cin >> noOfTimes;
    
    for(int index = 1; index <= noOfTimes; index++)
    {
        rotateClockwise(name);
    }
    
    cout << "String after rotated by " << noOfTimes << " place is " << name << endl;
}

void rotateClockwise(string &name)
{
    int stringIndex = name.size() - 2;
    char character = name[name.size() - 1];

    while(stringIndex >= 0)
    {
        name[stringIndex + 1] = name[stringIndex];
        stringIndex--;
    }

    name[0] = character;
}