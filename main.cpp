#include <iostream>
#include <vector>
#include <unistd.h>
#include "communication/identifiable.h"
#include "communication/abstract_client.h"
#include "communication/abstract_sender.h"

using namespace depth_clustering;
using namespace std;


class Publisher : public AbstractSender<int> {
public:
    explicit Publisher(int d) : AbstractSender<int>{SenderType::STORER}, _data_tx(d) {}

    ~Publisher() {}

    int getData() {
        return _data_tx;
    }

private:
    int _data_tx;
};


class Subscriber : public AbstractClient<int> {
public:
    explicit Subscriber() : AbstractClient<int>{}, _data_rx(0) {}

    explicit Subscriber(int d) : AbstractClient<int>{}, _data_rx(d) {}

    ~Subscriber() {}

    //必须实现这个类
    void OnNewObjectReceived(const int &object,
                             const int sender_id) {
        cout << "received object: " << object << endl;
        cout << "received sender_id: " << sender_id << endl;
    }

private:
    int _data_rx;
};

int main() {
    //为什么publisher的id相同，subscriber的id就不同？
    Publisher pub(10);
    cout << __LINE__ << " " << pub.id() << endl;//1
    cout << __LINE__ << " " << Identifiable::get_current_id_counter() << endl;//1

    Subscriber sub1(1);
    cout << __LINE__ << " " << sub1.id() << endl;//2
    cout << __LINE__ << " " << Identifiable::get_current_id_counter() << endl;//3

    Subscriber sub2(2);
    cout << __LINE__ << " " << sub2.id() << endl;//4
    cout << __LINE__ << " " << Identifiable::get_current_id_counter() << endl;//5


    Publisher pub2(10);
    cout << __LINE__ << " " << pub2.id() << endl;//6
    cout << __LINE__ << " " << Identifiable::get_current_id_counter() << endl;//6
    cout << __LINE__ << " " << Identifiable::get_current_id_counter() << endl;//6


    Subscriber sub5;
    cout << __LINE__ << " " << Identifiable::get_current_id_counter() << endl;//8
    cout << __LINE__ << " " << sub5.id() << endl;//7
    cout << __LINE__ << " " << Identifiable::get_current_id_counter() << endl;//8

    sleep(1);
    //why this is multi-thread
//    pub.AddClient(&sub1);
//    pub.AddClient(&sub2);
//    pub.AddClient(&sub3);
//    pub.AddClient(&sub4);

//    sleep(2);
    //    cout<<Identifiable::get_current_id_counter()<<endl;
//    pub.ShareDataWithAllClients(pub.getData());
    return 0;
}