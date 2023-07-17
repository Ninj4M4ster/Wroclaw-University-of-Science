#ifndef AI_LIST4_ZAD2_DBSCAN_H_
#define AI_LIST4_ZAD2_DBSCAN_H_

#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <math.h>

typedef std::vector<double> Pixels;

typedef struct photo_data {
  Pixels pixels = std::vector<double>(28 * 28);
  double magnitude = 0;
  int label = -2;  // undefined
} Photo;


int reverseInt(int i) {
  unsigned char c1, c2, c3, c4;

  c1 = i & 255;
  c2 = (i >> 8) & 255;
  c3 = (i >> 16) & 255;
  c4 = (i >> 24) & 255;

  return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}
inline double magnitude(Pixels& photo) {
  double result = 0;
  for(auto val : photo) {
    result += val * val;
  }
  return std::sqrt(result);
}

void load_images(std::vector<Photo> & photos, std::string file_name) {
  std::ifstream file;
  file.open(file_name.c_str(), std::ifstream::binary);
  if (file.is_open())
  {
    int magic_number=0;
    int number_of_images=0;
    int n_rows=0;
    int n_cols=0;
    file.read((char*)&magic_number,sizeof(magic_number));
    magic_number = reverseInt(magic_number);
    file.read((char*)&number_of_images,sizeof(number_of_images));
    number_of_images = reverseInt(number_of_images);
    file.read((char*)&n_rows,sizeof(n_rows));
    n_rows = reverseInt(n_rows);
    file.read((char*)&n_cols,sizeof(n_cols));
    n_cols = reverseInt(n_cols);
    for(int i=0; i<number_of_images; i++)
    {
      Photo photo;
      for(int r=0; r<n_rows; r++)
      {
        for(int c=0; c<n_cols; c++)
        {
          unsigned char temp = 0;
          file.read((char*)&temp,sizeof(temp));
          photo.pixels.at(r * 28 + c) = (double) temp / 255.0;
        }
      }
      photo.magnitude = magnitude(photo.pixels);
      photos.push_back(photo);
    }
  }
  file.close();
}

void load_labels(std::vector<unsigned char> & labels, std::string file_name) {
  std::ifstream f;
  f.open(file_name, std::ifstream::binary);
  if(f.is_open()) {
    int magic_number = 0;
    int number_of_items = 0;
    f.read((char*)&magic_number,sizeof(magic_number));
    magic_number = reverseInt(magic_number);
    f.read((char*)&number_of_items,sizeof(number_of_items));
    number_of_items = reverseInt(number_of_items);
    for(int i = 0; i < number_of_items; i++) {
      unsigned char temp = 0;
      f.read((char*)&temp,sizeof(temp));
      labels.push_back(temp);
    }
  }
  f.close();
}

inline double dotProduct(Pixels& photo1, Pixels& photo2) {
  double result = 0;
  for(int i = 0; i < photo1.size(); i++) {
    result += photo1.at(i) * photo2.at(i);
  }
  return result;
}

inline double distance(Photo& photo1, Photo& photo2) {
  double dot_prod = dotProduct(photo1.pixels, photo2.pixels);
  return 1.0 - dot_prod / (photo1.magnitude * photo2.magnitude);
}

std::set<Photo*> closestNeighbours(std::set<Photo*> & photos, Photo & photo, double eps) {
  std::set<Photo*> neighbours;
  for(auto & curr_photo : photos) {
    if(distance(photo, *curr_photo) <= eps) {
      if(curr_photo->pixels == photo.pixels)
        continue;
      Photo* pointer = curr_photo;
      neighbours.emplace(pointer);
    }
  }
  return neighbours;
}

std::set<Photo*> closestNeighbours(std::vector<Photo> & photos, Photo & photo, double eps) {
  std::set<Photo*> neighbours;
  int index = 0;
  for(auto & curr_photo : photos) {
    if(distance(photo, curr_photo) <= eps) {
      if(curr_photo.pixels == photo.pixels) {
        continue;
      }
      Photo* pointer = &curr_photo;
      neighbours.emplace(pointer);
    }
  }
  return neighbours;
}

int dbscan(std::vector<Photo> & photos, double eps, int minPts) {
  int cluster_counter = 0;
  int index = 0;
  for(auto & point : photos) {  // outside loop start
    if(index % 1000 == 0)
      std::cout << "Next point: " << index << "\n";
    if(point.label != -2) { // skip if label already given
      index++;
      continue;
    }

    std::set<Photo*> neighbours = closestNeighbours(photos, point, eps);
    if(neighbours.size() + 1 < minPts) {
      point.label = -1;  // mark as noise
      index++;
      continue;
    }

    cluster_counter++;
    std::cout << "Clusters increased: " << cluster_counter << std::endl;
    point.label = cluster_counter;
    for(auto & nei : neighbours) {  // seed point loop start
      if(nei->label == -1) {
        nei->label = cluster_counter;
      }
      if(nei->label != -2)
        continue;
      nei->label = cluster_counter;
      std::set<Photo*> neighbours_of_neighbours = closestNeighbours(neighbours, *nei, eps);
      if(neighbours_of_neighbours.size() + 1 >= minPts) {  // add to seed set loop start
        for(auto & nei_nei : neighbours_of_neighbours)
          neighbours.emplace(nei_nei);
      }  // add to seed set loop end
    }  // seed point loop end
    index++;
  }  // outside loop end
  std::cout << "Final cluster counter: " << cluster_counter << std::endl;
  return cluster_counter;
}

#endif //AI_LIST4_ZAD2_DBSCAN_H_
