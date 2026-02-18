#include <iostream>
#include <exception>

class NegativeAgeException : public std::exception
{
    public:

    const char* what() const noexcept override
    {
        return "Exception Occurred : Age can't be Negative\n";
    }
};

int main()
{
    int age = -10;
    
    try
    {
        if(age < 0)
        throw NegativeAgeException();

        std::cout << "Age is Positive\n";
    }
    catch(const NegativeAgeException &error)
    {
        std::cout << error.what();
    }
}
