#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<int> vec;
    size_t num_of_elements;
    std::cin >> num_of_elements;
    vec.resize(num_of_elements);
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cin >> vec[i];
    }
    //QuickSort<int>(vec.begin(), vec.end());
    std::sort(vec.begin(), vec.end());
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}
