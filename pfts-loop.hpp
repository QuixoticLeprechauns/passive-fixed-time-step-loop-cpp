#ifndef PFTSLOOP_FILE
#define PFTSLOOP_FILE

#include <chrono>
#include <thread>

/// @brief Runs a process in a passive fixed time step loop.
/// @param process A function returning int without arguments. Return 0 to exit loop. 
/// @param MaxSleepTime The target fixed time step, in miliseconds, for this loop.
/// @param MinSleepTime The minimum period of time, in miliseconds, this loop will sleep between cycles.
inline void pfts_loop(int (*process) (void), int MaxSleepTime = 16, int MinSleepTime = 1)
{
    int retval;
    do
    {
        std::thread sleep([&](){std::this_thread::sleep_for(std::chrono::milliseconds(MaxSleepTime));});
        retval = process();
        std::this_thread::sleep_for(std::chrono::milliseconds(MinSleepTime));
        sleep.join();
    } while (retval != 0);
}

#endif