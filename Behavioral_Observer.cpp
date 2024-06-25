#include <iostream>
#include <list>

class iSubscriber{
  public:
    virtual void NotifyMsg(std::string strMsg)=0;
};
 

class iPublisher{
    public:
    virtual void subscribe(iSubscriber * subscriber)=0;
    virtual void unsubscribe(iSubscriber * subscriber)=0;
    virtual void OnMessageReceived(std::string strMsg)=0;
};

 
class EventListner:public iSubscriber{
    private:
        int id;
        iPublisher * ptrPublisher;
    public:
      EventListner(int i,iPublisher * ptr):id(i),ptrPublisher(ptr)
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
      std::list<iSubscriber *> lstSubscribers;
    public:
      void subscribe(iSubscriber * subscriber)
      {
          lstSubscribers.push_back(subscriber);
      }
      void unsubscribe(iSubscriber * subscriber)
      {
        lstSubscribers.remove(subscriber);
      }
      void OnMessageReceived(std::string strMsg)
      {
        for(iSubscriber * iter:lstSubscribers)
            iter->NotifyMsg(strMsg);
      }
};

int main()
{
    std::cout<<"Hello World\n";
    std::cout<<"Creating Publisher\n";
    iPublisher * ptrEvManager = new EventManager();
    std::cout<<"Creating Subscribers 1,2,3\n";
    EventListner *s1 = new EventListner(1, ptrEvManager);
    EventListner *s2 = new EventListner(2, ptrEvManager);
    EventListner *s3 = new EventListner(3, ptrEvManager);

    std::cout<<"Simulating message event\n";
    ptrEvManager->OnMessageReceived("Message X");
  
    std::cout<<"Subscriber 2 unsubscribed\n";
    s2->unsubscribeMsg();
  
    std::cout<<"Simulating message event\n";
    ptrEvManager->OnMessageReceived("Message Y"); 

    return 0;

}
