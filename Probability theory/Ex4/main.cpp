#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <fstream>

std::mutex map_insertion_mutex;

/**
 * Function for generating clique graph.
 *
 * @param n Number of vertices.
 * @return Links list of clique graph.
 */
std::vector<std::vector<int>> generate_clique_graph(int n) {
    std::vector<std::vector<int>> graph(n);
    for(int i=0; i < n; i++) {
        for(int j=0; j < n; j++) {
            if(i != j)
                graph.at(i).push_back(j);
        }
    }
    return graph;
}

/**
 * Function for generating path graph.
 *
 * @param n Number of vertices.
 * @return Links list of path graph.
 */
std::vector<std::vector<int>> generate_path_graph(int n) {
    std::vector<std::vector<int>> graph(n);
    for(int i=0; i < n; i++) {
        if(i != n-1)
            graph.at(i).push_back(i+1);
        if(i > 0)
            graph.at(i).push_back(i-1);
    }
    return graph;
}

/**
 * Function for generating full binary tree graph.
 *
 * @param n Number of vertices.
 * @return Links list of full binary tree graph.
 */
std::vector<std::vector<int>> generate_full_btree(int n) {
    std::vector<std::vector<int>> graph(n);
    int current_vertex = 0;
    int last_linked_value = 1;
    while(last_linked_value < n) {
        graph.at(current_vertex).push_back(last_linked_value);
        graph.at(last_linked_value).push_back(current_vertex);
        last_linked_value++;
        if(last_linked_value == n)
            break;
        graph.at(current_vertex).push_back(last_linked_value);
        graph.at(last_linked_value).push_back(current_vertex);
        last_linked_value++;
        current_vertex++;
    }
    return graph;
}

/**
 * Function for generating lollipop graph.
 *
 * @param n Number of vertices.
 * @return Links list of lollipop graph.
 */
std::vector<std::vector<int>> generate_lollipop_graph(int n) {
    int size_of_clique = 2 * n / 3;
    int last_clique_vertex = size_of_clique - 1;
    std::vector<std::vector<int>> graph(n);
    for(int i=0; i < size_of_clique; i++) {
        for(int j=0; j < size_of_clique; j++) {
            if(i != j)
                graph.at(i).push_back(j);
        }
    }
    for(int i = last_clique_vertex; i < n; i++) {
        if(i != n-1)
            graph.at(i).push_back(i+1);
        if(i != last_clique_vertex)
            graph.at(i).push_back(i-1);
    }
    return graph;
}

/**
 * Function for generating a step of random walk on given graph.
 *
 * @param graph Links list of a graph.
 * @param current_vertex Current position on the graph.
 * @param rand_gen Random numbers generator.
 * @return Vertex number after one step of random walk;
 */
int random_walk_step(const std::vector<std::vector<int>> &graph, int current_vertex, std::mt19937_64 &rand_gen) {
    std::uniform_int_distribution<> dist(0, (int)graph.at(current_vertex).size() - 1);
    int chosen_index = dist(rand_gen);
    return graph.at(current_vertex).at(chosen_index);
}

/**
 * Function for checking if all vertices have been visited.
 *
 * @param vertex_visit_counter List with numbers of visits in particular vertices.
 * @return Have all vertices been visited?
 */
bool check_vertex_visits(std::vector<unsigned long long int> vertex_visit_counter) {
    return std::all_of(vertex_visit_counter.begin(),
                       vertex_visit_counter.end(),
                       [](unsigned long long int & counter) {
        return counter > 0;
    });
}

/**
 * Function for generating one experiment. It does a random walk on a graph until all vertices are visited.
 *
 * @param graph Links list of a graph.
 * @param current_vertex Starting vertex.
 * @param rand_gen Random numbers generator.
 * @return Number of random walks done in experiment.
 */
unsigned long long int generate_experiment(const std::vector<std::vector<int>> &graph, int current_vertex, std::mt19937_64 &rand_gen) {
    std::vector<unsigned long long int> vertex_visit_counter(graph.size(), 0);
    unsigned long long int counter = 0;
    vertex_visit_counter.at(current_vertex)++;  // not sure if starting vertex is taken as visited
    while(!check_vertex_visits(vertex_visit_counter)) {
        current_vertex = random_walk_step(graph, current_vertex, rand_gen);
        vertex_visit_counter.at(current_vertex)++;
        if(counter + 1 < counter)
            std::cout << "numerics limit reached" << std::endl;
        counter++;
    }
    return counter;
}

/**
 * Helper function for generating experiments for all types of graphs.
 *
 * @param results Unordered map for results.
 * @param n Number of vertices.
 * @param rand_gen Random numbers generator.
 * @param dist Uniform int distribution for choosing first vertex on clique graph.
 * @param lollipop_dist Uniform int distribution for choosing first vertex on lollipop graph.
 * @param end Number of times to generate experiments.
 * @param clique_graph Clique graph.
 * @param path_graph Path graph.
 * @param btree_graph Full binary tree graph.
 * @param lollipop_graph Lollipop graph.
 */
