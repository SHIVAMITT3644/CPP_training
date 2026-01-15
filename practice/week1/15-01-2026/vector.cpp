#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void printVector(vector<int> v)
{
    cout << "Vector is "  ;

    for(auto number : v)
    {
        cout << number << " ";
    }

    //other way
    // for(auto i =  v.begin(); i != v.end();i++)
    // {
    //     cout << *i;
    // }

    cout << endl;
}

int main()
{
    vector<int> v1;

    cout << "Intial size and capacity of vector is " << v1.size() << " " << v1.capacity() << endl;

    v1.push_back(1);
    v1.push_back(10);
    v1.push_back(8);
    v1.push_back(90);
    v1.push_back(20);

    printVector(v1);
    cout << "Intial size and capacity of vector is " << v1.size() << " " << v1.capacity() << endl;

    v1.pop_back();
    printVector(v1);
    cout << "Intial size and capacity of vector is " << v1.size() << " " << v1.capacity() << endl;

    v1.erase(v1.begin() + 1);
    printVector(v1);

    v1.insert(v1.begin() + 1 , 111);
    printVector(v1);

    cout << "Element at starting is " << v1.front() << endl;
    cout << "Element at end is " << v1.back() << endl;
    cout << "Element at index 2 is " << v1.at(2) << endl;
    cout << "Is vector is empty = " << v1.empty() << endl;
    cout << "111 is present " << count(v1.begin(), v1.end(), 111) << " times" << endl;
    cout << "Maximum Element is " << *max_element(v1.begin(), v1.end()) << endl;
    cout << "Minimum Element is " << *min_element(v1.begin(), v1.end()) << endl;


    //sort in ascending order
    cout << "Sorting vector in ascending order" << endl;
    sort(v1.begin() , v1.end());
    printVector(v1);

    //binary_search
    if(binary_search(v1.begin() , v1.end() , 90))
    {
        cout << "element is present at index ";
        cout << find(v1.begin() , v1.end(),90) - v1.begin() << endl;;
    }
    else
    {
        cout << "Element is not Present" << endl;;
    }

    //sort in decending order
    cout << "Sorting vector in decending order" << endl;
    sort(v1.begin() , v1.end() , greater<int>());
    printVector(v1);

    return 0;
}
