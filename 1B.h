#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

bool Solution(const std::string& sequence, int* i) {
    std::stack<char> opening;
    std::unordered_map<char, char> match;
    match['}'] = '{';
    match[')'] = '(';
    match[']'] = '[';

    int n = int(sequence.size());

    while (*i < n) {
        if (sequence[*i] == '(' || sequence[*i] == '{' || sequence[*i] == '[') {
            opening.push(sequence[*i]);
            *i += 1;
        }
        else {
            if (opening.empty()) {
                return false;
            }
            char open = opening.top();
            opening.pop();
            if (open != match[sequence[*i]]) {
                return false;
            }
            *i += 1;
        }
    }
    return opening.empty();
}


int main() {
    std::string my_sequence;
    std::cin >> my_sequence;
    int count = 0;
    bool flag = Solution(my_sequence, &count);
    if (flag) {
        std::cout << "CORRECT" << std::endl;
    }
    else {
        std::cout << count << std::endl;
    }
    return 0;
}
