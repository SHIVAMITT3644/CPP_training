#include <iostream>
using namespace std;

// Function to calculate sum of all elements in 2D array
int sum2DArray(int arr[][3], int rows, int cols) {
    int sum = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            sum += arr[i][j];
        }
    }
    return sum;
}

// Function to find maximum element in 2D array
int max2DArray(int arr[][3], int rows, int cols) {
    int maxVal = arr[0][0];
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(arr[i][j] > maxVal)
                maxVal = arr[i][j];
        }
    }
    return maxVal;
}

int main() {
    const int rows = 3;
    const int cols = 3;

    int matrix[rows][cols] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "Original 2D Array:" << endl;
    for(int i = 0; i < rows; i++) 
    {
        for(int j = 0; j < cols; j++) 
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    matrix[1][1] = 50; // update element at row 2, col 2
    matrix[0][2] = 30; // update element at row 1, col 3

    cout << "\nUpdated 2D Array:" << endl;
    for(int i = 0; i < rows; i++) 
    {
        for(int j = 0; j < cols; j++) 
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    
    int totalSum = sum2DArray(matrix, rows, cols);
    int maxElement = max2DArray(matrix, rows, cols);

    cout << "\nSum of all elements: " << totalSum << endl;
    cout << "Maximum element: " << maxElement << endl;

    return 0;
}
