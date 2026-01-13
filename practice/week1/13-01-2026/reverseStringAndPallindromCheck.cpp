#include <iostream>
using namespace std;

void reverseString(string &s)
{
    int start = 0 , end = s.size()-1;

    while(start < end)
    {
        swap(s[start], s[end]);
        start++;
        end--;
    }
}

void checkPallindrom(string s)
{
    int start = 0 , end = s.size()-1;

    while(start < end)
    {
        if(s[start] != s[end])
        {
            cout << "Not a palindrom string" << endl;
            return;
        }
        start++;
        end--;
    }
    cout << s << " is " << "palindrom string" << endl;
}
 
int main()
{
    string s1 = "naman";
    
    cout << "Before Reversing : " << s1 << endl;
    reverseString(s1);
    cout << "After Reversing : " << s1 << endl;

    checkPallindrom(s1);

}