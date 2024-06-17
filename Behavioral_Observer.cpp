#include <iostream>
#include <list>

class iListner{
  public:
    virtual void NotifyMsg(std::string strMsg)=0;
};
 

class iPublisher{
    public:
    virtual void subscribe(iListner * subscriber)=0;
    virtual void unsubscribe(iListner * subscriber)=0;
    virtual void OnMessageReceived(std::string strMsg)=0;
};

 
class subscriber:public iListner{
    private:
        int id;
        iPublisher * ptrPublisher;
    public:
      subscriber(int i,iPublisher * ptr):id(i),ptrPublisher(ptr)
      {
        ptrPublisher->subscribe(this);
      }
      void NotifyMsg(std::string strMsg)
      {
        std::cout<<__FUNCTION__<<"Subscriber "<<id<<": "<<strMsg<<std::endl;
      }
      void unsubscribeMsg()
      {
        ptrPublisher->unsubscribe(this);
      }
};

 

class EventManager: public iPublisher{
    private:
      std::list<iListner *> lstSubscribers;
    public:
      void subscribe(iListner * subscriber)
      {
          lstSubscribers.push_back(subscriber);
      }
      void unsubscribe(iListner * subscriber)
      {
        lstSubscribers.remove(subscriber);
      }
      void OnMessageReceived(std::string strMsg)
      {
        for(iListner * iter:lstSubscribers)
            iter->NotifyMsg(strMsg);
      }
};

int main()
{
    std::cout<<"Hello World\n";
    std::cout<<"Creating Publisher\n";
    iPublisher * ptrEvManager = new EventManager();
    std::cout<<"Creating Subscribers 1,2,3\n";
    subscriber *s1 = new subscriber(1, ptrEvManager);
    subscriber *s2 = new subscriber(2, ptrEvManager);
    subscriber *s3 = new subscriber(3, ptrEvManager);

    std::cout<<"Simulating message event\n";
    ptrEvManager->OnMessageReceived("Message X");
  
    std::cout<<"Subscriber 2 unsubscribed\n";
    s2->unsubscribeMsg();
  
    std::cout<<"Simulating message event\n";
    ptrEvManager->OnMessageReceived("Message Y"); 

    return 0;

}
