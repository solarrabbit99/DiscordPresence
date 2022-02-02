#include <future>
#include <iostream>
#include "presence.h"

std::future<int> discordInstance;

int main()
{
    presence::discordSetup(discordInstance);
    bool shouldTick = true;
    while (shouldTick)
        presence::discordTick(shouldTick);
}