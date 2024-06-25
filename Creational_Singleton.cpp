#include <iostream>

class mytest{

  private:
    int data;
    static mytest *instance;  
    mytest(int x):data(x){}  //Private CTOR to avoid 'new' operator object creation
    ~mytest(){std::cout<<"DTOR called\n";} //Private DTOR to avoid 'delete' operation

  public:
    //delete copy CTOR and assignment operator to avoid copy creation
    mytest(const mytest & ) = delete;
    void operator=(const mytest & ) = delete;
    // get instance interface
    static mytest* getinstance()
    {
        if(nullptr == instance)
        {
            instance = new mytest(20);
        }
        return instance;
    }
    void print()
    {
        std::cout<<data;
    }

};

mytest * mytest::instance=nullptr;

int main()
{
    mytest *ptr = mytest::getinstance();
    std::cout<<"Hello World\n";
    ptr->print();
   
    return 0;
}
