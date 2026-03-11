#include<iostream>
#include <queue>
#include <vector>

using namespace std;

bool cmp(int a, int b)
{
    return a>b;
}

int main()
{
    priority_queue<int , vector<int>, bool(*)(int,int)> pq(cmp);

    pq.push(10);
    pq.push(4);
    pq.push(7);
    pq.push(1);
    pq.push(15);

    while(!pq.empty())
    {
        std::cout << pq.top()<< " ";
        pq.pop();
    }

    return  0;
}