#include <iostream>
#include <vector>

using namespace std;

void printNNaturalNumber(int number)
{
    if (number == 1)
    {
        cout << number << " ";
        return;
    }

    printNNaturalNumber(number - 1);
    cout << number << " ";
}

int factorial(int number)
{
    if(number == 0)
    {
        return 1;
    }

    return number * factorial(number - 1);
}

int nthTermOfFibonnaciSeries(int number)
{
    if(number == 0 || number == 1)
    {
        return number;
    }

    return nthTermOfFibonnaciSeries(number - 1) + nthTermOfFibonnaciSeries(number - 2);
}

int sumOfNNaturalNumber(int number)
{
    if(number == 1)
    {
        return 1;
    }
    
    return  number + sumOfNNaturalNumber(number - 1);
}

bool isSorted(vector<int> array , int n)
{
    if(n == 0 || n == 1)
    {
        return true;
    }
 
    return array[n-1] >= array[n-2] && isSorted(array , n-1);
}

int binary_search(vector<int> array , int target , int start, int end)
{
    if(start <= end)
    {
        int mid = start + (end - start)/2;

        if(array[mid] == target)
        {
            return mid;
        }
        else if (array[mid] <= target)
        {
            return binary_search(array, target, mid+1, end);
        }
        else
        {
            return binary_search(array, target, start, mid - 1);
        }        
    }

    return -1;
}

void printSubArray(vector<int> &array, vector<int> &resultArray , int temperoryVariable)
{
    if(temperoryVariable == array.size())
    {
        for(int value : resultArray)
        {
            cout<< value << " ";
        }

        cout << endl;
        return;
    }

    resultArray.push_back(array[temperoryVariable]);
    printSubArray(array , resultArray , temperoryVariable +1); 

    resultArray.pop_back();
    printSubArray(array , resultArray , temperoryVariable +1);
}

int main()
{
    int number;

    cout << "Enter a number" << endl;
    cin >> number;

    cout << "All natural Number from 1 to " << number << " is :";
    printNNaturalNumber(number);
    cout << endl;

    cout << "Factorial of " << number << " is : " << factorial(number);
    cout << endl;  
    
    cout << "Sum of " << number << " Natural number is : " << sumOfNNaturalNumber(number);
    cout << endl; 
    
    cout << number << "th term of Fibonnaci series is : " << nthTermOfFibonnaciSeries(number);
    cout << endl;

    vector<int> array = {1,2,3};

    if(isSorted(array,5))
    {
        cout << "Given Array is Sorted";
    }
    else
    {
        cout << "Given Array is Not Sorted";
    }
    cout << endl;

    if(binary_search(array , 10, 0, array.size()-1) == -1)
    {
        cout << "Target value not found" << endl;
    }
    else
    {
        cout << "Target value found at index" << binary_search(array , 2, 0, array.size()-1) << endl;
    }

    vector<int> resultArray;
    cout << "All Possible subser of Given Array array : " << endl;
    printSubArray(array ,resultArray ,0);

    return 0;
}