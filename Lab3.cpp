#include <iostream>
#include <stack>
#include <string>

bool isBalanced(const std::string& expr) {
    std::stack<char> bracketStack;

    for (char ch : expr) {
        // Push any opening brackets
        if (ch == '(' || ch == '{' || ch == '[') {
            bracketStack.push(ch);
        }
        // check for closing brackets and try to match
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (bracketStack.empty()) return false; // No match for closing bracket
            char openBracket = bracketStack.top();
            bracketStack.pop();
            // makes sure each closing bracket matches the correct opening type
            if ((ch == ')' && openBracket != '(') ||
                (ch == '}' && openBracket != '{') ||
                (ch == ']' && openBracket != '[')) {
                return false;
            }
        }
    }
    // All brackets matched if stack is empty
    return bracketStack.empty();
}

int main() {
    std::string expr;

    std::cout << "Enter an expression to check for balanced brackets: ";
    std::getline(std::cin, expr);

    if (isBalanced(expr)) {
        std::cout << "Balanced brackets!\n";
    } else {
        std::cout << "Unbalanced brackets.\n";
    }

    return 0;
}
