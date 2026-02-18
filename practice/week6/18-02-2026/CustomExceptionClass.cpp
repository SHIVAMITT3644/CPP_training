#include <iostream>
#include <exception>

using namespace std;

class OverSpeed : public exception 
{
    int speed;
    public:

    const char* what()
    {
        return " Overspeeding! PLease Slow down Your Speed";
    } 

    void getSpeed()
    {
        cout << "Your Car Speed is " << speed << endl;
    }
    
    void setSpeed(int speed)
    {
        this -> speed =  speed;
    }

};

class Car
{
    int speed;
    public:

    Car()
    {
        speed = 0;
        cout << "Your Car Speed is " << speed << endl;
    }

    void accelerate()
    {
        for(;;)
        {
            speed += 10;
            cout << "Your Car Speed is " << speed << endl;
            
            if(speed > 250)
            {
                OverSpeed overspeedInstance;

                overspeedInstance.setSpeed(speed);
                throw overspeedInstance;            
            }
        }
    }
};

int main()
{
    Car shivamCar;
    
    try{
        shivamCar.accelerate();
    }
    catch(OverSpeed error)
    {
        error.getSpeed();
        cout << endl << error.what() <<endl;
    }
}
