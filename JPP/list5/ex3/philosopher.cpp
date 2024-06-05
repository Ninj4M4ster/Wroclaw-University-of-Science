#include "philosopher.hpp"
#include <chrono>
#include <thread>
#include "timer.cpp"

Philosopher::Philosopher(int id, 
                int meals_count, 
                std::shared_ptr<Fork> left_fork,
                std::shared_ptr<Fork> right_fork,
                std::vector<std::shared_ptr<Philosopher>> &philosophers) {
    id_ = id;
    meals_count_ = meals_count;
    left_fork_ = left_fork;
    right_fork_ = right_fork;
    philosophers_ = philosophers;
    fork_request_ = fork_request_promise_.get_future();
}

std::future<bool> Philosopher::StartProcess(std::shared_future<bool> main_finished) {
    main_finished_ = main_finished;
    std::future<bool> finished = finished_promise.get_future();
    std::thread([this]() {run();}).detach();
    return finished;
}

void Philosopher::run() {
    std::uniform_int_distribution<int> dist{0, 5000};
    bool is_thinking = false;
    int left_id = id_ - 1 < 0 ? philosophers_.size() - 1 : id_ - 1;
    int right_id = id_ + 1 == philosophers_.size() ? 0 : id_ + 1;
    int ate_meals = 0;
    std::shared_ptr<Timer> thinking_timer;
    
    while(ate_meals < meals_count_) {
        if(is_thinking) {
            std::cout << "Philosopher " << id_ << " starts_thinking\n"; 
            while(is_thinking) {
                if(fork_request_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                    ForkRequestStruct asking_phil = fork_request_.get();
                    fork_request_promise_ = std::promise<ForkRequestStruct>();
                    fork_request_ = fork_request_promise_.get_future();
                    request_pending_ = false;
                    if(asking_phil.left && left_fork_) {
                        left_fork_->ChangeState(true);
                        asking_phil.fork_promise->set_value(left_fork_);
                        left_fork_ = nullptr;
                    } else if(right_fork_) {
                        right_fork_->ChangeState(true);
                        asking_phil.fork_promise->set_value(right_fork_);
                        right_fork_ = nullptr;
                    }
                }
                if(thinking_timer->TimerFinished()) {
                    is_thinking = false;
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
                ForkRequestStruct req = {false, &fork_promise};
                philosophers_.at(left_id)->RequestFork(req);
                left_fork_requested = true;
            }
            if(right_fork_ == nullptr && !right_fork_requested) {
                std::promise<std::shared_ptr<Fork>> fork_promise;
                get_right_fork_ = fork_promise.get_future();
                ForkRequestStruct req = {true, &fork_promise};
                philosophers_.at(right_id)->RequestFork(req);
                right_fork_requested = true;
            }

            if(fork_request_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                ForkRequestStruct asking_phil = fork_request_.get();
                fork_request_promise_ = std::promise<ForkRequestStruct>();
                fork_request_ = fork_request_promise_.get_future();
                request_pending_ = false;
                if(asking_phil.left && left_fork_) {
                    if(!left_fork_->IsClean()) {
                        left_fork_->ChangeState(true);
                        asking_phil.fork_promise->set_value(left_fork_);
                        left_fork_ = nullptr;
                    } else {
                        asking_phil.fork_promise->set_value(nullptr);
                    }
                } else if(right_fork_) {
                    if(!right_fork_->IsClean()) {
                        right_fork_->ChangeState(true);
                        asking_phil.fork_promise->set_value(right_fork_);
                        right_fork_ = nullptr;
                    } else {
                        asking_phil.fork_promise->set_value(nullptr);
                    }
                } else {
                    throw std::runtime_error("Asked for fork but does not have one");
                }
            }

            if(right_fork_requested && get_right_fork_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                right_fork_ = get_right_fork_.get();
                right_fork_requested = false;
            }

            if(left_fork_requested && get_left_fork_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                left_fork_ = get_left_fork_.get();
                left_fork_requested = false;
            }
        }
        left_fork_->ChangeState(false);
        right_fork_->ChangeState(false);
        // eat
        std::cout << "Philosopher " << id_ << " starts eating\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(rand_gen)));

        ate_meals++;
        std::cout << "Philosopher " << id_ << " ate " << ate_meals << " meals\n";
        // give out forks
        for(int i = 0; i < 2; i++) {
            if(fork_request_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                    ForkRequestStruct asking_phil = fork_request_.get();
                    fork_request_promise_ = std::promise<ForkRequestStruct>();
                    fork_request_ = fork_request_promise_.get_future();
                    request_pending_ = false;
                    if(asking_phil.left && left_fork_) {
                        left_fork_->ChangeState(true);
                        asking_phil.fork_promise->set_value(left_fork_);
                        left_fork_ = nullptr;
                    } else if(right_fork_) {
                        right_fork_->ChangeState(true);
                        asking_phil.fork_promise->set_value(right_fork_);
                        right_fork_ = nullptr;
                    }
                }
        }
        if(meals_count_ > ate_meals) {
            // create thinking timer
            is_thinking = true;
            thinking_timer = std::make_shared<Timer>(dist(rand_gen));
        } else {
            finished_promise.set_value(true);
            while(left_fork_ || right_fork_) {
                if(fork_request_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                    ForkRequestStruct asking_phil = fork_request_.get();
                    fork_request_promise_ = std::promise<ForkRequestStruct>();
                    fork_request_ = fork_request_promise_.get_future();
                    request_pending_ = false;
                    if(asking_phil.left && left_fork_) {
                        left_fork_->ChangeState(true);
                        asking_phil.fork_promise->set_value(left_fork_);
                        left_fork_ = nullptr;
                    } else if(right_fork_) {
                        right_fork_->ChangeState(true);
                        asking_phil.fork_promise->set_value(right_fork_);
                        right_fork_ = nullptr;
                    }
                }
                if(main_finished_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                    return;
                }
            }
        }
    }
}

void Philosopher::RequestFork(ForkRequestStruct request) {
    if(request_pending_) {
        request.fork_promise->set_value(nullptr);
    } else {
        request_pending_ = true;
        fork_request_promise_.set_value(request);
    }
}