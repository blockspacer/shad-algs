#include <iostream>
#include <stack>
#include <vector>
// #include <testing.h>
// #include <random>

template <class T>
struct MaxFriend {
    T Me;
    T MyMaximalFriend;
};

template <class T>
class MyStack {
public:
    MyStack() {
    }
    
    T Top() {
        if (stack.empty()) {
            // throw std::runtime_error("stack_is_empty");
        }
        return stack.top().Me;
    }
    
    void Pop() {
        if (stack.empty()) {
            // throw std::runtime_error("stack_is_empty");
        }
        stack.pop();
    }
    
    void Push(T help) {
        MaxFriend<T> helper;
        helper.Me = help;
        if (!stack.empty()) {
            helper.MyMaximalFriend =
                help > stack.top().MyMaximalFriend ? help: stack.top().MyMaximalFriend;
        } else {
            helper.MyMaximalFriend = help;
        }
        stack.push(helper);
    }
    
    T Max() {
        return stack.top().MyMaximalFriend;
    }
    
    bool Empty() {
        return stack.empty();
    }
    
private:
    std::stack<MaxFriend<T>> stack;
};

// void StackCheck() {
//    MyStack<int> stack;
//    int helper;
//    std::string text;
//    std::cin >> text;
//    if (text == "pop") {
//        stack.Pop();
//    } else if (text == "top") {
//        std::cout << stack.Top() << std::endl;
//    } else if (text == "push") {
//        std::cin >> helper;
//        stack.Push(helper);
//    } else if (text == "max") {
//        std::cout << stack.Max() <<std::endl;
//    }
//    while (text != "quit") {
//        std::cin >> text;
//        if (text == "pop") {
//            stack.Pop();
//        } else if (text == "top") {
//            std::cout << stack.Top() << std::endl;
//        } else if (text == "push") {
//            std::cin >> helper;
//            stack.Push(helper);
//        } else if (text == "max") {
//            std::cout << stack.Max() <<std::endl;
//        }
//    }
// }

template <class T>
class MyQueue {
public:
    MyQueue() {
    }
    
    bool Empty() {
        return stack_one.Empty() && stack_two.Empty();
    }
    
    T Top() {
        T helper;
        if (this->Empty()) {
            // throw std::runtime_error("no top queue is empty");
        } else if (stack_two.Empty()) {
            while (!stack_one.Empty()) {
                helper= stack_one.Top();
                stack_one.Pop();
                stack_two.Push(helper);
            }
        }
        return stack_two.Top();
    }
    
    void Pop() {
        T helper;
        if (this->Empty()) {
            // throw std::runtime_error("no pop queue is empty");
        } else if (stack_two.Empty()) {
            while (!stack_one.Empty()) {
                helper= stack_one.Top();
                stack_one.Pop();
                stack_two.Push(helper);
            }
        }
        return stack_two.Pop();
    }
    
    void Push(T helper) {
        stack_one.Push(helper);
    }
    
    T Max() {
        if (this->Empty()) {
            // throw std::runtime_error("queue is empty");
        } else if (stack_one.Empty()) {
            return stack_two.Max();
        } else if (stack_two.Empty()) {
            return stack_one.Max();
        }
        return stack_one.Max() > stack_two.Max() ? stack_one.Max() : stack_two.Max();
    }
    
private:
    MyStack<T> stack_one;
    MyStack<T> stack_two;
};

// void QueueCheck() {
//    MyQueue<int> queue;
//    int helper;
//    std::string text;
//    std::cin >> text;
//    if (text == "pop") {
//        queue.Pop();
//    } else if (text == "top") {
//        std::cout << queue.Top() << std::endl;
//    } else if (text == "push") {
//        std::cin >> helper;
//        queue.Push(helper);
//    } else if (text == "max") {
//        std::cout << queue.Max() <<std::endl;
//    }
//    while (text != "quit") {
//        std::cin >> text;
//        if (text == "pop") {
//            queue.Pop();
//        } else if (text == "top") {
//            std::cout << queue.Top() << std::endl;
//        } else if (text == "push") {
//            std::cin >> helper;
//            queue.Push(helper);
//        } else if (text == "max") {
//            std::cout << queue.Max() <<std::endl;
//        }
//    }
// }

// template<class Iterator, class T>
// T Max(const Iterator first, const Iterator last) {
//    //std::cout << "in here" << std::endl;
//    T max = *first;
//    Iterator it1 = first;
//    Iterator it2 = last;
//    it2++;
//    while (it1 != it2) {
//        //std::cout << "in here" << std::endl;
//        if (*it1 > max) {
//            max = *it1;
//            //std::cout << *it1 << std::endl;
//        }
//        it1++;
//    }
//    
//    return max;
// }



std::vector<int64_t> MyMethod(const std::vector<int64_t>& input, const std::vector<char>& letters) {
    std::vector<int64_t> res;
    std::vector<int64_t>::const_iterator it;
    MyQueue<int64_t> queue;
    it = input.begin();
    queue.Push(*it);
    for (size_t i = 0; i < letters.size(); ++i) {
        if (letters[i] == 'R') {
            it++;
            queue.Push(*it);
        } else if (letters[i] == 'L') {
            queue.Pop();
        }
        res.push_back(queue.Max());
    }
    return res;
}

void TaskMethod() {
    size_t num, mun;
    std::vector<int64_t> vect;
    std::vector<char> letters;
    std::vector<int64_t> res;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> num;
    vect.resize(num);
    for (size_t i = 0; i < vect.size(); ++i) {
        std::cin >> vect[i];
    }
    std::cin >> mun;
    letters.resize(mun);
    for (size_t i = 0; i < letters.size(); ++i) {
        std::cin >> letters[i];
    }
    res = MyMethod(vect, letters);
    for (int64_t elem : res) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

int main() {
    // stress_test::TaskFunc();
    TaskMethod();
    return 0;
}


