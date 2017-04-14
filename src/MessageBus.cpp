#include "MessageCentre.h"


void MessageBus::clear(string eventName)
{
    vector<Message>& queue = messageQueue.at(eventName);
    queue.clear();
    messageQueue.erase(eventName);
}


void MessageBus::flush(string eventName)
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


void MessageBus::notify()
{
    for (auto queuePair : messageQueue) {
        auto eventName = queuePair.first;
        flush(eventName);
    }
}


void MessageBus::publish(string eventName, Message message)
{
    vector<Message>& channel = messageQueue[eventName];
    channel.push_back(message);
}


void MessageBus::purge()
{
    for (auto queuePair : messageQueue) {
        auto eventName = queuePair.first;
        clear(eventName);
    }
}


void MessageBus::subscribe(string eventName,
                           int uuid,
                           ListenerCallback callback)
{
    vector<ListenerCallback>& callbacks = listeners[eventName];
    callbacks.push_back(callback);

    //auto& listenersByUuid
    //callbacks.back()
    // get the listenersByUuid, insert a reference to the stored callback
}
