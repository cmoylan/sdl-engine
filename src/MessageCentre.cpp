#include "MessageCentre.h"

void MessageCentre::publish(string eventName, Message body)
{
    vector<ListenerCallback>& callbacks = listeners[eventName];
    for (ListenerCallback& callback : callbacks) {
        (callback)(body);
    }
}


void MessageCentre::subscribe(string eventName, ListenerCallback callback)
{
    vector<ListenerCallback>& callbacks = listeners[eventName];
    callbacks.push_back(callback);
}



