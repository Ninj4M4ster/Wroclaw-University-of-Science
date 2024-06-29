#include "philosopher.hpp"
#include <chrono>
#include <thread>
#include "timer.cpp"

Philosopher::Philosopher(int id,
                         int meals_count,
                         std::shared_ptr<Fork> left_fork,
                         std::shared_ptr<Fork> right_fork) {
  id_ = id;
  meals_count_ = meals_count;
  left_fork_ = left_fork;
  right_fork_ = right_fork;
  fork_request_ = fork_request_promise_.get_future();
}

/**
 * Pass vector containing all active philosophers.
 * @param philosophers
 */
void Philosopher::AssignPhilosophersVector(std::vector<std::shared_ptr<Philosopher>> philosophers) {
  philosophers_ = philosophers;
}

/**
 * Start philosopher process and pass a a future object in return, that can be used to
 * join the philosopher process.
 *
 * @param main_finished Future object signaling that all philosophers finished eating.
 * @return Future object.
 */
std::future<bool> Philosopher::StartProcess(std::shared_future<bool> main_finished) {
  main_finished_ = main_finished;
  std::future<bool> finished = finished_promise.get_future();
  std::thread([this]() { run(); }).detach();
  return std::move(finished);
}

/**
 * Philosopher main loop.
 */
