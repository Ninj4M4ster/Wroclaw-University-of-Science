#include "timer.hpp"

Timer::Timer(int miliseconds) {
    std::promise<bool> finished_promise;
    result = finished_promise.get_future();
    std::thread([&finished_promise, miliseconds]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
        finished_promise.set_value(true);
    }).detach();
}

bool Timer::TimerFinished() {
    if(result.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        return true;
    }
    return false;
}