#include <iostream>
#include <future>
#include <memory>
#include <vector>
#include <mutex>
#include "fork.hpp"

typedef struct {
    bool left;
    std::promise<std::shared_ptr<Fork>> fork_promise;
} ForkRequestStruct;

class Philosopher {
    int id_;
    int meals_count_;
    std::shared_ptr<Fork> left_fork_;
    std::shared_ptr<Fork> right_fork_;
    std::vector<std::shared_ptr<Philosopher>> philosophers_;

    bool request_pending_ = false;
    std::promise<ForkRequestStruct> fork_request_promise_;
    std::future<ForkRequestStruct> fork_request_;

    std::future<std::shared_ptr<Fork>> get_left_fork_;
    std::future<std::shared_ptr<Fork>> get_right_fork_;

    std::mutex access_mutex_;

public:
    Philosopher(int id, 
                int meals_count, 
                std::shared_ptr<Fork> left_fork,
                std::shared_ptr<Fork> right_fork,
                std::vector<std::shared_ptr<Philosopher>> philosophers);
    void run();

    void RequestFork(ForkRequestStruct request);
};
