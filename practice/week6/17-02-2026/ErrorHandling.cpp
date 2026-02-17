#include <iostream>
#include <stdexcept>
using namespace std;

void test()
{
    // throw 5;
    // throw runtime_error("Runtime exception");
    // throw 'S';
    throw "string exception";
}

int main()
{
    int number1 = 10;
    int number2 = 0;
    int result;

    try
    {
        if(number2 == 0)
        {
            throw "divided by zero exception";
        }
        result = number1 / number2;

        cout << "number1 / number2 = " << result << endl;
    }
    catch(const char *e)
    {
        cout << "An error Occured " << endl << e << endl;
    }

    //Runtime error standard exception

    try
    {
        if(number2 == 0)
        {
            throw runtime_error("divided by zero exception");
        }
        
        result = number1 / number2;

        cout << "number1 / number2 = " << result << endl;
    }
    catch(runtime_error &e)
    {
        cout << "An error Occured " << endl;
        cout << e.what() << endl;
    }

    //Multiple Catch block

    cout << endl << "Multiple Catch Block"<<endl;

    try
    {
        // throw "string Exception";
        // throw 2;
        // throw runtime_error("Runtime Error Occured");
        throw bad_array_new_length();
    }
    catch(const char *error)
    {
        cout << error << '\n';
    }
    catch(int error)
    {
        cout << "integer exception occured :- " << error << endl ;
    }
    catch(runtime_error error)
    {
        cout << error.what() << endl;
    }
        catch(bad_array_new_length error)
    {
        cout << error.what() << endl;
    }
    catch(...)
    {
        cout << "All Exception Other Than this Handled here" << endl;
    }

    //exception throw by function
    cout << endl << "exception throw by function"<<endl;
    try
    {
        test();
    }
    catch(const char e)
    {
        cout << "Char Exception :- " << e << endl;
    }
    catch(const char *e)
    {
        cout << e << endl;
    }
    catch( int e)
    {
        cout << "Interger Exception :- " << e << endl;
    }   
    catch(runtime_error e)
    {
        cout << "Exception caused by " << e.what() << endl;
    }

    //Nested a try catch and rethrow exception
    cout << endl;
    cout << "Nested try catch and rethrow exception" << endl;

    try
    {
        try
        {
            throw "string type exception";
        }
        catch(char *error)
        {
            cout << "Exception occurred in inner block -->" << error << endl;
            cout << "Rethrowing Exception from inner block to outer block" << endl;
            
            throw;
        }
    }
    catch(char *error)
    {
        cout << "Exception occurred in outer block -->" << error << endl;
    }
    catch(...)
    {
        cout << "Other exception handled here in outer block" << endl ;
    }

    return 0;
}
