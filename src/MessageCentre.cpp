#include "MessageCentre.h"


void MessageCentre::clear(string eventName)
{
    vector<Message>& queue = messageQueue.at(eventName);
    queue.clear();
    messageQueue.erase(eventName);
}


void MessageCentre::flush(string eventName)
{
    vector<Message>& queue = messageQueue.at(eventName);
    vector<ListenerCallback>& callbacks = listeners[eventName];

    for (Message message : queue) {
        for (ListenerCallback& callback : callbacks) {
            callback(message);
        }
    }

    clear(eventName);
}


void MessageCentre::notify()
{
    for (auto queuePair : messageQueue) {
        auto eventName = queuePair.first;
        flush(eventName);
    }
}


void MessageCentre::publish(string eventName, Message message)
{
    vector<Message>& channel = messageQueue[eventName];
    channel.push_back(message);
}


void MessageCentre::purge()
{
    for (auto queuePair : messageQueue) {
        auto eventName = queuePair.first;
        clear(eventName);
    }
}


void MessageCentre::subscribe(string eventName, ListenerCallback callback)
{
    vector<ListenerCallback>& callbacks = listeners[eventName];
    callbacks.push_back(callback);
}