void generate_i_experiments(std::unordered_map<std::string, std::unordered_map<int, std::vector<unsigned long long int>>> &results,
                            int n,
                            std::mt19937_64 &rand_gen,
                            std::uniform_int_distribution<> &dist,
                            std::uniform_int_distribution<> &lollipop_dist,
                            int end,
                            const std::vector<std::vector<int>> &clique_graph,
                            const std::vector<std::vector<int>> &path_graph,
                            const std::vector<std::vector<int>> &btree_graph,
                            const std::vector<std::vector<int>> &lollipop_graph) {
    for(int k=0; k < end; k++) {
        unsigned long long int time = generate_experiment(clique_graph, dist(rand_gen), rand_gen);
        map_insertion_mutex.lock();
        results["clique"][n].push_back(time);
        map_insertion_mutex.unlock();

        time = generate_experiment(path_graph, n/2, rand_gen);
        map_insertion_mutex.lock();
        results["path"][n].push_back(time);
        map_insertion_mutex.unlock();

        time = generate_experiment(path_graph, 0, rand_gen);
        map_insertion_mutex.lock();
        results["path_end"][n].push_back(time);
        map_insertion_mutex.unlock();

        time = generate_experiment(btree_graph, 0, rand_gen);
        map_insertion_mutex.lock();
        results["btree"][n].push_back(time);
        map_insertion_mutex.unlock();

        time = generate_experiment(lollipop_graph, lollipop_dist(rand_gen), rand_gen);
        map_insertion_mutex.lock();
        results["lollipop"][n].push_back(time);
        map_insertion_mutex.unlock();
    }
}

/**
 * Function for inserting results to a file.
 *
 * @param file_name File name for results.
 * @param results Unordered map with results.
 * @param header Name of the graph.
 */
void drop_results_to_file(
        const char* file_name,
        std::unordered_map<std::string, std::unordered_map<int, std::vector<unsigned long long int>>> &results,
        const char* header) {
    std::fstream file;
    file.open(file_name, std::fstream::out);
    file << "x;" << header << std::endl;
    for(int n=100; n <= 2000; n+=50) {
        for(int k=0; k < 16; k++) {
            file << n << ";" << results[header][n].at(k) << std::endl;
        }
    }
    file.close();
}

/**
 * Function for inserting means to a file.
 *
 * @param file_name File name for means.
 * @param means Unordered map with means.
 * @param header Name of the graph.
 */
void drop_mean_to_file(const char* file_name,
                       std::unordered_map<std::string, std::unordered_map<int, long double>> means,
                       const char* header) {
    std::fstream file;
    file.open(file_name, std::fstream::out);
    file << "x;" << header << std::endl;
    for(int n=100; n <= 2000; n+=50) {
        file << n << ";" << means[header][n] << std::endl;
    }
    file.close();
}

/**
 * Function for inserting calculations of asymptotics to a file.
 *
 * @param file_name File name for calculations.
 * @param asymptotics Unordered map with calculations.
 * @param header Name of the graph.
 */
void drop_asymptotics_to_file(
        const char* file_name,
        std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<int, long double>>> &asymptotics,
        const char* header) {
    std::fstream file;
    file.open(file_name, std::fstream::out);
    file << "x;n;x;nlogn;x;n^2;x;n^3" << std::endl;
    for(int n=100; n <= 2000; n+=50) {
        file << n << ";" << asymptotics[header]["n"][n] << ";";
        file << n << ";" << asymptotics[header]["nlogn"][n] << ";";
        file << n << ";" << asymptotics[header]["nn"][n] << ";";
        file << n << ";" << asymptotics[header]["nnn"][n] << std::endl;
    }
    file.close();
}


