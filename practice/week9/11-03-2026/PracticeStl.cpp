#include <iostream>
#include <vector>

int main()
{
    std::vector<std::vector<int>> v;

    int rows, column;

    std::cout << "Enter number of rows: ";
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> column;

    for (int i = 0; i < rows; i++)
    {
        v.emplace_back();
        for (int j = 0; j < column; j++)
        {
            int x;
            std::cin >> x;
            v.back().emplace_back(x);
        }        
    }

    int countNoOfZero = 0;
    std::vector<std::vector<int>> :: iterator rowit;
    std::vector<int> :: iterator columnit;


    for (rowit = v.begin(); rowit != v.end(); )
    {
        bool isRowZero = true;

        for ( columnit = rowit->begin(); columnit != rowit->end(); columnit++)
        {
            if (*columnit != 0)
            {
                isRowZero = false;
                break;
            }
        }

        if (isRowZero)
        {
            countNoOfZero++;
            rowit = v.erase(rowit);
        }
        else
        {
            ++rowit;
        }
    }

    for (int i = 0; i < countNoOfZero; i++)
    {
        v.emplace_back();
        for (int j = 0; j < column; j++)
        {
            v.back().emplace_back(0);
        }
    }

    std::cout << "\n";

    for (auto rowit = v.begin(); rowit != v.end(); rowit++)
    {
        for (auto columnit = rowit->begin(); columnit != rowit->end(); columnit++)
        {
            std::cout << *columnit << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
