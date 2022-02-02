#include <chrono>
#include <future>
#include <iostream>
#include <discord/discord.h>
#include <unistd.h>

#define BOT_ID 936291126133022730
#define LARGE_IMAGE_ASSET_KEY "app-icon"
#define LARGE_TEXT "Discord"

using namespace discord;

Core *core{};

namespace presence
{
    void launchDiscordIfNotRunning(std::future<int> &discordInstance)
    {
        // Discord not required as we do not want to launch discord
        Core::Create(BOT_ID, DiscordCreateFlags_NoRequireDiscord, &core);
        if (core == nullptr)
        {
            std::cout << "You do not have discord app opened! Opening Discord..." << std::endl;
            discordInstance = std::async(std::launch::async, []
                                         { return system("/Applications/Discord.app/Contents/MacOS/Discord"); });
            while (core == nullptr)
                Core::Create(BOT_ID, DiscordCreateFlags_NoRequireDiscord, &core);
        }
        else
            std::cout << "Discord instance detected! Displaying presence now..." << std::endl;
    }

    void discordSetup(std::future<int> &discordInstance)
    {
        launchDiscordIfNotRunning(discordInstance);
        sleep(5); // Give enough time for discord to register
        // Fix to presumably erased stack variable
        Core::Create(BOT_ID, DiscordCreateFlags_NoRequireDiscord, &core);
        std::cout << "If this message appears before the application is fully loaded, your presence may not work and you will have to restart..." << std::endl;

        Activity activity{};
        ActivityAssets *assets = &(activity.GetAssets());
        assets->SetLargeImage(LARGE_IMAGE_ASSET_KEY);
        assets->SetLargeText(LARGE_TEXT);

        // Initiate elapsed time
        using namespace std::chrono;
        ActivityTimestamps *timestamp = &(activity.GetTimestamps());
        timestamp->SetStart(system_clock::to_time_t(system_clock::now()));
        core->ActivityManager().UpdateActivity(activity, [](Result result) {});
    }

    void discordTick(bool &shouldTick)
    {
        // close application when discord closes
        if (core == nullptr || core->RunCallbacks() == Result::NotRunning)
            shouldTick = false;
    }
}
