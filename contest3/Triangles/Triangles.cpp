#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <list>
#include <algorithm>


struct Triangle {
    int64_t xax = 0;
    int64_t yax = 0;
    int64_t zax = 0;
};

class Set {
public:
    explicit Set(size_t num_of_elements_to_come);
    
    void Add(Triangle tr);
    
    bool Contains(Triangle tr);
    
private:
    int64_t Hash(Triangle number);
    
    std::vector<std::list<Triangle>> buckets;
    
    int64_t x_coef = 0;
    int64_t square;
    size_t M_coef = 1;
};



void PrintTriangles(const std::vector<Triangle>& trs);

void ReadTriangles(std::vector<Triangle>* ptr);

bool operator==(Triangle first, Triangle second) {
    return ((first.xax == second.xax) && (first.yax == second.yax) && (first.zax == second.zax));
}

void ThreeSort(int64_t* one, int64_t* two, int64_t* three);

int64_t gcd(int64_t first, int64_t last);



void TaskFunc() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    size_t num;
    std::cin >> num;
    std::vector<Triangle> input;
    int64_t GCD;
    Triangle help;
// std::cout << "read size\n";
    for (size_t i = 0; i < num; ++i) {
        std::cin >> help.xax >> help.yax >> help.zax;
        input.push_back(help);
        GCD = std::__gcd(input[i].xax, input[i].yax);
        // std::cout << GCD << '\n';
        GCD = std::__gcd(GCD, input[i].zax);
        input[i].xax /= GCD;
        input[i].yax /= GCD;
        input[i].zax /= GCD;
        ThreeSort(&input[i].xax, &input[i].yax, &input[i].zax);
    }
//    ReadTriangles(&input);
//    PrintTriangles(input);
    Set my_set(input.size());
    size_t num_of_classes = 0;
//    std::cout << "off we go\n";
    for (size_t i = 0; i < input.size(); ++i) {
        if (!my_set.Contains(input[i])) {
            num_of_classes++;
            my_set.Add(input[i]);
        }
    }
    std::cout << num_of_classes << '\n';
}





void ThreeSort(int64_t* one, int64_t* two, int64_t* three) {
    if (*one > *two) {
        std::swap(*one, *two);
    }
    if (*three < *two) {
        if (*three < *one) {
            std::swap(*three, *one);
            std::swap(*three, *two);
        } else {
            std::swap(*three, *two);
        }
    }
}


int64_t gcd(int64_t first, int64_t last) {
    if (last == 0)
        return std::abs(first);
    return gcd(last, first % last);
}

void ReadTriangles(std::vector<Triangle>* ptr) {
    size_t num;
    std::cin >> num;
    int64_t GCD;
    // std::cout << "read size\n";
    ptr->resize(num);
    for (size_t i = 0; i < num; ++i) {
        std::cin >> (*ptr)[i].xax >> (*ptr)[i].yax >> (*ptr)[i].zax;
        GCD = gcd(gcd((*ptr)[i].xax, (*ptr)[i].yax), (*ptr)[i].zax);
        (*ptr)[i].xax = (*ptr)[i].xax / GCD;
        (*ptr)[i].yax = (*ptr)[i].yax / GCD;
        (*ptr)[i].zax = (*ptr)[i].zax / GCD;
        ThreeSort(&(*ptr)[i].xax, &(*ptr)[i].yax, &(*ptr)[i].zax);
    }
}

void PrintTriangles(const std::vector<Triangle>& trs) {
    for (size_t i = 0; i < trs.size(); ++i) {
        std::cout << trs[i].xax << ' ' << trs[i].yax << ' ' << trs[i].zax << '\n';
    }
}


Set::Set(size_t num_of_elements_to_come) {
    buckets = std::vector<std::list<Triangle>>(num_of_elements_to_come);
    M_coef = num_of_elements_to_come;
    std::default_random_engine generator(time(0));
    std::uniform_int_distribution<int64_t> distribution(1, (static_cast<int64_t>(1) << 31) - 1);
    x_coef = distribution(generator);
    square = ((
              (static_cast<int64_t>(1) << 31)
              - 1
              + (x_coef * x_coef)
              % ((static_cast<int64_t>(1) << 31) - 1)
              )
              % ((static_cast<int64_t>(1) << 31) - 1)
              );
}

void Set::Add(Triangle tr) {
    size_t hash = Hash(tr);
    for (auto elem : buckets[hash]) {
        if (elem == tr) {
            return;
        }
    }
    buckets[hash].push_back(tr);
}

bool Set::Contains(Triangle tr) {
    size_t hash = Hash(tr);
    for (auto elem : buckets[hash]) {
        if (elem == tr) {
            return true;
        }
    }
    return false;
}

int64_t Set::Hash(Triangle tr) {
    return (((tr.xax + (tr.yax * x_coef) % ((static_cast<int64_t>(1) << 31) - 1)
            + (tr.zax * square) % ((static_cast<int64_t>(1) << 31) - 1)) %
            ((static_cast<int64_t>(1) << 31) - 1)) % M_coef + M_coef) % M_coef;
}

int main() {
    TaskFunc();
    return 0;
}
