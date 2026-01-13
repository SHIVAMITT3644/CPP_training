#include <iostream>
#include <limits>

using namespace std;

int main()
{
    string name;

    cout << "Enter a name" << endl;

    cin >> name;
    cout << "name is " << name << endl;

    //bydefalut it ignore one character
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // for reading complete line use getline

    getline(cin , name);
    cout << "name is " << name << endl;
    
    //finding size of string
    cout << "The Size of string is " << name.size() << endl;

    //concatinate two string
    string s1 = "shivam" , s2 = "pratap";
    string s3 = s1 + " " + s2;
    //string s3 = s1.append(s2);

    cout << "Concatinated string is " << s3 << endl;

    s1.push_back('S');
    cout << s1 << endl;

    s1.pop_back();
    cout << s1 << endl;

    //store" in a string
    string s4 = "shivam is learning \"C++\"";
    cout << s4 << endl;
    
    return 0;
}