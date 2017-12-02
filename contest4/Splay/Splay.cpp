#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <time.h>


/* INPUT
 3
 -3 -3 3 3
 -2 2 2 -2
 -1 -1 1 1
 */


template<class T>
class SplayTree {
public:
    struct Node {
        std::shared_ptr<Node> left_child_;
        std::shared_ptr<Node> right_child_;
        std::shared_ptr<Node> parent_;
        T key_;
        
        Node(const T& key = T(), std::shared_ptr<Node> left = std::shared_ptr<Node>(), std::shared_ptr<Node> right = std::shared_ptr<Node>()) : left_child_(left), right_child_(right), parent_(nullptr), key_(key) {}
        
        
    };
    std::shared_ptr<Node> root_;
    
    void KeepParent_(std::shared_ptr<Node> vertex) {
        if (vertex == nullptr) {
            throw std::runtime_error("nullptr\n");
        }
        if (vertex->left_child_.get() != nullptr) {
            vertex->left_child_->parent_ = vertex;
        }
        if (vertex->right_child_.get() != nullptr) {
            vertex->right_child_->parent_ = vertex;
        }
    }
    
    void Rotate_(std::shared_ptr<Node> parent, std::shared_ptr<Node> child) {
        std::shared_ptr<Node> gparent = parent->parent_;
        
        if (gparent.get() != nullptr) {
            if (gparent->left_child_ == parent) {
                gparent->left_child_ = child;
            } else {
                gparent->right_child_ = child;
            }
        } else {
            // root_ = child;
        }
        
        if (parent->left_child_ == child) {
            parent->left_child_ = child->right_child_;
            child->right_child_ = parent;
        } else {
            parent->right_child_ = child->left_child_;
            child->left_child_ = parent;
        }
        KeepParent_(child);
        KeepParent_(parent);
        child->parent_ = gparent;
    }
    
    std::shared_ptr<Node> Splay_(std::shared_ptr<Node> vertex) {
        std::shared_ptr<Node> parent;
        std::shared_ptr<Node> gparent;
        while (vertex->parent_.get() != nullptr) {
            // std::cout << "one more step\n";
            parent = vertex->parent_;
            gparent = parent->parent_;
            if (gparent.get() == nullptr) {
                // std::cout << "no granny\n";
                Rotate_(parent, vertex);
            } else {
                if ((gparent->left_child_ == parent)
                    == (parent->left_child_ == vertex)) {
                    Rotate_(gparent, parent);
                    Rotate_(parent, vertex);
                } else {
                    Rotate_(parent, vertex);
                    Rotate_(gparent, vertex);
                }
            }
        }
        return vertex;
    }
    
    std::shared_ptr<Node> Search_(std::shared_ptr<Node> vertex, const T& key) {
        if (vertex.get() == nullptr) {
            return std::shared_ptr<Node>();
        } else if (vertex->key_ == key) {
            Splay_(vertex);
            return vertex;
        } else if ((key < vertex->key_) && (vertex->left_child_.get() != nullptr)) {
            return Search_(vertex->left_child_, key);
        } else if ((key > vertex->key_) && (vertex->right_child_.get() != nullptr)) {
            return Search_(vertex->right_child_, key);
        }
        Splay_(vertex);
        return vertex;
    }
    
    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> Split_(std::shared_ptr<Node> root, const T& key) {
        if (root.get() == nullptr) {
            return std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>(std::shared_ptr<Node>(), std::shared_ptr<Node>());
        }
        root = Search_(root, key);
        if (root->key_ == key) {
            if (root->left_child_.get() != nullptr) {
                root->left_child_->parent_ = std::shared_ptr<Node>();
            }
            if (root->right_child_.get() != nullptr) {
                root->right_child_->parent_ = std::shared_ptr<Node>();
            }
            return std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> (root->left_child_, root->right_child_);
        }
        if (root->key_ < key) {
            if (root->right_child_.get() == nullptr) {
                return std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> (root, std::shared_ptr<Node>());
            }
            std::shared_ptr<Node> right = root->right_child_;
            right->parent_ = std::shared_ptr<Node>();
            root->right_child_ = std::shared_ptr<Node>();
            return std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> (root, right);
        } else {
            if (root->left_child_.get() == nullptr) {
                return std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> (std::shared_ptr<Node>(), root);
            }
            std::shared_ptr<Node> left = root->left_child_;
            left->parent_ = std::shared_ptr<Node>();
            root->left_child_ = std::shared_ptr<Node>();
            return std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> (left, root);
        }

    }
    
    std::shared_ptr<Node> Insert_(std::shared_ptr<Node> root, const T& key) {
        std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> left_and_right = Split_(root, key);
        if ((left_and_right.second.get() != nullptr) && (left_and_right.second->key_ == key)) {
            //throw std::runtime_error("inserting an element that is already inside a tree\n");
            return Merge_(left_and_right.first, left_and_right.second);
        }
        root = std::make_shared<Node>(key, left_and_right.first, left_and_right.second);
        KeepParent_(root);
        return root;
    }
    
