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


class QuadraticHash {
public:
    QuadraticHash();
    
    void Initialize(const std::vector<int64_t>& numbers);
    
    void Initialize();
    
    void AddElement(int64_t element);
    
    bool Contains(int64_t to_check);
    
    size_t GetBucketSize();
    
private:
    int GetHash(int64_t number);
    
    std::vector<int64_t> elements;
    
    std::vector<int64_t> table;
    
    int64_t a_coef;
    int64_t b_coef;
    int64_t M_coef = 1;
};

class FixedSet {
public:
    FixedSet();
    
    void Initialize(const std::vector<int64_t>& numbers);
    
    bool Contains(int64_t number);
    
private:
    int Hash(int64_t number);
    
    std::vector<QuadraticHash> first_level_buckets;
    
    int64_t a_coef;
    int64_t b_coef;
    int64_t M_coef = 1;
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

QuadraticHash::QuadraticHash() {}

int QuadraticHash::GetHash(int64_t number) {
// std::cout << a << ' ' << b << ' ' << number << std::endl;
    return (M_coef + (((((a_coef % (static_cast<int64_t>(1) << 31) - static_cast<int64_t>(1))
                         * ((number + 1000000000) % (static_cast<int64_t>(1) << 31) -
                            static_cast<int64_t>(1))) % ((static_cast<int64_t>(1) << 31) - 1) +
                        (b_coef % (static_cast<int64_t>(1) << 31) - 1)) %
                       (static_cast<int64_t>(1) << 31) - 1) % M_coef)) % M_coef;
}

void QuadraticHash::AddElement(int64_t element) {
    elements.push_back(element);
}

void QuadraticHash::Initialize() {
    Initialize(elements);
}

void QuadraticHash::Initialize(const std::vector<int64_t>& numbers) {
    std::default_random_engine generator(time(0));
    std::uniform_int_distribution<int64_t> distribution_one(1, (static_cast<int64_t>(1) << 31) - 1);
    std::uniform_int_distribution<int64_t> distribution_two(0, (static_cast<int64_t>(1) << 31) - 1);
    bool flag = true;
    bool flaggy = true;
    int hash = 0;
    while (flag) {
        a_coef = distribution_one(generator);
        b_coef = distribution_two(generator);
        M_coef = numbers.size() * numbers.size();
        // std::cout << a << ' ' << b << ' ' << M << '\n';
        // std::cout << "creating table\n";
        table = std::vector<int64_t>(M_coef, -1000000000);
        // std::cout << "done\n";
        flaggy = true;
        // std::cout << "initializing\n";
        for (size_t i = 0; (i < numbers.size()) && (flaggy); ++i) {
            hash = GetHash(numbers[i]);
            if (table[hash] > -1000000000) {
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


bool QuadraticHash::Contains(int64_t to_check) {
    
    // std::cout << to_check << ' ' << GetHash(to_check) << '\n';
    if (table.size() == 0) {
        return false;
    }
    return table[GetHash(to_check)] == to_check;
}

size_t QuadraticHash::GetBucketSize() {
    return elements.size();
}

FixedSet::FixedSet() {}

void FixedSet::Initialize(const std::vector<int64_t>& numbers) {
    std::default_random_engine generator(time(0));
    std::uniform_int_distribution<int64_t> distribution_one(1, (static_cast<int64_t>(1) << 31) - 1);
    std::uniform_int_distribution<int64_t> distribution_two(0, (static_cast<int64_t>(1) << 31) - 1);
    bool flag = true;
    bool flaggy = true;
    int64_t hash = 0;
    size_t sum;
    while (flag) {
        sum = 0;
        flaggy = true;
        a_coef = distribution_one(generator);
        b_coef = distribution_two(generator);
        M_coef = numbers.size();
        first_level_buckets.resize(numbers.size());
        for (size_t i = 0; (i < numbers.size()) && (flaggy); ++i) {
            hash = Hash(numbers[i]);
            // std::cout << numbers[i] << ' ' << hash << '\n';
            sum += 2 * first_level_buckets[hash].GetBucketSize() + 1;
            first_level_buckets[hash].AddElement(numbers[i]);
            if (sum > 4 * numbers.size()) {
                // std::cout << "smth went wrong\n";
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

bool FixedSet::Contains(int64_t number) {
    // std::cout << number << ' ' << Hash(number) << '\n';
    return first_level_buckets[Hash(number)].Contains(number);
}

int FixedSet::Hash(int64_t number) {
    return (M_coef + (((((a_coef % (static_cast<int64_t>(1) << 31) -
                          static_cast<int64_t>(1)) *
                         ((number + 1000000000) % (static_cast<int64_t>(1) << 31) -
                          static_cast<int64_t>(1))) %
                        ((static_cast<int64_t>(1) << 31) - 1) +
                        (b_coef % (static_cast<int64_t>(1) << 31) - 1)) %
                       (static_cast<int64_t>(1) << 31) - 1) % M_coef)) % M_coef;
}





