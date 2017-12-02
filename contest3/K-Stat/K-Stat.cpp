#include <iostream>
#include <vector>
#include <algorithm>
#include <random>


struct Node {
    int64_t key;
    int64_t prior;
    Node* left;
    Node* right;
    Node() { }
    Node (int64_t key, int64_t prior) : key(key), prior(prior), left(nullptr), right(nullptr) { }
    int64_t subtrnum = 1;
};



void UpdateSub(Node* tree);


void Split(Node* ttt, int64_t key, Node* & left, Node* & right) {
    if (ttt == nullptr) {
        left = right = NULL;
    } else if (key < ttt->key) {
        Split(ttt->left, key, left, ttt->left);
        right = ttt;
    } else {
        Split(ttt->right, key, ttt->right, right);
        left = ttt;
    }
    UpdateSub(ttt);
    UpdateSub(left);
    UpdateSub(right);
}


void Insert(Node* & ttt, Node* & it) {
    if (ttt == nullptr) {
        // std::cout << "tree was empty\n";
        // std::cout << it << std::endl;
        ttt = it;
        // std::cout << ttt << '\n';
    } else if (it->prior > ttt->prior) {
        Split(ttt, it->key, it->left, it->right);
        ttt = it;
    } else {
        Insert(it->key < ttt->key ? ttt->left : ttt->right, it);
    }
    UpdateSub(ttt);
    UpdateSub(it);
}


void Merge(Node* & ttt, Node* left, Node* right) {
    if ((left == nullptr) || (right == nullptr)) {
        ttt = left ? left : right;
    } else if (left->prior > right->prior) {
        Merge(left->right, left->right, right);
        ttt = left;
    } else {
        Merge(right->left, left, right->left);
        ttt = right;
    }
    UpdateSub(ttt);
    UpdateSub(left);
    UpdateSub(right);
}


void Erase(Node* & ttt, int64_t key) {
    if (ttt->key == key) {
        Merge(ttt, ttt->left, ttt->right);
    } else {
        Erase(key < ttt->key ? ttt->left : ttt->right, key);
    }
    UpdateSub(ttt);
}


Node* Unite(Node* left, Node* right) {
    if ((left == nullptr) || (right == nullptr)) {
        return left ? left : right;
    }
    if (left->prior < right->prior) {
        std::swap(left, right);
    }
    Node* lefttree;
    Node* righttree;
    Split(right, left->key, lefttree, righttree);
    left->left = Unite(left->left, lefttree);
    left->right = Unite(left->right, righttree);
    UpdateSub(left);
    UpdateSub(right);
    return left;
}


size_t SubNum(Node* tree) {
    return tree ? tree->subtrnum : 0;
}


void UpdateSub(Node* tree) {
    if (tree != nullptr) {
        tree->subtrnum = 1 + SubNum(tree->left) + SubNum(tree->right);
    }
}


int64_t KthElement(Node* tree, size_t K_stat) {
    Node* cur = tree;
    while (cur != nullptr) {
        // std::cout << "current K is " << K_stat << '\n';
        size_t sizeLeft = SubNum(cur->left);
        
        if (sizeLeft == K_stat) {
            return cur->key;
        }
        
        cur = sizeLeft > K_stat ? cur->left : cur->right;
        if (sizeLeft < K_stat) {
            K_stat -= sizeLeft + 1;
        }
    }
    return -1;
}



void TaskFunc() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<Node> nodes;
    std::vector<int64_t> input;
    // std::vector<Node*> ptrs;
    size_t num_of_elements;
    size_t K_stat;
    size_t num_of_queries;
    std::cin >> num_of_elements >> num_of_queries >> K_stat;
    // std::cout << K_stat << '\n';
    input.resize(num_of_elements);
    nodes.resize(num_of_elements);
    int64_t num;
    std::default_random_engine generator(time(0));
    std::uniform_int_distribution<int64_t> distributor(1, 1000);
    for (size_t i = 0; i < num_of_elements; ++i) {
        std::cin >> num;
        input[i] = num;
        nodes[i] = Node(num, distributor(generator));
    }
    size_t left, right;
    left = 0;
    right = 0;
    char letter;
    Node* tree;
    // std::cout << tree << ' ' << ptrs[0] << '\n'
    Node* helper = &nodes[0];
    Insert(tree, helper);
    // std::cout << tree << ' ' << ptrs[0] << '\n';
    for (size_t ij = 0; ij < num_of_queries; ++ij) {
        std::cin >> letter;
        if (letter == 'R') {
            right++;
            helper = &nodes[right];
            Insert(tree, helper);
            std::cout << KthElement(tree, K_stat - 1) << ' ';
        } else if (letter == 'L') {
            Erase(tree, input[left]);
            left++;
            std::cout << KthElement(tree, K_stat - 1) << ' ';
        }
    }
    std::cout << '\n';
}


int main() {
    TaskFunc();
    return 0;
}