    std::shared_ptr<Node> Merge_(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
        if (left.get() == nullptr) {
            return right;
        }
        if (right.get() == nullptr) {
            return left;
        }
        right = Search_(right, left->key_);
        left->parent_ = right;
        right->left_child_ = left;
        return right;
    }
    
    std::shared_ptr<Node> Remove_(std::shared_ptr<Node> root, const T& key) {
        if (root.get() == nullptr) {
            throw std::runtime_error("trying to remove from empty tree\n");
        }
        root = Search_(root, key);
        if (root->left_child_.get() != nullptr) {
            root->left_child_->parent_ = std::shared_ptr<Node>();
        }
        if (root->right_child_.get() != nullptr) {
            root->right_child_->parent_ = std::shared_ptr<Node>();
        }
        return Merge_(root->left_child_, root->right_child_);
    }
    
    std::shared_ptr<Node> Max_(std::shared_ptr<Node> root) {
        if (root.get() == nullptr) {
            return std::shared_ptr<Node>();
        }
        while (root->right_child_.get() != nullptr) {
            root = root->right_child_;
        }
        return Splay_(root);
    }
    
    void Insert(const T& key) {
        root_ = Insert_(root_, key);
    }
    
    void Remove(const T& key) {
        root_ = Remove_(root_, key);
    }
    
    bool Search(const T& key) {
        if (root_.get() == nullptr) {
            return false;
        }
        root_ = Search_(root_, key);
        return root_->key_ == key;
    }
    
    bool IsEmpty() {
        return root_.get() == nullptr;
    }
    
    void print_(std::shared_ptr<Node> vertex) {
        if (vertex.get() != nullptr) {
            print_(vertex->left_child_);
            std::cout << "my key is " << vertex->key_ <<
            " | " <<
            "my left_child is " <<
            (vertex->left_child_.get() != nullptr ? vertex->left_child_->key_ : T()) <<
            " | " <<
            "my right child is " <<
            (vertex->right_child_.get() != nullptr ? vertex->right_child_.get()->key_ : T()) <<
            " | " <<
            "my parent is " <<
            (vertex->parent_.get() != nullptr ? vertex->parent_.get()->key_ : T()) <<
            "\n";
            print_(vertex->right_child_);
        }
        
    }
    
    void Print() {
        std::cout << "Printing tree\n==========================================\n";
        print_(root_);
        std::cout << "==========================================\nDone printing\n";
    }
public:
    
};


struct segment {
    int64_t x_axis;
    int64_t start;
    int64_t finish;
    bool is_left;
};

std::ostream& operator<<(std::ostream& out, const segment& x) {
    out << x.x_axis << " " << x.start << " " << x.finish;
    return out;
}

bool operator==(const segment& first, const segment& second) {
    return ((first.start == second.start) && (first.finish == second.finish));
}

bool operator<(const segment& first, const segment& second) {
    return first.start < second.start;
}

bool operator>(const segment& first, const segment& second) {
    return first.start > second.start;
}

bool is_inside(const segment& first, const segment& second) {
    return (first.start < second.start) && (first.finish > second.finish);
}

class Comaparator {
public:
    Comaparator() {}
    bool operator()(const segment& first, const segment& second) {
        return first.x_axis < second.x_axis;
    }
        };

void TaskFunc() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    SplayTree<segment> tree;
    std::vector<segment> segs;
    size_t num_of_rects;
    int64_t first, second, third, fourth;
    std::cin >> num_of_rects;
    segment helper;
    for (size_t i = 0; i < num_of_rects; ++i) {
        std::cin >> first >> second >> third >> fourth;
        helper.x_axis = std::min(first, third);
        helper.start = std::min(second, fourth);
        helper.finish = std::max(second, fourth);
        helper.is_left = true;
        segs.push_back(helper);
        helper.x_axis = std::max(first, third);
        helper.is_left = false;
        segs.push_back(helper);
    }
    clock_t time;
    time = clock();
    std::sort(segs.begin(), segs.end(), Comaparator());
    size_t counter = 0;
    for (size_t i = 0; i < segs.size(); ++i) {
        //std::cout << segs[i]. << '\n';
        if (segs[i].is_left) {
            if (tree.Search(segs[i])) {
                throw std::runtime_error("same segment twice\n");
            } else if (tree.IsEmpty()) {
                tree.Insert(segs[i]);
                counter++;
            } else if (is_inside(tree.root_->key_, segs[i])) {
                //tree.Insert(segs[i]);
            } else if (tree.root_->left_child_.get() != nullptr) {
                if (is_inside(tree.root_->left_child_->key_, segs[i])) {
                    
                } else {
                    tree.Insert(segs[i]);
                    counter++;
                }
            } else {
                tree.Insert(segs[i]);
                counter++;
            }
        } else {
            if (tree.Search(segs[i])) {
                // std::cout << segs[i] << '\n';
                tree.Remove(tree.root_->key_);
            }
        }
    }
    std::cout << static_cast<float>(clock() - time) / CLOCKS_PER_SEC << '\n';
    std::cout << counter << '\n';
}

int main() {
    
    TaskFunc();
    
    return 0;
}

