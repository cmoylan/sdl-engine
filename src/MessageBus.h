#pragma once

#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <vector>


using namespace std;

// this needs to be flexible 
// i'm not sure what kind of information callback functions will want
struct Message {
    int test;
};

typedef function<void (Message)> ListenerCallback;
typedef map<string, vector<ListenerCallback>> ListenerMap;
typedef map<string, vector<Message>> MessageMap;

class MessageBus {

    // vector? messages
    // list messages
    ListenerMap listeners;
    MessageMap messageQueue;

public:

    MessageBus() {};
    ~MessageBus() {};

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
     * @todo create a helper so consuming code isn't littered with bind/placeholder
     */
    void subscribe(string eventName, ListenerCallback callback);
    // unsubscribe [?]

    /**
     * Publish an event
     * @param evenName the name of the event
     * @param message the message you would like to publish
     */
    void publish(string eventName, Message message);

    /**
     * Send all queued messages for a single event
     * @param eventName the name of the event
     */
    void flush(string eventName);

    /**
     * Empty a single queue, without notifying subscribers
     * @param evenName the event you with to clear
     */
    void clear(string eventName);

    /**
     * Flush all published messages, notify any subscribers
     */
    void notify();

    /**
     * Clear all published messages
     */
    void purge();
};