#include <iostream>
using namespace std;

int main()
{
    string ipAddress = "255.6.11.5.7.16.5";
    string temp;

    for(int stringIndex = 0; stringIndex < ipAddress.size(); stringIndex++)
    {
        if(ipAddress[stringIndex] == '.')
        {
            temp += "[.]";
        }
        else
        {
            temp += ipAddress[stringIndex];
        }
    }
    
    cout << "Defanging Ip address is : " << temp << endl;
    temp .clear();

    return 0;
}