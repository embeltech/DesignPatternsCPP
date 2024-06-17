#include <iostream>
class service{
    public:
      virtual void request()=0;
};

class realservice:public service{
    public:
      realservice(){std::cout<<"[Real] Service started\n";}
      void request()
      {
        std::cout<<"[Real] Serving Request\n";
      }
      ~realservice()
      {
        std::cout<<"[Real] Original Service shutdown\n";
      }
}; 

class proxyservice:public service{
    private:
      realservice * rserv;
    public:
      proxyservice():rserv(nullptr){std::cout<<"[Proxy] Service started\n";}
      void request()
      {
        //Lazy loading. Instantiate when needed.
        if(rserv==nullptr)
        {
            std::cout<<"[Lazy loading] Start real service\n";
            rserv = new realservice();
        }
        else{
            std::cout<<"[cached result] Start real service\n";
        }
        std::cout<<"[Proxy] Serving Request\n";
        rserv->request();
    }
    ~proxyservice()
    {
        delete rserv;
        rserv = nullptr;
    }
};


int main()
{
    std::cout<<"Hello World\n";
    std::cout<<"----- proxy service [lazy load]------\n";
    proxyservice p;
    p.request();

    std::cout<<"----- proxy service [cached]------\n";
    service * sptr = &p;
    sptr->request();

    return 0;

}
