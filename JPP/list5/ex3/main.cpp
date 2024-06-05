#include "philosopher.cpp"

int main() {
    int philosophers_count = 5;
    int meals_to_eat = 5;
    std::vector<std::shared_ptr<Fork>> forks;
    std::vector<std::shared_ptr<Philosopher>> philosophers;
    for(int i = 0; i < philosophers_count; i++) {
        forks.push_back(std::make_shared<Fork>());
    }
    philosophers.push_back(
        std::make_shared<Philosopher>(0, 
        meals_to_eat, 
        forks.at(forks.size() - 1), 
        forks.at(0)));
    for(int i = 1; i < philosophers_count - 1; i++) {
        philosophers.push_back(
            std::make_shared<Philosopher>(
                i,
                meals_to_eat,
                nullptr,
                forks.at(i)
            )
        );
    }
    philosophers.push_back(std::make_shared<Philosopher>(
        philosophers_count - 1,
        meals_to_eat,
        nullptr,
        nullptr
    ));

    for(auto p : philosophers) {
      p->AssignPhilosophersVector(philosophers);
    }

    std::promise<bool> all_finished_promise;
    std::shared_future<bool> all_finished(all_finished_promise.get_future());
    std::vector<std::future<bool>> philosophers_finished_futures;
    for(auto p : philosophers) {
        std::future<bool> res = p->StartProcess(all_finished);
        philosophers_finished_futures.push_back(std::move(res));
    }
    for(int i = 0; i < philosophers_finished_futures.size(); i++) {
        philosophers_finished_futures.at(i).get();
    }
    all_finished_promise.set_value(true);
    return 0;
}