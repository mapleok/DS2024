#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>

// 优先级表，这里只包含简单的四则运算，可根据需要扩展
std::unordered_map<char, int> priority = {
    {'(', 0},
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2}
};

double calculate(std::string expression) {
    Stack<double> operandStack;
    Stack<char> operatorStack;

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (isdigit(c) || c == '.') {
            std::string numberStr;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                numberStr += expression[i++];
            }
            i--;
            operandStack.push(std::stod(numberStr));
        } else if (c == '(') {
            operatorStack.push(c);
        } else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.peek()!= '(') {
                double operand2 = operandStack.pop();
                double operand1 = operandStack.pop();
                char op = operatorStack.pop();
                double result = 0;
                switch (op) {
                    case '+':
                        result = operand1 + operand2;
                        break;
                    case '-':
                        result = operand1 - operand2;
                        break;
                    case '*':
                        result = operand1 * operand2;
                        break;
                    case '/':
                        if (operand2 == 0) {
                            std::cerr << "Division by zero" << std::endl;
                            return 0;
                        }
                        result = operand1 / operand2;
                        break;
                }
                operandStack.push(result);
            }
            if (!operatorStack.empty() && operatorStack.peek() == '(') {
                operatorStack.pop();
            }
        } else {
            while (!operatorStack.empty() && priority[operatorStack.peek()] >= priority[c]) {
                double operand2 = operandStack.pop();
                double operand1 = operandStack.pop();
                char op = operatorStack.pop();
                double result = 0;
                switch (op) {
                    case '+':
                        result = operand1 + operand2;
                        break;
                    case '-':
                        result = operand1 - operand2;
                        break;
                    case '*':
                        result = operand1 * operand2;
                        break;
                    case '/':
                        if (operand2 == 0) {
                            std::cerr << "Division by zero" << std::endl;
                            return 0;
                        }
                        result = operand1 / operand2;
                        break;
                }
                operandStack.push(result);
            }
            operatorStack.push(c);
        }
    }

    while (!operatorStack.empty()) {
        double operand2 = operandStack.pop();
        double operand1 = operandStack.pop();
        char op = operatorStack.pop();
        double result = 0;
        switch (op) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                if (operand2 == 0) {
                    std::cerr << "Division by zero" << std::endl;
                    return 0;
                }
                result = operand1 / operand2;
                break;
        }
        operandStack.push(result);
    }

    return operandStack.pop();
}

// 案例测试
int main() {
    std::string expression1 = "(1+2)*3";
    std::cout << "Result of " << expression1 << ": " << calculate(expression1) << std::endl;

    std::string expression2 = "1+2*3";
    std::cout << "Result of " << expression2 << ": " << calculate(expression2) << std::endl;

    std::string expression3 = "((2-3)*(4+5))";
    std::cout << "Result of " << expression3 << ": " << calculate(expression3) << std::endl;

    return 0;
}
