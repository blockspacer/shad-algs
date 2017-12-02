#include <iostream>
#include <vector>


int64_t Sign(int64_t number) {
    
    return (number > 0) - (number < 0);
}

struct ItemIndex {
    
    int64_t value;
    int64_t index;
    ItemIndex(int64_t argv, int64_t argi) {
        value = argv;
        index = argi;
    }
};

void ExtractLocalUnique(const std::vector<int64_t> &sequence, std::vector<int64_t> *uniques) {
    
    for (size_t i = 0; i < sequence.size(); ++i) {
        uniques->push_back(sequence[i]);
        while (i + 1 < sequence.size() && sequence[i + 1] == sequence[i]) {
            ++i;
        }
    }
}

std::vector<ItemIndex> FindLocalExtremums(const std::vector<int64_t> &sequence) {
    
    std::vector<ItemIndex> extremums;
    extremums.push_back(ItemIndex(sequence[0], 0));
    
    for (size_t i = 0; i < sequence.size() - 2; ++i) {
        if (Sign(sequence[i] - sequence[i + 1]) !=
            Sign(sequence[i + 1] - sequence[i + 2])) {
            extremums.push_back(ItemIndex(sequence[i + 1], i + 1));
        }
    }
    extremums.push_back(ItemIndex(sequence.back(), static_cast<int64_t>(sequence.size() - 1)));
//    for (size_t i = 0; i < extremums.size(); ++i) {
//        std::cout << extremums[i].value << ' ';
//    }
//    std::cout << '\n';
    return extremums;
}

std::vector<int64_t> FindLongestAlternateSubsequence(const std::vector<int64_t> &sequence) {
    
    std::vector<int64_t> different_neighbours;
    ExtractLocalUnique(sequence, &different_neighbours);
    if (different_neighbours.size() <= 1) {
        return different_neighbours;
    }
    std::vector<ItemIndex> extremums = FindLocalExtremums(different_neighbours);
    std::vector<int64_t> subsequence(1, different_neighbours[0]);
    size_t seq_index = 1;
    
    for (size_t subseq_index = 1; subseq_index < extremums.size() - 1;
         ++subseq_index) {
        if (extremums[subseq_index].value < extremums[subseq_index - 1].value) {
            while (seq_index > 0 &&
                   (different_neighbours[seq_index] < extremums[subseq_index + 1].value &&
                    different_neighbours[seq_index] < subsequence.back())) {
                       --seq_index;
                   }
        } else {
            while (seq_index > 0 &&
                   (different_neighbours[seq_index] > extremums[subseq_index + 1].value &&
                    different_neighbours[seq_index] > subsequence.back())) {
                       --seq_index;
                   }
        }
        subsequence.push_back(different_neighbours[seq_index + 1]);
        seq_index = extremums[subseq_index + 1].index;
    }
    if (extremums[extremums.size() - 1].value < extremums[extremums.size() - 2].value) {
        while (seq_index < different_neighbours.size() &&
               (different_neighbours[seq_index] < subsequence.back())) {
                   --seq_index;
               }
    } else {
        while (seq_index > 0 &&
               (different_neighbours[seq_index] > subsequence.back())) {
                   --seq_index;
               }
    }
    subsequence.push_back(different_neighbours[seq_index + 1]);
    return subsequence;
}

void TaskFunc() {
    std::vector<int64_t> sequence;
    size_t sequence_length;
    std::cin >> sequence_length;
    for (size_t i = 0; i < sequence_length; ++i) {
        int64_t element;
        std::cin >> element;
        sequence.push_back(element);
    }
    
    std::vector<int64_t> alternate_subsequence = FindLongestAlternateSubsequence(sequence);
    for (size_t i = 0; i < alternate_subsequence.size(); ++i) {
        std::cout << alternate_subsequence[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    
    
    TaskFunc();
    return 0;
}
