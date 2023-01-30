#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <thread>
#include <mutex>

std::mutex map_insertion_mutex;

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
 *
 * @return Vertex number after one step of random walk;
 */
int random_walk_step(const std::vector<std::vector<int>> &graph, int current_vertex, std::mt19937_64 &rand_gen) {
    std::uniform_int_distribution<> dist(0, (int)graph.at(current_vertex).size() - 1);
    int chosen_index = dist(rand_gen);
    return graph.at(current_vertex).at(chosen_index);
}

bool check_vertex_visits(std::vector<int> vertex_visit_counter) {
    return std::all_of(vertex_visit_counter.begin(),
                       vertex_visit_counter.end(),
                       [](int & counter) {
        return counter > 0;
    });
}

int generate_experiment(const std::vector<std::vector<int>> &graph, int current_vertex, std::mt19937_64 &rand_gen) {
    std::vector<int> vertex_visit_counter(graph.size(), 0);
    int counter = 0;
    vertex_visit_counter.at(current_vertex)++;  // not sure if starting vertex is taken as visited
    while(!check_vertex_visits(vertex_visit_counter)) {
        current_vertex = random_walk_step(graph, current_vertex, rand_gen);
        vertex_visit_counter.at(current_vertex)++;
        counter++;
    }
    return counter;
}

void generate_i_experiments(std::unordered_map<std::string, std::unordered_map<int, std::vector<int>>> &results,
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
        int time = generate_experiment(clique_graph, dist(rand_gen), rand_gen);
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

void print_links(std::vector<std::vector<int>> graph) {
    for(int i=0; i < graph.size(); i++) {
        auto links = graph.at(i);
        for(int j : links) {
            std::cout << i << " -> " << j << std::endl;
        }
        std::cout << std::endl;
    }
}


int main() {
    std::random_device rd{};
    std::mt19937_64 rand_gen{rd()};

    // available keys: clique, path, path_end, btree, lollipop
    std::unordered_map<std::string, std::unordered_map<int, std::vector<int>>> results;

    // experiments
    int K = 50;

    for(int n=100; n <= 500; n += 50) {
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
    std::unordered_map<std::string, std::unordered_map<int, int>> means;

}