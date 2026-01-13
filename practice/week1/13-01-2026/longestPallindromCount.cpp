#include <iostream>
#include <vector>
using namespace std;

int main()
{
    string name = "abccccdd";
    vector<int> lowerCase(26,0);
    vector<int> upperCase(26,0);
    
    for(int stringIndex = 0; stringIndex < name.size(); stringIndex++)
    {
        if(name[stringIndex] >= 'a')
        {
            lowerCase[name[stringIndex] - 'a']++;
        }
        else
        {
            lowerCase[name[stringIndex] - 'A']++;
        }
    }

    int count = 0;
    bool odd = false;

    for(int arrayIndex = 0; arrayIndex < 26; arrayIndex++)
    {
        if(lowerCase[arrayIndex] % 2 == 0)
        {
            count += lowerCase[arrayIndex];
        }
        else
        {
            count += lowerCase[arrayIndex] - 1;
            odd = true;
        }

        if(upperCase[arrayIndex] % 2 == 0)
        {
            count += upperCase[arrayIndex];
        }
        else
        {
            count += upperCase[arrayIndex] - 1;
            odd = true;
        }
    }

    if(odd)
    {
        count ++;
    }

    cout << "Longest Palindrom Count = " << count <<endl;
}