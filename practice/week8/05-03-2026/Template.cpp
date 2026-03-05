#include <iostream>

template <class T>
class vector{
public:
    T *arr;
    int size;

    vector(int size)
    {
        this->size = size;
        arr = new T[this->size];
    }

    template<class U>
    auto dotProduct(vector<U> &vec)
    {
        auto dotSum = 0.0;

        for(int i = 0; i < size; i++)
        {
            dotSum += this->arr[i] * vec.arr[i];
        }

        return dotSum;
    }
};

int main()
{
   vector<int> v1(2);
   vector<char> v2(2);

   v1.arr[0] = 1;
   v1.arr[1] = 2;

   v2.arr[0] = 'q';
   v2.arr[1] = 2.7;

   std::cout << v1.dotProduct(v2) << std::endl;
}