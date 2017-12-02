#include <iostream>
#include <vector>
#include <algorithm>


template <class T>
void read_vector(std::vector<T>* vector) {
    
    
    size_t num_of_elements;
    std::cin >> num_of_elements;
    vector->resize(num_of_elements);
    for (size_t i = 0; i < vector->size(); ++i) {
        std::cin >> (*vector)[i];
    }
}


template <class T>
void write_vector(const std::vector<T>& vector) {
    
    
    for (size_t i = 0; i < vector.size(); ++i) {
        std::cout << vector[i] << ' ';
    }
    std::cout << '\n';
}


template <class T>
void write_matrix(const std::vector<std::vector<T>>& vector) {
    
    
    for (size_t i = 0; i < vector.size(); ++i) {
        for (size_t j = 0; j < vector[0].size(); ++j) {
            std::cout << vector[i][j] << ' ';
        }
        std::cout << '\n';
    }
}


template <class T>
size_t LCS(const std::vector<T>& first, const std::vector<T>& second) {
    
    
    std::vector<std::vector<size_t>> dynamic;
    dynamic.resize(second.size() + 1);
    for (size_t i = 0; i < second.size() + 1; ++i) {
        dynamic[i].resize(first.size() + 1);
        for (size_t j = 0; j < first.size() + 1; ++j) {
            if ((i == 0) || (j == 0)) {
                dynamic[i][j] = 0;
            } else if (first[j - 1] == second[i - 1]) {
                dynamic[i][j] = dynamic[i - 1][j - 1] + 1;
            } else {
                dynamic[i][j] = std::max(dynamic[i][j - 1], dynamic[i - 1][j]);
            }
        }
    }
    return dynamic.back().back();
}

void TaskFunc() {
    
    
    std::vector<int> first, second;
    read_vector(&first);
    read_vector(&second);
    std::cout << LCS(first, second) << '\n';
}


int main() {
    
    
    TaskFunc();
    return 0;
}
