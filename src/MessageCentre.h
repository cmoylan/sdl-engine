#pragma once

#include "MessageBus.h"

// Global message bus for the program
MessageBus& messageCentre()
{
    static MessageBus messageBus;
    return messageBus;
}