#include <iostream>
#include <vector>
#include <random>
#include <ctime>


/* INPUT
 3
 1 2 3
 4
 1 2 3 4
 */

const int64_t my_prime = (static_cast<int64_t>(1) << 31) - static_cast<int64_t>(1);

const int64_t my_const = 1000000000;


class Hash {
public:
    Hash(const int64_t& a, const int64_t& b, const int64_t& M)
    : a_coef(a), b_coef(b), M_coef(M) {
    }
    int GetHash(int number) const {
        return (M_coef + (((((a_coef % my_prime) *
                             ((number + my_const) % my_prime)) %
                            my_prime +
                            (b_coef % my_prime) %
                            my_prime) % M_coef))) % M_coef;
    }
private:
    int64_t a_coef;
    int64_t b_coef;
    int64_t M_coef = 1;
};

class QuadraticHash {
public:
    QuadraticHash();
    
    void Initialize(const std::vector<int64_t>& numbers);
    
    void Initialize();
    
    void AddElement(int64_t element);
    
    bool Contains(const int64_t& to_check) const;
    
    size_t GetBucketSize() const;
    
private:
    int GetHash(const int64_t& number) const;
    
    std::vector<int64_t> elements;
    
    std::vector<int64_t> table;
    
    Hash hash_;
    
//    int64_t a_coef;
//    int64_t b_coef;
//    int64_t M_coef = 1;
};

class FixedSet {
public:
    FixedSet();
    
    void Initialize(const std::vector<int64_t>& numbers);
    
    bool Contains(int64_t number) const;
    
private:
    int GetHash(const int64_t& number) const;
    
    std::vector<QuadraticHash> first_level_buckets;
    
    Hash hash_;
    
//    int64_t a_coef;
//    int64_t b_coef;
//    int64_t M_coef = 1;
};


void TaskFunc() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t num_of_elements;
    size_t num_of_queries;
    int number;
    std::vector<int64_t> nums;
    std::vector<int64_t> queries;
    std::cin >> num_of_elements;
    nums.resize(num_of_elements);
    for (size_t i = 0; i < num_of_elements; ++i) {
        std::cin >> nums[i];
    }
    FixedSet hs;
    hs.Initialize(nums);
    std::cin >> num_of_queries;
    // queries.resize(n);
//   std::cout << "queries\n";
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    for (size_t i = 0; i < num_of_queries; ++i) {
        std::cin >> number;
        if (hs.Contains(number)) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }
}


int main() {
    TaskFunc();
    return 0;
}

QuadraticHash::QuadraticHash() : hash_(0, 0, 0) {}

int QuadraticHash::GetHash(const int64_t& number) const {
    return hash_.GetHash(number);
}

void QuadraticHash::AddElement(int64_t element) {
    elements.push_back(element);
}

void QuadraticHash::Initialize() {
    Initialize(elements);
}

void QuadraticHash::Initialize(const std::vector<int64_t>& numbers) {
    std::default_random_engine generator(time(0));
    std::uniform_int_distribution<int64_t> distribution_one(1, my_prime);
    std::uniform_int_distribution<int64_t> distribution_two(0, my_prime);
    bool flag = true;
    bool flaggy = true;
    int hash = 0;
    while (flag) {
        hash_ = Hash(distribution_one(generator),
                     distribution_one(generator),
                     numbers.size() * numbers.size());
//        a_coef = distribution_one(generator);
//        b_coef = distribution_two(generator);
//        M_coef = numbers.size() * numbers.size();
        table = std::vector<int64_t>(numbers.size() * numbers.size(), -my_const);
        // std::cout << "done\n";
        flaggy = true;
        // std::cout << "initializing\n";
        for (size_t i = 0; (i < numbers.size()) && (flaggy); ++i) {
            hash = GetHash(numbers[i]);
            if (table[hash] > -my_const) {
                flaggy = false;
                table.clear();
            } else {
                table[hash] = numbers[i];
            }
        }
        if (flaggy) {
            flag = false;
        }
    }
}


bool QuadraticHash::Contains(const int64_t& to_check) const {
    
    // std::cout << to_check << ' ' << GetHash(to_check) << '\n';
    if (table.size() == 0) {
        return false;
    }
    return table[GetHash(to_check)] == to_check;
}

size_t QuadraticHash::GetBucketSize() const {
    return elements.size();
}

FixedSet::FixedSet() : hash_(0, 0, 0) {}

void FixedSet::Initialize(const std::vector<int64_t>& numbers) {
    std::default_random_engine generator(time(0));
    std::uniform_int_distribution<int64_t> distribution_one(1, my_prime);
    std::uniform_int_distribution<int64_t> distribution_two(0, my_prime);
    bool flag = true;
    bool flaggy = true;
    int64_t hash = 0;
    size_t sum;
    while (flag) {
        sum = 0;
        flaggy = true;
        hash_ = Hash(distribution_one(generator), distribution_two(generator), numbers.size());
        first_level_buckets.resize(numbers.size());
        for (size_t i = 0; (i < numbers.size()) && (flaggy); ++i) {
            hash = GetHash(numbers[i]);
            sum += 2 * first_level_buckets[hash].GetBucketSize() + 1;
            first_level_buckets[hash].AddElement(numbers[i]);
            if (sum > 4 * numbers.size()) {
                first_level_buckets.clear();
                flaggy = false;
            }
        }
        if (flaggy) {
            flag = false;
        }
    }
    
    for (size_t i = 0; i < first_level_buckets.size() ; ++i) {
        // std::cout << "initializing bucket\n";
        first_level_buckets[i].Initialize();
        // std::cout << '\n';
    }
    //    std::cout << "printing_table\n";
    //    for (size_t i = 0; i < table.size(); ++i) {
    //        std::cout << table[i] << ' ';
    //    }
    //    std::cout << '\n';
    //    std::cout << "a is " << a << "b is " << b << "M is " << M << '\n';
    // std::cout << "leaving\n";
}

bool FixedSet::Contains(int64_t number) const {
    // std::cout << number << ' ' << Hash(number) << '\n';
    return first_level_buckets[GetHash(number)].Contains(number);
}

int FixedSet::GetHash(const int64_t& number) const {
    return hash_.GetHash(number);
}





