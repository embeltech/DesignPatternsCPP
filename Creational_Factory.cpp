#include <iostream>

//product
class vehicle{
    public:
      virtual void drive()=0;
      virtual ~vehicle(){}
};

//concrete products car,truck
class car:public vehicle{
    public:
      car(){std::cout<<"CAR product created\n";}
      void drive(){std::cout<<"CAR Driving\n";}
};
class truck:public vehicle{
    public:
      truck(){std::cout<<"TRUCK product created\n";}
      void drive(){std::cout<<"TRUCK Driving\n";}
};
//----------------------------------------------------
//creator with factory method
class vehicleFactory{
    public:
    virtual vehicle * createVehicle()=0;
    virtual ~vehicleFactory(){}
};
//creator concrete
class carFactory:public vehicleFactory{
    public:
    carFactory(){std::cout<<"created carFactory\n";}
    vehicle * createVehicle(){
        std::cout<<"Create CAR from carFactory\n";
        return new car();
    }
};
class truckFactory:public vehicleFactory{
    public:
    truckFactory(){std::cout<<"created truckFactory\n";}
    vehicle * createVehicle(){
        std::cout<<"Create TRUCK from truckFactory\n";
        return new truck();
    }
};
//------------------------------------------------------
int main()
{
    std::cout<<"Hello World\n";
    int choice;
    std::cout<<"Enter 1 for car, 2 for truck : \n";
    std::cin>>choice;

    vehicleFactory * vfPtr=nullptr;
    if(1 == choice)
        vfPtr = new carFactory();
    else if(2 == choice)
        vfPtr = new truckFactory();

    if(nullptr != vfPtr)
    {
        vehicle * veh = vfPtr->createVehicle();
        veh->drive();
    }   

    return 0;
}

 
