#include "dbscan.h"
#include <limits>

void load_file(std::vector<Photo> & labels, std::string file_name, int & clusters_count) {
  std::fstream f;
  f.open(file_name);

  std::string buff;
  getline(f, buff);
  clusters_count = std::stoi(buff);

  int index = 0;
  while(getline(f, buff)) {
    labels.at(index).label = std::stoi(buff);
    index++;
  }

  f.close();
}

void calc_corr_incorr(int & correct_labels, int & incorrect_labels, std::vector<int> & labels) {
  int max = std::numeric_limits<int>::min();
  int max_index = 0;
  for(int i = 0; i < labels.size(); i++) {
    if(labels.at(i) > max) {
      max = labels.at(i);
      max_index = i;
    }
  }

  correct_labels += labels.at(max_index);

  for(int i = 0; i < labels.size(); i++) {
    if(i == max_index)
      continue;
    incorrect_labels += labels.at(i);
  }
}

void analyze_results(std::vector<Photo> & clustered_photos,
                     std::vector<unsigned char> & labels,
                     int clusters_count) {
  int noise_count = 0;
  int correct_labels = 0;
  int incorrect_labels = 0;
  std::vector<std::vector<int>> grouped_clusters(clusters_count, std::vector<int>());
  for(int i = 0; i < clustered_photos.size(); i++) {
    auto curr_photo = clustered_photos.at(i);
    if(curr_photo.label == -1) {
      noise_count++;
      continue;
    }

    grouped_clusters.at(curr_photo.label - 1).push_back(labels.at(i));
  }
  for(auto & group : grouped_clusters) {
    std::vector<int> occurrences_count(10, 0);
    for(auto label : group) {
      occurrences_count.at(label)++;
    }

    calc_corr_incorr(correct_labels, incorrect_labels, occurrences_count);
  }
  std::cout << "Correct data: " << (double) correct_labels / (double) clustered_photos.size() << std::endl;
  std::cout << "Incorrect data: " << (double) incorrect_labels / (double) clustered_photos.size() << std::endl;
  std::cout << "Noise amount: " << (double) noise_count / (double) clustered_photos.size() << std::endl;
}

int main() {
  std::vector<Photo> photos;
  load_images(photos, "./Zad2/data/train-images.idx3-ubyte");
  std::vector<unsigned char> labels;
  load_labels(labels, "./Zad2/data/train-labels.idx1-ubyte");

  int clusters_count = dbscan(photos, 0.4, 5000);

  std::fstream out_f;
  out_f.open("Result_clusters3.txt", std::fstream::out);

  out_f << clusters_count << std::endl;
  for(auto & photo : photos) {
    out_f << photo.label << std::endl;
  }

  out_f.close();

//  int clusters_count = 0;
//  load_file(photos, "./Result clusters.txt", clusters_count);

  analyze_results(photos,
                  labels,
                  clusters_count);
}