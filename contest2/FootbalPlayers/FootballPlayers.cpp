
/* INPUT
 5
 3 2 5 4 1
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>

template<class T>
typename std::vector<T>::iterator
Partition(
          typename std::vector<T>::iterator first,
          typename std::vector<T>::iterator last,
          typename std::vector<T>::iterator pivot
          );


template<class T>
void QuickSort(
               typename std::vector<T>::iterator first,
               typename std::vector<T>::iterator last
               );



template<class T, class Compare>
typename std::vector<T>::iterator
PartitionWithComparator(
                        typename std::vector<T>::iterator first,
                        typename std::vector<T>::iterator last,
                        typename std::vector<T>::iterator pivot,
                        Compare comp
                        );



template<class T, class Compare>
void QuickSortWithComparator(
                             typename std::vector<T>::iterator first,
                             typename std::vector<T>::iterator last,
                             Compare comp
                             );




struct FootballPlayer {
    
    
    size_t position;
    uint64_t goodness;
};

struct BestTeam {
    
    
    std::vector<FootballPlayer>::iterator first;
    std::vector<FootballPlayer>::iterator last;
    uint64_t total_goodness;
};

bool operator<(struct FootballPlayer first,
               struct FootballPlayer second
               ) {
    
    
    return first.goodness < second.goodness;
}

bool operator>(struct FootballPlayer first,
               struct FootballPlayer second
               ) {
    
    
    return first.goodness > second.goodness;
}

class CompareFunctor {
public:
    bool operator()(struct FootballPlayer first,
                    struct FootballPlayer second
                    ) {
        return first.position < second.position;
    }
};

template<class T>
typename std::vector<T>::iterator
Partition(
          typename std::vector<T>::iterator first,
          typename std::vector<T>::iterator last,
          typename std::vector<T>::iterator pivot
          ) {
    
    
    T piv = *pivot;
    typename std::vector<T>::iterator i = first;
    typename std::vector<T>::iterator j = last - 1;
    while (j - i >= 0) {
        while (*i < piv) {
            i++;
        }
        while (*j > piv) {
            j--;
        }
        if (j - i >= 0) {
            std::swap(*i, *j);
            i++;
            j--;
        }
    }
    return i;
}


template<class T>
void QuickSort(typename std::vector<T>::iterator first,
               typename std::vector<T>::iterator last
               ) {
    
    
    if (last - first > 2) {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(1, last - first - 2);
        size_t pivot_num = distribution(generator);
        typename std::vector<T>::iterator pivot =
        Partition<T>(first, last, first + pivot_num);
        QuickSort<T>(first, pivot);
        QuickSort<T>(pivot, last);
    } else if (last - first == 2) {
        if (*first > *(first + 1)) {
            std::swap(*first, *(first + 1));
        }
    }
}

template<class T, class Compare>
typename std::vector<T>::iterator
PartitionWithComparator(
                        typename std::vector<T>::iterator first,
                        typename std::vector<T>::iterator last,
                        typename std::vector<T>::iterator pivot,
                        Compare comp
                        ) {
    
    
    T piv = *pivot;
    typename std::vector<T>::iterator i = first;
    typename std::vector<T>::iterator j = last - 1;
    while (j - i >= 0) {
        while (comp(*i, piv)) {
            i++;
        }
        while (comp(piv, *j)) {
            j--;
        }
        if (j - i >= 0) {
            std::swap(*i, *j);
            i++;
            j--;
        }
    }
    return i;
}


template<class T, class Compare>
void QuickSortWithComparator(
                             typename std::vector<T>::iterator first,
                             typename std::vector<T>::iterator last,
                             Compare comp
                             ) {
    
    
    if (!(last - first <= 2)) {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(1, last - first - 2);
        size_t pivot_num = distribution(generator);
        typename std::vector<T>::iterator pivot =
        PartitionWithComparator<T, Compare>(
                                            first,
                                            last,
                                            first + pivot_num,
                                            comp
                                            );
        QuickSortWithComparator<T>(first, pivot, comp);
        QuickSortWithComparator<T>(pivot, last, comp);
    } else if (last - first == 2) {
        if (comp(*(first + 1), *first)) {
            std::swap(*first, *(first + 1));
        }
    }
}


void read_vector_football(std::vector<FootballPlayer>* vector) {
    
    
    FootballPlayer help;
    size_t num_of_elements;
    std::cin >> num_of_elements;
    vector->resize(num_of_elements);
    for (size_t i = 0; i < vector->size(); ++i) {
        std::cin >> help.goodness;
        help.position = i;
        (*vector)[i] = help;
    }
}


void write_result(struct BestTeam res) {
    
    std::cout << res.total_goodness << '\n';
    while (res.last - res.first >= 0) {
        std::cout << (*res.first).position + 1 << ' ';
        res.first++;
    }
    std::cout << '\n';
}


bool check_team_prop(int64_t first, int64_t second, int64_t third) {
    
    
    return first + second >= third;
}


struct BestTeam
FindBestPossibleTeam (
                      std::vector<FootballPlayer>::iterator start,
                      std::vector<FootballPlayer>::iterator finish
                      ) {
    
    
    struct BestTeam res;
    if (finish - start > 2) {
        std::vector<FootballPlayer>::iterator begin, end;
        begin = finish - 2;
        end = finish - 1;
        res.first = begin;
        res.last = end;
        uint64_t sum = 0;
        uint64_t max = 0;
        sum += (*end).goodness;
        sum += (*begin).goodness;
        while (begin != start) {
            if (check_team_prop((*(begin - 1)).goodness,
                                (*begin).goodness,
                                (*end).goodness)
                ) {
                begin--;
                sum += (*begin).goodness;
            } else {
                if (sum >= max) {
                    max = sum;
                    res.first = begin;
                    res.last = end;
                    res.total_goodness = max;
                }
                sum -= (*end).goodness;
                end--;
            }
        }
        if (sum >= max) {
            max = sum;
            res.first = begin;
            res.last = end;
            res.total_goodness = max;
        }
    } else {
        res.first = start;
        res.last = finish - 1;
        if (finish - start == 2) {
            res.total_goodness = (*start).goodness + (*(start + 1)).goodness;
        } else if (finish - start == 1) {
            res.total_goodness = (*start).goodness;
        }
    }
    return res;
}


void Football() {
    
    
    std::vector<FootballPlayer> vec;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    read_vector_football(&vec);
    QuickSort<FootballPlayer>(vec.begin(), vec.end());
    struct BestTeam res = FindBestPossibleTeam(vec.begin(), vec.end());
    CompareFunctor comparator;
    QuickSortWithComparator<FootballPlayer, CompareFunctor>(res.first,
                                                            res.last + 1,
                                                            comparator
                                                            );
    write_result(res);
}


int main() {
    
    
    Football();
    return 0;
}
