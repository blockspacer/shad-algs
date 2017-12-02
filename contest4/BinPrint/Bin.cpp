#include <iostream>
#include <vector>
#include <algorithm>


/* INPUT
6
5 3 2 3 5 6
 */

void Binny(const std::vector<int64_t>& input,
           size_t first,
           size_t last,
           size_t ans_first,
           size_t ans_last,
           std::vector<int64_t>* output) {
//    std::cout << "one more level\n";
//    std::cout << first << ' ' << last << ' ' << ans_first << ' ' << ans_last << '\n';
    bool flag = true;
    while (flag) {
        if (last - first + 1 <= 2) {
            if (last - first + 1 == 2) {
                (*output)[ans_first] = input[first + 1];
                (*output)[ans_first + 1] = input[first];
            } else if (last - first == 0) {
                (*output)[ans_first] = input[first];
            }
            return;
        }
        (*output)[ans_last] = input[first];
        size_t start, finish, middle;
        start = first + 1;
        finish = last;
    //    std::cout << start << ' ' << finish << '\n';
        while (start != finish - 1) {
            middle = start + (finish - start) / 2;
    //        std::cout << finish - start + 1 << ' ' << middle << '\n';
            if (input[middle] < input[first]) {
                start = middle;
            } else {
                finish = middle;
            }
        }
        if (input[start] >= input[first]) {
            middle = start - 1;
        } else if (input[finish] >= input[first]) {
            middle = finish - 1;
        } else {
            middle = finish;
        }
    //    std::cout << start << ' ' << finish << ' ' << middle << '\n';
    //    std::cout << "level finished\n\n";
        if ((middle > first) && (last > middle)) {
            Binny(input, first + 1, middle, ans_first, ans_first + (middle - first - 1), output);
            Binny(input, middle + 1, last, ans_first + (middle - first), ans_last - 1, output);
            flag = false;
        } else if (middle > first) {
            last = middle;
            ans_last = ans_first + (middle - first - 1);
            first++;
        } else if (last > middle) {
            ans_last--;
            ans_first += middle - first;
            first = middle + 1;
        }
    }
}

//  void ReadVector(std::vector<int64_t>* input) {
//    size_t num;
//    std::cin >> num;
//    input->resize(num);
//    for (size_t i = 0; i < input->size(); ++i) {
//        std::cin >> (*input)[i];
//    }
//  }

void TaskFunc() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t num;
    std::cin >> num;
    std::vector<int64_t> tree(num);
    std::vector<int64_t> post(num);
    //    input->resize(num);
        for (size_t i = 0; i < tree.size(); ++i) {
            std::cin >> tree[i];
        }
    // ReadVector(&tree);
//    std::cout << "read\n";
    Binny(tree, 0, tree.size() - 1, 0, post.size() - 1, &post);
    for (size_t i = 0; i < tree.size(); ++i) {
        std::cout << post[i] << ' ';
    }
    std::cout << '\n';
    std::sort(tree.begin(), tree.end());
    for (size_t i = 0; i < tree.size(); ++i) {
        std::cout << tree[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    TaskFunc();
    return 0;
}

