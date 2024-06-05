#include "philosopher.hpp"
#include <chrono>

Philosopher::Philosopher(int id, 
                int meals_count, 
                std::shared_ptr<Fork> left_fork,
                std::shared_ptr<Fork> right_fork,
                std::vector<std::shared_ptr<Philosopher>> philosophers) {
    id_ = id;
    meals_count_ = meals_count;
    left_fork_ = left_fork;
    right_fork_ = right_fork;
    philosophers_ = philosophers;
    fork_request_ = fork_request_promise_.get_future();
}

void Philosopher::run() {
    bool is_thinking = false;
    int left_id = id_ - 1 < 0 ? philosophers_.size() - 1 : id_ - 1;
    int right_id = id_ + 1 == philosophers_.size() ? 0 : id_ + 1;
    int ate_meals = 0;
    std::future<> left_fork_request = nullptr;
    // TODO(Jakub Drzewiecki): Use mutex
    while(ate_meals < meals_count_) {
        if(is_thinking) {
            std::cout << "Philosopher " << id_ << " starts_thinking\n"; 
            while(is_thinking) {
                // TODO(Jakub Drzewiecki): Add timer for stopping thinking
                if(fork_request_.wait_for(std::chrono::seconds(0))) {
                    ForkRequestStruct asking_phil = fork_request_.get();
                    fork_request_promise_ = std::promise<ForkRequestStruct>();
                    fork_request_ = fork_request_promise_.get_future();
                    if(asking_phil.left && left_fork_) {
                        left_fork_->ChangeState(true);
                        asking_phil.fork_promise.set_value(left_fork_);
                        left_fork_ = nullptr;
                    } else if(right_fork_) {
                        right_fork_->ChangeState(true);
                        asking_phil.fork_promise.set_value(right_fork_);
                        right_fork_ = nullptr;
                    }
                }
            }
            std::cout << "Philosopher " << id_ << " stopped thinking\n";
        }
        bool left_fork_requested = false;
        bool right_fork_requested = false;
        while(left_fork_ == nullptr || right_fork_ == nullptr) {
            if(left_fork_ == nullptr && !left_fork_requested) {
                std::promise<std::shared_ptr<Fork>> fork_promise;
                get_left_fork_ = fork_promise.get_future();
                ForkRequestStruct req = {false, fork_promise};
                philosophers_.at(left_id)->RequestFork(req);
            }
            if(right_fork_ == nullptr && !right_fork_requested) {
                std::promise<std::shared_ptr<Fork>> fork_promise;
                get_right_fork_ = fork_promise.get_future();
                ForkRequestStruct req = {true, fork_promise};
                philosophers_.at(right_id)->RequestFork(req);
            }

            if(fork_request_.wait_for(std::chrono::seconds(0))) {
                ForkRequestStruct asking_phil = fork_request_.get();
                fork_request_promise_ = std::promise<ForkRequestStruct>();
                fork_request_ = fork_request_promise_.get_future();
                if(asking_phil.left && left_fork_) {
                    if(!left_fork_->IsClean()) {
                        left_fork_->ChangeState(true);
                        asking_phil.fork_promise.set_value(left_fork_);
                        left_fork_ = nullptr;
                    } else {
                        asking_phil.fork_promise.set_value(nullptr);
                    }
                } else if(right_fork_) {
                    if(!right_fork_->IsClean()) {
                        right_fork_->ChangeState(true);
                        asking_phil.fork_promise.set_value(right_fork_);
                        right_fork_ = nullptr;
                    } else {
                        asking_phil.fork_promise.set_value(nullptr);
                    }
                } else {
                    throw std::runtime_error("Asked for fork but does not have one");
                }
            }

            if(right_fork_requested && get_right_fork_.wait_for(std::chrono::seconds(0))) {
                right_fork_ = get_right_fork_.get();
                right_fork_requested = false;
            }

            if(left_fork_requested && get_left_fork_.wait_for(std::chrono::seconds(0))) {
                left_fork_ = get_left_fork_.get();
                left_fork_requested = false;
            }
        }
        left_fork_->ChangeState(false);
        right_fork_->ChangeState(false);
        // eat
        std::cout << "Philosopher " << id_ << " starts eating\n";

        ate_meals++;
        std::cout << "Philosopher " << id_ << " ate " << ate_meals << " meals\n";
        // give out forks
        for(int i = 0; i < 2; i++) {

        }
        if(meals_count_ > ate_meals) {
            // create thinking timer
            is_thinking = true;
        } else {
            
        }
    }
}

void Philosopher::RequestFork(ForkRequestStruct request) {
    std::lock_guard<std::mutex> lock_guard(access_mutex_);
    if(request_pending_) {
        request.fork_promise.set_value(nullptr);
    } else {
        request_pending_ = true;
        fork_request_promise_.set_value(request);
    }
}