int main() {
    std::random_device rd{};
    std::mt19937_64 rand_gen{rd()};

    // available keys: clique, path, path_end, btree, lollipop
    std::unordered_map<std::string, std::unordered_map<int, std::vector<unsigned long long int>>> results;

    // experiments
    int K = 16;

    for(int n=100; n <= 2000; n += 50) {
        std::cout << "Generating experiments for n = " << n << std::endl;
        std::uniform_int_distribution<> dist(0, n - 1);
        std::uniform_int_distribution<> lollipop_dist(0, (2 * n / 3) - 1);
        auto clique = generate_clique_graph(n);
        auto path = generate_path_graph(n);
        auto btree = generate_full_btree(n);
        auto lollipop = generate_lollipop_graph(n);

        std::vector<std::thread> threads;
        int threads_count = std::thread::hardware_concurrency() > 0 ? (int)std::thread::hardware_concurrency() : 1;
        int start = 0;
        int end = K / threads_count;
        int left = K - end * threads_count;
        while(start < K){
            end = K / threads_count;
            if(left > 0) {
                end++;
                left--;
            }
            threads.emplace_back(generate_i_experiments,
                                          std::ref(results),
                                          n,
                                          std::ref(rand_gen),
                                          std::ref(dist),
                                          std::ref(lollipop_dist),
                                          end,
                                          std::ref(clique),
                                          std::ref(path),
                                          std::ref(btree),
                                          std::ref(lollipop));
            start += end;
        }
        for(std::thread &th: threads) {
            th.join();
        }
    }


    // calculating means
    std::unordered_map<std::string, std::unordered_map<int, long double>> means;

    for(int n = 100; n <= 2000; n+= 50) {
        unsigned long long int sum_clique = 0;
        unsigned long long int sum_path = 0;
        unsigned long long int sum_path_end = 0;
        unsigned long long int sum_btree = 0;
        unsigned long long int sum_lollipop = 0;
        for(int k=0; k < K; k++) {
            sum_clique += results["clique"][n].at(k);
            sum_path += results["path"][n].at(k);
            sum_path_end += results["path_end"][n].at(k);
            sum_btree += results["btree"][n].at(k);
            sum_lollipop += results["lollipop"][n].at(k);
        }
        means["clique"][n] = (double)sum_clique / (double)K;
        means["path"][n] = (double)sum_path / (double)K;
        means["path_end"][n] = (double)sum_path_end / (double)K;
        means["btree"][n] = (double)sum_btree / (double)K;
        means["lollipop"][n] = (double)sum_lollipop / (double)K;
    }

    // finding big O notation
    std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<int, long double>>> asymptotics;

    for(int n = 100; n <= 2000; n+=50) {
        asymptotics["clique"]["n"][n] = means["clique"][n] / (double)n;
        asymptotics["clique"]["nlogn"][n] = means["clique"][n] / ((double)n * std::log(n));
        asymptotics["clique"]["nn"][n] = means["clique"][n] / (double)(n * n);
        asymptotics["clique"]["nnn"][n] = means["clique"][n] / (double)(n * n * n);

        asymptotics["path"]["n"][n] = means["path"][n] / (double)n;
        asymptotics["path"]["nlogn"][n] = means["path"][n] / ((double)n * std::log(n));
        asymptotics["path"]["nn"][n] = means["path"][n] / (double)(n * n);
        asymptotics["path"]["nnn"][n] = means["path"][n] / (double)(n * n * n);

        asymptotics["path_end"]["n"][n] = means["path_end"][n] / (double)n;
        asymptotics["path_end"]["nlogn"][n] = means["path_end"][n] / ((double)n * std::log(n));
        asymptotics["path_end"]["nn"][n] = means["path_end"][n] / (double)(n * n);
        asymptotics["path_end"]["nnn"][n] = means["path_end"][n] / (double)(n * n * n);

        asymptotics["btree"]["n"][n] = means["btree"][n] / (double)n;
        asymptotics["btree"]["nlogn"][n] = means["btree"][n] / ((double)n * std::log(n));
        asymptotics["btree"]["nn"][n] = means["btree"][n] / (double)(n * n);
        asymptotics["btree"]["nnn"][n] = means["btree"][n] / (double)(n * n * n);

        asymptotics["lollipop"]["n"][n] = means["lollipop"][n] / (double)n;
        asymptotics["lollipop"]["nlogn"][n] = means["lollipop"][n] / ((double)n * std::log(n));
        asymptotics["lollipop"]["nn"][n] = means["lollipop"][n] / (double)(n * n);
        asymptotics["lollipop"]["nnnn"][n] = means["lollipop"][n] / (double)(n * n * n);
    }

    // put results in files
    drop_results_to_file("clique.txt", results, "clique");

    drop_results_to_file("path.txt", results, "path");

    drop_results_to_file("path_end.txt", results, "path_end");

    drop_results_to_file("btree.txt", results, "btree");

    drop_results_to_file("lollipop.txt", results, "lollipop");

    // put means in files
    drop_mean_to_file("clique_mean.txt", means, "clique");

    drop_mean_to_file("path_mean.txt", means, "path");

    drop_mean_to_file("path_end_mean.txt", means, "path_end");

    drop_mean_to_file("btree_mean.txt", means, "btree");

    drop_mean_to_file("lollipop_mean.txt", means, "lollipop");

    // put big O notation to file
    drop_asymptotics_to_file("clique_asymptotic.txt", asymptotics, "clique");

    drop_asymptotics_to_file("path_asymptotic.txt", asymptotics, "path");

    drop_asymptotics_to_file("path_end_asymptotic.txt", asymptotics,"path_end");

    drop_asymptotics_to_file("btree_asymptotic.txt", asymptotics, "btree");

    drop_asymptotics_to_file("lollipop_asymptotic.txt", asymptotics, "lollipop");

    std::cout << "Finished putting results to files\n";
}