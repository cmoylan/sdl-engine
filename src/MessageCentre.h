#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>


using namespace std;

struct Message {
    int test;
};

typedef function<void (Message)> ListenerCallback;
typedef map<string, vector<ListenerCallback>> ListenerMap;
//typedef map<

class MessageCentre {

    // vector? messages
    // list messages
    ListenerMap listeners;

public:

    MessageCentre() {};
    ~MessageCentre() {};

    // TODO: read about std:function
    void subscribe(string eventName, ListenerCallback callback);

    // subscribe
    // unsubscribe

    // publish
    void publish(string eventName, Message body);

    // notify
    void notify();

    // tick / update

    // purge
    void purge();
};