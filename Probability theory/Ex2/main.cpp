#include <random>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <chrono>

#define K 50

std::mutex map_insertion_mutex;

/**
 * Insert U magnitude to the map for given n.
 *
 * @param n Number of urns.
 * @param no_of_urns_with_one_sphere Number of urns with one or more spheres inside.
 * @param magnitudes Map containing list of magnitudes found in each generated experiment.
 */
void check_u(int n,
             int no_of_urns_with_one_sphere,
             std::unordered_map<std::string, std::unordered_map<int, std::vector<int>>> &magnitudes
             ) {
    map_insertion_mutex.lock();
    magnitudes["u"][n].push_back(n - no_of_urns_with_one_sphere);
    map_insertion_mutex.unlock();
}

/**
 * Insert L magnitude into map for given n.
 *
 * @param n Number of urns.
 * @param max_num_of_spheres Max number of spheres in one urn.
 * @param magnitudes Map containing list of magnitudes found in each generated experiment.
 */
void check_l(int n,
             int max_num_of_spheres,
             std::unordered_map<std::string, std::unordered_map<int, std::vector<int>>> &magnitudes
             ) {
    map_insertion_mutex.lock();
    magnitudes["l"][n].push_back(max_num_of_spheres);
    map_insertion_mutex.unlock();
}

/**
 * Experiment. It throws spheres into random urns until there are at least two spheres in each urn.
 *
 * @param n Number of urns.
 * @param rand_num_gen Random number generator (Mersenne Twister).
 * @param magnitudes Map containing list of magnitudes found in each generated experiment.
 */
void spread_spheres_in_urns(
        int n,
        std::mt19937_64 rand_num_gen,
        std::unordered_map<std::string, std::unordered_map<int, std::vector<int>>> &magnitudes
        ) {
    std::vector<int> urns(n, 0);
    std::uniform_int_distribution<> dist(0, n-1);
    int no_of_urns_with_two_spheres = 0;
    int no_of_urns_with_one_sphere = 0;
    int number_of_throws = 0;
    int c;
    int max_num_of_spheres = 0;
    // throwing spheres into random urns until each one has two spheres inside
    while(no_of_urns_with_two_spheres < n) {
        int index = dist(rand_num_gen);
        urns.at(index) += 1;
        // update max number of spheres in urn if needed
        if(urns.at(index) > max_num_of_spheres)
            max_num_of_spheres = urns.at(index);
        number_of_throws++;
        if(urns.at(index) == 1) {
            no_of_urns_with_one_sphere++;
            if(no_of_urns_with_one_sphere == n) {
                // we got C magnitude
                map_insertion_mutex.lock();
                magnitudes["c"][n].push_back(number_of_throws);
                map_insertion_mutex.unlock();
                c = number_of_throws;
            }
        } else if(urns.at(index) == 2) {
            no_of_urns_with_two_spheres++;
            if(no_of_urns_with_two_spheres == 1) {
                // we got B magnitude
                map_insertion_mutex.lock();
                magnitudes["b"][n].push_back(number_of_throws);
                map_insertion_mutex.unlock();
            }
        }
        if(number_of_throws == n) {
            // fill U and L
            check_u(n, no_of_urns_with_one_sphere, magnitudes);
            check_l(n, max_num_of_spheres, magnitudes);
        }
    }
    // fill D and D-C after end of loop
    map_insertion_mutex.lock();
    magnitudes["d"][n].push_back(number_of_throws);
    magnitudes["d-c"][n].push_back(number_of_throws - c);
    map_insertion_mutex.unlock();
}

/**
 * This is a helper function for creating threads. It generates i experiments.
 *
 * @param n Number of urns.
 * @param magnitudes Map containing list of magnitudes found in each generated experiment.
 * @param i Amount of experiments to generate.
 */
void generate_i_experiments(
        int n,
        std::unordered_map<std::string, std::unordered_map<int, std::vector<int>>> &magnitudes,
        int i
        ) {
    std::random_device rd{};
    std::mt19937_64 rand_num_gen{rd()};
    for(int j=0; j < i; j++) {
        spread_spheres_in_urns(n, rand_num_gen, magnitudes);
    }
}

/**
 * First part of generating experiments. It creates threads and spreads generating experiments on each one.
 *
 * @param n Number of urns.
 * @param magnitudes Map containing list of magnitudes found in each generated experiment.
 */
void generate_experiment(
        int n,
        std::unordered_map<std::string, std::unordered_map<int, std::vector<int>>> &magnitudes
        ) {
    std::vector<std::thread> threads;
    int threads_count = std::thread::hardware_concurrency() > 0 ? std::thread::hardware_concurrency() : 1;
    int start = 0;
    int end = K / threads_count;
    int left = K - end * threads_count;
    while(start < K){
        end = K / threads_count;
        if(left > 0) {
            end++;
            left--;
        }
        threads.push_back(std::thread(generate_i_experiments, n, std::ref(magnitudes), end));
        start += end;
    }
    for(std::thread &th: threads) {
        th.join();
    }
}

// list containing strings for all basic magnitudes
std::string MAGNITUDES_LIST[] = {"c", "d", "u", "l", "b", "d-c"};