void Philosopher::run() {
  std::uniform_int_distribution<int> dist{0, 1000};
  bool is_thinking = false;
  int left_id = id_ - 1 < 0 ? philosophers_.size() - 1 : id_ - 1;
  int right_id = id_ + 1 == philosophers_.size() ? 0 : id_ + 1;
  int ate_meals = 0;
  std::shared_ptr<Timer> thinking_timer;

  while (ate_meals < meals_count_) {
    if (is_thinking) {
      std::cout << "Philosopher " << id_ << " starts_thinking\n";
      while (is_thinking) {
        if (fork_request_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
          ForkRequestStruct asking_phil = fork_request_.get();
          fork_request_promise_ = std::promise<ForkRequestStruct>();
          fork_request_ = fork_request_promise_.get_future();
          request_pending_ = false;
          if (asking_phil.left) {
            received_left_request_ = std::move(asking_phil);
            if(left_fork_) {
              left_fork_->ChangeState(true);
              received_left_request_.fork_promise.set_value(left_fork_);
              left_fork_ = nullptr;
            } else {
              received_left_request_.fork_promise.set_value(nullptr);
            }
          } else {
            received_right_request_ = std::move(asking_phil);
            if (right_fork_) {
              right_fork_->ChangeState(true);
              received_right_request_.fork_promise.set_value(right_fork_);
              right_fork_ = nullptr;
            } else {
              received_right_request_.fork_promise.set_value(nullptr);
            }
          }
        }
        if (thinking_timer->TimerFinished()) {
          is_thinking = false;
        }
      }
      std::cout << "Philosopher " << id_ << " stopped thinking\n";
    }
    bool left_fork_requested = false;
    bool right_fork_requested = false;
    while (left_fork_ == nullptr || right_fork_ == nullptr) {
      // send request for left fork
      if (left_fork_ == nullptr && !left_fork_requested) {
        left_fork_promise_ = std::promise<std::shared_ptr<Fork>>();
        get_left_fork_ = left_fork_promise_.get_future();
        ForkRequestStruct req = {false, std::move(left_fork_promise_)};
        philosophers_.at(left_id)->RequestFork(std::move(req));
        left_fork_requested = true;
      }
      // send request for right fork
      if (right_fork_ == nullptr && !right_fork_requested) {
        right_fork_promise_ = std::promise<std::shared_ptr<Fork>>();
        get_right_fork_ = right_fork_promise_.get_future();
        ForkRequestStruct req = {true, std::move(right_fork_promise_)};
        philosophers_.at(right_id)->RequestFork(std::move(req));
        right_fork_requested = true;
      }

      // accept a fork request from different philosopher
      if (fork_request_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        ForkRequestStruct asking_phil = fork_request_.get();
        fork_request_promise_ = std::promise<ForkRequestStruct>();
        fork_request_ = fork_request_promise_.get_future();
        request_pending_ = false;
        if (asking_phil.left) {
          received_left_request_ = std::move(asking_phil);
          if(left_fork_) {
            if (!left_fork_->IsClean()) {
              left_fork_->ChangeState(true);
              received_left_request_.fork_promise.set_value(left_fork_);
              left_fork_ = nullptr;
            } else {
              received_left_request_.fork_promise.set_value(nullptr);
            }
          } else {
            received_left_request_.fork_promise.set_value(nullptr);
          }
        } else {
          received_right_request_ = std::move(asking_phil);
          if (right_fork_) {
            if (!right_fork_->IsClean()) {
              right_fork_->ChangeState(true);
              received_right_request_.fork_promise.set_value(right_fork_);
              right_fork_ = nullptr;
            } else {
              received_right_request_.fork_promise.set_value(nullptr);
            }
          } else {
            received_right_request_.fork_promise.set_value(nullptr);
          }
        }
      }

      // receive right fork
      if (right_fork_requested && get_right_fork_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        right_fork_ = get_right_fork_.get();
        right_fork_requested = false;
      }

      // receive left fork
      if (left_fork_requested && get_left_fork_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
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
    for (int i = 0; i < 2; i++) {
      if (fork_request_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        ForkRequestStruct asking_phil = fork_request_.get();
        fork_request_promise_ = std::promise<ForkRequestStruct>();
        fork_request_ = fork_request_promise_.get_future();
        request_pending_ = false;
        if (asking_phil.left) {
          received_left_request_ = std::move(asking_phil);
          if(left_fork_) {
            left_fork_->ChangeState(true);
            received_left_request_.fork_promise.set_value(left_fork_);
            left_fork_ = nullptr;
          } else {
            received_left_request_.fork_promise.set_value(nullptr);
          }
        } else {
          received_right_request_ = std::move(asking_phil);
          if (right_fork_) {
            right_fork_->ChangeState(true);
            received_right_request_.fork_promise.set_value(right_fork_);
            right_fork_ = nullptr;
          } else {
            received_right_request_.fork_promise.set_value(nullptr);
          }
        }
      }
    }
    if (meals_count_ > ate_meals) {
      // create thinking timer
      is_thinking = true;
      thinking_timer = std::make_shared<Timer>(dist(rand_gen));
    } else {
      // signal that philosopher ended eating and give out forks while it is possible
      finished_promise.set_value(true);
      while (left_fork_ || right_fork_) {
        if (fork_request_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
          ForkRequestStruct asking_phil = fork_request_.get();
          fork_request_promise_ = std::promise<ForkRequestStruct>();
          fork_request_ = fork_request_promise_.get_future();
          request_pending_ = false;
          if (asking_phil.left) {
            received_left_request_ = std::move(asking_phil);
            if(left_fork_) {
              left_fork_->ChangeState(true);
              received_left_request_.fork_promise.set_value(left_fork_);
              left_fork_ = nullptr;
            } else {
              received_left_request_.fork_promise.set_value(nullptr);
            }
          } else {
            received_right_request_ = std::move(asking_phil);
            if (right_fork_) {
              right_fork_->ChangeState(true);
              received_right_request_.fork_promise.set_value(right_fork_);
              right_fork_ = nullptr;
            } else {
              received_right_request_.fork_promise.set_value(nullptr);
            }
          }
        }
        if (main_finished_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
          return;
        }
      }
    }
  }
}

/**
 * Send a fork request to the philosopher.
 * @param request
 */
void Philosopher::RequestFork(ForkRequestStruct request) {
  request_mutex.lock();
  if (request_pending_) {
    if(request.left) {
      received_left_request_ = std::move(request);
      received_left_request_.fork_promise.set_value(nullptr);
    } else {
      received_right_request_ = std::move(request);
      received_right_request_.fork_promise.set_value(nullptr);
    }
  } else {
    request_pending_ = true;
    fork_request_promise_.set_value(std::move(request));
  }
  request_mutex.unlock();
}