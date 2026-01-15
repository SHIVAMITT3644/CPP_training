#include <iostream>
using namespace std;

int main()
{
    // way to initialize array
    int array[5] = {1,2,3,4,5};
    int array1[] = {1,2,3,4};
    int array2[5] = {5};
    int array3[5] = {0};


    cout << "array1 is :- ";

    for(int i = 0; i < 4; i++)
    {
        cout  << array1[i] << " ";
    }

    cout << endl;

    cout << "array2 is :- ";

    for(int i = 0; i < 5; i++)
    {
        cout  << array2[i] << " ";
    }

    cout << endl;

    cout << "array3 is :- ";

        
    for(int i = 0; i < 5; i++)
    {
        cout << array3[i] << " ";
    }

    cout  << endl << endl;

    cout << "----------------------------------" << endl;
    cout << "array is :- ";

    for(int i = 0; i < 5; i++)
    {
        cout  << array[i] << " ";
    }

    cout  << endl;

    {
        //minimum element in array

        int result = INT8_MAX;

        cout << "Minimum element in array is = ";

        for(int i = 0; i < 5; i++)
        {
            if(result > array[i])
            {
                result = array[i];
            }       
        }

        cout << result << endl;
    }

    {
        //search element in array

        int searchElement = 2;
        bool isPresent = false;

        for(int i = 0; i < 5; i++)
        {
            if(searchElement == array[i])
            {
                cout << "Element is present at index " << i << endl;
                isPresent = true;
                break;
            }       
        }

        if(!isPresent)
        {
            cout <<  searchElement << " is not present" << endl;
        }
    }

    {
        //Reversing the array

        int i = 0;
        int j = 4;

        while(i < j)
        {
            swap(array[i] , array[j]);
            i++;
            j--;
        }

        cout << "After Reversing the array == " ;

        for(int i = 0; i < 5; i++)
        {
            cout << array[i] << " ";     
        }

        cout << endl;
    }

    {
        //missing number in the array
        //missing number from 1 to N
        int tempArray[] = {3,2,1,6,8,4,7};
        int sum = 0;
        int sumOfNNumber = 0;
        int size = sizeof(tempArray)/sizeof(tempArray[0]);

        for(int i = 0; i < size; i++)
        {
            sum += tempArray[i];     
        }

        for(int i = 1; i <= size + 1; i++)
        {
            sumOfNNumber += i;     
        }
        
        cout << "Missing number is " << sumOfNNumber - sum ;

        cout << endl;
    }

    {
        int number; 

        cout << "Enter a number for fibonnacci" << endl;
        cin >> number;

        int array[1000];

        array[0] = 0;
        array[1] = 1;

        for(int i = 2; i < number; i++)
        {
            array[i] = array[i-1] + array[i-2];
        }

        cout << "Fibonacci series is :- ";
    
        for(int i = 0; i < number; i++)
        {
            cout << array[i] << " ";     
        }

        cout << endl;
    }
        
    return 0;
}