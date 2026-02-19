#include <iostream>
#include <string>

int main()
{
    std::string exceptio = "hehehehe";
    try
    { 
        try{
            std::cout <<"1" << "\n"; 
        
        std::cout <<"2" << "\n";
        throw 10.5;
        throw exceptio;
        std::cout <<"3" << "\n";
        throw -1;
        }catch(double){
            std::cout << "hii\n";
            throw;
        }

        throw 1;
    }
    catch (double) 
    {
        std::cerr << "We caught an exception of type double\n";
    }
    catch (int x)
    {
        std::cerr << "We caught an int exception with value: " << x << '\n';
    }
    catch (const std::string&) 
    {
        std::cerr << "We caught an exception of type std::string\n";
    }

    std::cout << "Continuing on our merry way\n";

    return 0;
}
    