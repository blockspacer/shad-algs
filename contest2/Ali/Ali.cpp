#include <iostream>
#include <vector>
#include <algorithm>


/* INPUT
 5
 1 3
 3 1
 5 8
 8 19
 10 15
 */


struct coin {
    uint64_t lifetime;
    uint64_t position;
};


bool operator<(struct coin first, struct coin second) {
    return (first.position < second.position) || ((first.position == second.position)
                                                  && (first.lifetime < second.lifetime));
}


void read_coins(std::vector<coin>* coins) {
    size_t num_of_coins;
    std::cin >> num_of_coins;
    coins->resize(num_of_coins);
    for (size_t i = 0; i < num_of_coins; ++i) {
        std::cin >> (*coins)[i].position >> (*coins)[i].lifetime;
    }
}


std::vector<coin> get_rid_of_duplets(const std::vector<coin>& coins) {
    std::vector<coin> res;
    if (coins.size() > 0) {
        res.push_back(coins[0]);
    }
    for (size_t i = 1; i < coins.size(); ++i) {
        if (coins[i].position != res.back().position) {
            res.push_back(coins[i]);
        }
    }
    return res;
}


void write_coins(const std::vector<coin>& coins) {
    for (size_t i = 0; i < coins.size(); ++i) {
        std::cout << coins[i].position << ' ' << coins[i].lifetime << '\n';
    }
}


size_t MinimalTime(const std::vector<coin>& coins) {
    std::vector<std::vector<size_t>> table;
    size_t tmp_time;
    table.resize(coins.size());
    for (size_t i = 0; i < table.size(); ++i) {
        table[i].resize(coins.size());
        table[i][i] = 0;
    }
    for (size_t index_l = 1; index_l < table.size(); ++index_l) {
        for (size_t index_r = 0; index_r < table.size() - index_l; ++index_r) {
            tmp_time = std::min(table[index_r][index_l + index_r - 1]
                                + coins[index_l + index_r].position
                                - coins[index_l + index_r - 1].position,
                                table[index_l + index_r - 1][index_r]
                                + coins[index_r + index_l].position
                                - coins[index_r].position);
            table[index_r][index_l + index_r]
            = tmp_time > coins[index_l + index_r].lifetime ? 1000001 : tmp_time;
            tmp_time = std::min(table[index_l + index_r][index_r + 1]
                                + coins[index_r + 1].position
                                - coins[index_r].position,
                                table[index_r + 1][index_l + index_r]
                                + coins[index_r + index_l].position
                                - coins[index_r].position);
            table[index_l + index_r][index_r]
            = tmp_time > coins[index_r].lifetime ? 1000001 : tmp_time;
        }
    }
//    for (size_t i = 0; i < table.size(); ++i) {
//        for (size_t index_r = 0; index_r < table.size(); ++index_r) {
//            std::cout << table[i][index_r] << '\t';
//        }
//        std::cout << std::endl;
//    }
//    std::cout << std::min(table[0][table.size() - 1], table[table.size() - 1][0]) << std::endl;
    return std::min(table[0][table.size() - 1], table[table.size() - 1][0]);
}


void TaskFunc() {
    std::vector<coin> coins;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    read_coins(&coins);
    std::sort(coins.begin(), coins.end());
    // write_coins(coins);
    coins = get_rid_of_duplets(coins);
    // write_coins(coins);
    size_t res = MinimalTime(coins);
    if (res > 1000000) {
        std::cout << "No solution\n";
    } else {
        std::cout << res << '\n';
    }
}


int main() {
    
    
    TaskFunc();
    return 0;
}
