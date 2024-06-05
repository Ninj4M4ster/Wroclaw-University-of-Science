#include <iostream>
#include <chrono>
#include <future>
#include <thread>

class Timer {
    std::future<bool> result;
public:
    Timer(int miliseconds);
    bool TimerFinished();
};
