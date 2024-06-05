#include <iostream>
#include <future>
#include <memory>
#include <vector>
#include <mutex>
#include <atomic>
#include <random>
#include "fork.cpp"

typedef struct {
    bool left;
    std::promise<std::shared_ptr<Fork>> *fork_promise;
} ForkRequestStruct;

class Philosopher {
    int id_;
    int meals_count_;
    std::shared_ptr<Fork> left_fork_;
    std::shared_ptr<Fork> right_fork_;
    std::vector<std::shared_ptr<Philosopher>> philosophers_;

    std::atomic_bool request_pending_;
    std::promise<ForkRequestStruct> fork_request_promise_;
    std::future<ForkRequestStruct> fork_request_;

    std::future<std::shared_ptr<Fork>> get_left_fork_;
    std::future<std::shared_ptr<Fork>> get_right_fork_;

    std::mt19937_64 rand_gen{std::random_device{}()};

    std::promise<bool> finished_promise;

    std::shared_future<bool> main_finished_;

    void run();
public:
    Philosopher(int id, 
                int meals_count, 
                std::shared_ptr<Fork> left_fork,
                std::shared_ptr<Fork> right_fork,
                std::vector<std::shared_ptr<Philosopher>> &philosophers);
    
    std::future<bool> StartProcess(std::shared_future<bool> main_finished);

    void RequestFork(ForkRequestStruct request);
};
