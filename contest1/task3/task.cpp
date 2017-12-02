#include <iostream>
#include <vector>
#include <algorithm>


struct Box {
    int64_t length;
    int64_t width;
    int64_t height;
};

bool operator < (const struct Box first, const struct Box second) {
    return (first.length < second.length) && (first.width < second.width)
        && (first.height < second.height);
}


template<class T>
void vector_reader(std::vector<T>* vect) {
    size_t num_of_elements;
    std::cin >> num_of_elements;
    vect->resize(num_of_elements);
    for (size_t i = 0; i < vect->size(); ++i) {
        std::cin >> (*vect)[i];
    }
}


void box_vector_reader(std::vector<struct Box>* vect) {
    size_t num_of_elements;
    std::cin >> num_of_elements;
    vect->resize(num_of_elements);
    for (size_t i = 0; i < vect->size(); ++i) {
        std::cin >> (*vect)[i].length >> (*vect)[i].width >> (*vect)[i].height;
    }
}


template<class T>
void vector_writer(const std::vector<T>& vect) {
    for (size_t i = 0; i < vect.size(); ++i) {
        std::cout << vect[i] << ' ';
    }
    std::cout << '\n';
}


template<class T>
size_t longest_increasing_subsequence_size(const std::vector<T>& vector) {
    std::vector<size_t> dynamic;
    dynamic.resize(vector.size());
    for (size_t i = 0; i < vector.size(); ++i) {
        dynamic[i] = 1;
        for (size_t j = 0; j < i; ++j) {
            if (vector[j] < vector[i]) {
                dynamic[i] = std::max(dynamic[i], 1 + dynamic[j]);
            }
        }
    }
    
    size_t res = dynamic[0];
    for (size_t i = 0; i < vector.size(); ++i) {
        res = std::max(res, dynamic[i]);
    }
    return res;
}


template<class T>
void TaskFunc() {
    std::vector<T> vector;
    // std::cout << "stage1\n";
    vector_reader(&vector);
    // std::cout << "stage2\n";
    std::cout << longest_increasing_subsequence_size(vector) << '\n';
}


void BoxTaskFunc() {
    std::vector<struct Box> vector;
    // std::cout << "stage1\n";
    box_vector_reader(&vector);
    // std::cout << "stage2\n";
    std::cout << longest_increasing_subsequence_size(vector) << '\n';
}


int main() {
    
    BoxTaskFunc();
    // TaskFunc<int>();
    return 0;
}
