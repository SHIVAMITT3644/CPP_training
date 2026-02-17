#include <iostream>

int computeSum(int n)
{
    int sum = 0;

    for (int i = 1; i <= n; i++)
    {
        sum += i;

        if (i == 5)
        {
            sum += 100;   // <-- Intentional logic bug
        }
    }

    return sum;
}

int main()
{
    int n = 10;
    int result = computeSum(n);

    int counter = 0;

    while (counter < 3)
    {
        std::cout << "Counter: " << counter << std::endl;
        counter++;
    }

    std::cout << "Final Sum: " << result << std::endl;

    return 0;
}