int main(int argc, char* argv[]) {
    // this variable maps magnitude -> map : (n -> list of values of chosen magnitude)
    std::unordered_map<std::string, std::unordered_map<int, std::vector<int>>> magnitudes;
    std::unordered_map<std::string, std::unordered_map<int, double>> mean_values;
    std::unordered_map<std::string, std::unordered_map<int, double>> mean_special_values;

    // file for results of the simulation
    std::fstream all_generated_values_file_;
    std::fstream mean_values_file_;

    // generate experiments
    auto start = std::chrono::high_resolution_clock::now();
    for(int n = 1000; n <= 100000; n += 1000) {
        generate_experiment(n, magnitudes);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "Execution time: " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() <<
        " miliseconds" << std::endl;

    // calculate mean values
    for(std::string magnitude: MAGNITUDES_LIST) {
        for(int n = 1000; n <= 100000; n += 1000) {
            double sum=0.0;
            for(int i=0; i < K; i++) {
                sum += magnitudes[magnitude][n].at(i);
            }
            mean_values[magnitude][n] = sum / K;
        }
    }

    // calculate special values based on previously found mean values
    for(int n = 1000; n <= 100000; n += 1000) {
        mean_special_values["b/n"][n] = mean_values["b"][n] / n;
        mean_special_values["b/sq(n)"][n] = mean_values["b"][n] / std::sqrt(n);
        mean_special_values["u/n"][n] = mean_values["u"][n] / n;
        mean_special_values["l/ln(n)"][n] = mean_values["l"][n] / std::log(n);
        mean_special_values["l/(ln(n))/ln(ln(n))"][n] = mean_values["l"][n] /
                (std::log(n) / std::log(std::log(n)));
        mean_special_values["l/ln(ln(n))"][n] = mean_values["l"][n] / std::log(std::log(n));
        mean_special_values["c/n"][n] = mean_values["c"][n] / n;
        mean_special_values["c/nln(n)"][n] = mean_values["c"][n] / (n * std::log(n));
        mean_special_values["c/n^2"][n] = mean_values["c"][n] / n / n;
        mean_special_values["d/n"][n] = mean_values["d"][n] / n;
        mean_special_values["d/nln(n)"][n] = mean_values["d"][n] / (n * std::log(n));
        mean_special_values["d/n^2"][n] = mean_values["d"][n] / n / n;
        mean_special_values["d-c/n"][n] = mean_values["d-c"][n] / n;
        mean_special_values["d-c/nln(n)"][n] = mean_values["d-c"][n] / (n * std::log(n));
        mean_special_values["d-c/nln(ln(n))"][n] = mean_values["d-c"][n] / (n * std::log(std::log(n)));
    }

    // save results of all simulations to file
    all_generated_values_file_.open("results.csv", std::ios::out | std::ios::trunc);
    if(all_generated_values_file_) {
        all_generated_values_file_ << "x;B;x;U;x;L;x;C;x;D;x;D-C\n";
        for(int n=1000; n <= 100000; n += 1000) {
            for(int i=0; i < K; i++) {
                all_generated_values_file_ << n << ";" << magnitudes["b"][n].at(i) << ";";
                all_generated_values_file_ << n << ";" << magnitudes["u"][n].at(i) << ";";
                all_generated_values_file_ << n << ";" << magnitudes["l"][n].at(i) << ";";
                all_generated_values_file_ << n << ";" << magnitudes["c"][n].at(i) << ";";
                all_generated_values_file_ << n << ";" << magnitudes["d"][n].at(i) << ";";
                all_generated_values_file_ << n << ";" << magnitudes["d-c"][n].at(i) << "\n";
            }
        }
        all_generated_values_file_.close();
    }

    // save average results to file
    mean_values_file_.open("mean_results.csv", std::ios::out | std::ios::trunc);
    if(mean_values_file_) {
        mean_values_file_ << "x;b(n);x;u(n);x;l(n);x;c(n);x;d(n);x;d-c(n);x;b/n;x;b/sq(n);x;u/n;x;l/ln(n);";
        mean_values_file_ << "x;l/(ln(n))/ln(ln(n));x;l/ln(ln(n));x;c/n;x;c/nln(n);x;c/n^2;x;d/n;x;d/nln(n);";
        mean_values_file_ << "x;d/n^2;x;d-c/n;x;d-c/nln(n);x;d-c/nln(ln(n))\n";
        for(int n = 1000; n <= 100000; n += 1000) {
            mean_values_file_ << n << ";" << mean_values["b"][n] << ";";
            mean_values_file_ << n << ";" << mean_values["u"][n] << ";";
            mean_values_file_ << n << ";" << mean_values["l"][n] << ";";
            mean_values_file_ << n << ";" << mean_values["c"][n] << ";";
            mean_values_file_ << n << ";" << mean_values["d"][n] << ";";
            mean_values_file_ << n << ";" << mean_values["d-c"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["b/n"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["b/sq(n)"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["u/n"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["l/ln(n)"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["l/(ln(n))/ln(ln(n))"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["l/ln(ln(n))"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["c/n"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["c/nln(n)"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["c/n^2"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["d/n"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["d/nln(n)"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["d/n^2"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["d-c/n"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["d-c/nln(n)"][n] << ";";
            mean_values_file_ << n << ";" << mean_special_values["d-c/nln(ln(n))"][n] << "\n";
        }
        mean_values_file_.close();
    }
}

