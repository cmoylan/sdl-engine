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
    MessageCentre messageBus;
    TestMessageReceiver receiver;

    messageBus.subscribe("toast", receiver.callback);

}
