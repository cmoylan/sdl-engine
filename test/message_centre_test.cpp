#include <functional>
#include <iostream>

#include "catch.hpp"

#include "MessageCentre.h"

using namespace std;


class TestMessageReceiver {
public:
    int number = 0;

    void callback(Message message)
    {
        number = message.test;
    };
};



TEST_CASE("it calls back", "[MessageCentre]")
{
    using namespace placeholders; // adds visibility of _1, _2, _3,...

    MessageCentre messageBus;
    TestMessageReceiver receiver;

    //messageBus.subscribe("toast", receiver.callback);
    // handler->addHandler(std::bind(&MyClass::Callback, this, _1));
    messageBus.subscribe("toast", bind(&TestMessageReceiver::callback, &receiver,
                                       _1));

    Message message;
    message.test = 1;

    messageBus.publish("toast", message);

    // flush the queue and notify subscribers
    messageBus.notify();

    REQUIRE(receiver.number == 1);
}
