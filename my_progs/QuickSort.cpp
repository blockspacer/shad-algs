#include <iostream>
#include <random>


template<class T>
typename std::vector<T>::iterator Partition(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last, typename std::vector<T>::iterator pivot) {
    T piv = *pivot;
    typename std::vector<T>::iterator i = first;
    typename std::vector<T>::iterator j = last - 1;
    while (j - i >= 0){
        while (*i < piv) {
            i++;
        }
        while (*j > piv) {
            j--;
        }
        if (j - i >= 0){
            std::swap(*i, *j);
            i++;
            j--;
        }
    }
    return i;
}


template<class T>
void QuickSort(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last) {
    if (!(last - first <= 2)){
        std::default_random_engine generator(73473247);
        std::uniform_int_distribution<int> distribution(1, last - first - 2);
        size_t pivot_num = distribution(generator);
        typename std::vector<T>::iterator pivot = Partition<T>(first, last, first + pivot_num);
        QuickSort<T>(first, pivot);
        QuickSort<T>(pivot, last);
    } else if (last - first == 2) {
        if (*first > *(first + 1)) {
            std::swap(*first, *(first + 1));
        }
    }
}

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
    QuickSort<int>(vec.begin(), vec.end());
//    for (size_t i = 0; i < vec.size(); ++i) {
//        std::cout << vec[i] << ' ';
//        if (i % 20 == 0) {
//            std::cout << '\n';
//        }
//    }
//    std::cout << '\n';
    return 0;
}