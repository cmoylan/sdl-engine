#pragma once

#include <iostream>
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
typedef map<string, vector<Message>> MessageMap;

class MessageCentre {

    // vector? messages
    // list messages
    ListenerMap listeners;
    MessageMap messageQueue;

public:

    MessageCentre() {};
    ~MessageCentre() {};

    /**
     * Register a callback on an event
     * @param eventName the name of the event to which you are subscribing
     * @param callback the function/method to be called when the event occurs
     *
     * #include <functional>
     *
     * class Reciever {
     * public:
     *   void callback(Message body);
     * }
     * Receiver receiver;
     *
     * messageBus.subscribe("my event", bind(&Receiver::callback, &receiver, placeholders::_1))
     *
     */
    void subscribe(string eventName, ListenerCallback callback);
    // unsubscribe [?]

    void publish(string eventName, Message body);

    // will go through a queue and send all messages
    void flush(string eventName);

    // will empty a queue
    void clear(string eventName);

    // flush all published messages
    void notify();

    // clear all published messages
    void purge();
};