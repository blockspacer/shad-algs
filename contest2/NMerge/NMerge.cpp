#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


template <class T>
class MinHeap {
public:
    explicit MinHeap(size_t num_of_elements) {
        elements.resize(num_of_elements);
    }
    
    bool Add(T to_add) {
        elements[size_] = to_add;
        size_++;
        SiftUp(size_ - 1);
        return true;
    }
    
    bool Extract(T* res) {
        if (size_ != 0) {
            *res = elements.front();
            elements[0] = elements[size_ - 1];
            size_--;
            SiftDown(0);
            return true;
            }
        return false;
    }
    
    void Print() {
        std::cout << "printing\n============================================\n";
        for (size_t i = 0; i < size_; ++i) {
            std::cout << elements[i].elem << ' ';
        }
        std::cout << "\n======================================\ndoneprinting\n";
    }
    
private:
    void SiftUp(size_t index) {
        size_t param = (index - 1) / 2;
        if (!(index == 0)) {
            if (elements[param] > elements[index]) {
                std::swap(elements[param], elements[index]);
                SiftUp(param);
            }
        }
    }
    
    void SiftDown(size_t index) {
        size_t param;
        param = 2 * index + 1;
        if (param <= size_) {
            
            if (param + 1 <= size_ && elements[param] > elements[param + 1]) {
                param++;
            }
            
            if (elements[index] > elements[param]) {
                std::swap(elements[param], elements[index]);
                SiftDown(param);
            }
        }
    }
    
    std::vector<T> elements;
    size_t  size_ = 0;
};

template <class T>
struct with_vec_num {
    T elem;
    size_t vec_num;
    size_t elem_num;
    
    bool operator> (const struct with_vec_num rhs) const {
        return elem > rhs.elem;
    }
    
    with_vec_num& operator=(const struct with_vec_num& rhs) {
        elem = rhs.elem;
        elem_num = rhs.elem_num;
        vec_num = rhs.vec_num;
        return *this;
    }
};

template <class T>
void read_vector(std::vector<T>* vector, size_t num_of_elements, std::ifstream& in) {
    
    
    vector->resize(num_of_elements);
    for (size_t i = 0; i < vector->size(); ++i) {
        in >> (*vector)[i];
    }
}


template <class T>
void write_vector(const std::vector<T>& vector, std::ofstream& out) {
    
    
    for (size_t i = 0; i < vector.size(); ++i) {
        out << vector[i] << ' ';
    }
    out << '\n';
}


void TaskFunc() {
    
    size_t num;
    
    struct with_vec_num<int> xum;
    std::vector<std::vector<int>> vector;
    size_t mum;
    std::ifstream in;
    in.open("input.txt");
    in >> num >> mum;
    MinHeap<struct with_vec_num<int>> heap(num);
    vector.resize(num);
    
    for (size_t i = 0; i < num; ++i) {
        read_vector(&vector[i], mum, in);
    }
    in.close();
    std::vector<int> result;
    struct with_vec_num<int> tmpum;
    for (size_t i = 0; i < num; ++i) {
        tmpum.elem = vector[i][0];
        tmpum.elem_num = 0;
        tmpum.vec_num = i;
        heap.Add(tmpum);
    }
    for (size_t i = 0; i < mum * num; ++i) {
        heap.Extract(&xum);
        result.push_back(xum.elem);
        if (xum.elem_num < vector[xum.vec_num].size() - 1) {
            tmpum.elem = vector[xum.vec_num][xum.elem_num + 1];
            tmpum.elem_num = xum.elem_num + 1;
            tmpum.vec_num = xum.vec_num;
            heap.Add(tmpum);
        }
    }
    std::ofstream out;
    out.open("output.txt");
    write_vector(result, out);
}


int main() {
    
    
    TaskFunc();
    return 0;
}
