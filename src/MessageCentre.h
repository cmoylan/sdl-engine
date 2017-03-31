#pragma once

#include "MessageBus.h"

// Global message bus for the program
inline MessageBus& messageCentre()
{
    static MessageBus messageBus;
    return messageBus;
}