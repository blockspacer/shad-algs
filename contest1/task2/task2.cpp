#include <iostream>
#include <stack>
#include <string>

/* INPUT
(())
*/

void TaskFunc() {
    std::string input;
    // std::ios_base();
    std::stack<char> braces;
    size_t alpha = 0;
    std::cin >> input;
    for (char elem : input) {
        if ((elem == '{') || (elem == '[') || (elem == '(')) {
            braces.push(elem);
            alpha++;
        } else if ((elem == '}') && (braces.size() != 0)) {
            if (braces.top() == '{') {
                braces.pop();
                alpha++;
            } else {
                std::cout << alpha << '\n';
                return;
            }
        } else if ((elem == ']') && (braces.size() != 0)) {
            if (braces.top() == '[') {
                braces.pop();
                alpha++;
            } else {
                std::cout << alpha << '\n';
                return;
            }
        } else if ((elem == ')') && (braces.size() != 0)) {
            if (braces.top() == '(') {
                braces.pop();
                alpha++;
            } else {
                std::cout << alpha << '\n';
                return;
            }
        } else {
            std::cout << alpha << '\n';
            return;
        }
    }
    if (braces.size() == 0) {
        std::cout << "CORRECT" << '\n';
    } else {
        std::cout << alpha << '\n';
    }
}


int main() {
    TaskFunc();
    return 0;
}
