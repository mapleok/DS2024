#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <cctype>

// 操作符类型枚举
enum class OperatorType {
    ADD, SUB, MUL, DIV, POW, FACTORIAL, SIN, COS, TAN, LOG10, LN, LPAR, RPAR, END, NEGATIVE
};

// 操作符优先级表
const int priorityTable[][13] = {
    // ADD, SUB, MUL, DIV, POW, FACTORIAL, SIN, COS, TAN, LOG10, LN, LPAR, RPAR
    {1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1},  // ADD
    {1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1},  // SUB
    {1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, 1},  // MUL
    {1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, 1},  // DIV
    {1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, 1},   // POW
    {1, 1, 1, 1, 1, 2, -1, -1, -1, -1, -1, -1, 1},   // FACTORIAL
    {1, 1, 1, 1, 1, -1, 1, -1, -1, -1, -1, -1, 1},   // SIN
    {1, 1, 1, 1, 1, -1, -1, 1, -1, -1, -1, -1, 1},   // COS
    {1, 1, 1, 1, 1, -1, -1, -1, 1, -1, -1, -1, 1},   // TAN
    {1, 1, 1, 1, 1, -1, -1, -1, -1, 1, -1, -1, 1},   // LOG10
    {1, 1, 1, 1, 1, -1, -1, -1, -1, -1, 1, -1, 1},   // LN
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},  // LPAR
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},          // RPAR
    {1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, 1},   // END
    {1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1}   // NEGATIVE
};

// 将字符操作符转换为操作符类型
OperatorType charToOperatorType(char op) {
    switch (op) {
    case '+': return OperatorType::ADD;
    case '-': return OperatorType::SUB;
    case '*': return OperatorType::MUL;
    case '/': return OperatorType::DIV;
    case '^': return OperatorType::POW;
    case '!': return OperatorType::FACTORIAL;
    case '(': return OperatorType::LPAR;
    case ')': return OperatorType::RPAR;
    case '\0': return OperatorType::END;
    case's': return OperatorType::SIN;
    case 'c': return OperatorType::COS;
    case 't': return OperatorType::TAN;
    case 'g': return OperatorType::LOG10;
    case 'l': return OperatorType::LN;
    case 'n': return OperatorType::NEGATIVE;
    default: throw std::runtime_error("Invalid operator");
    }
}

// 比较两个操作符的优先级
int comparePriority(OperatorType op1, OperatorType op2) {
    return priorityTable[static_cast<int>(op1)][static_cast<int>(op2)];
}

// 从字符串中读取数字
double readNumber(const char*& s) {
    double num = 0;
    double decimal = 1;
    bool isDecimal = false;
    if (*s == '-') {
        s++;
        num = -1;
    } else {
        num = 0;
    }
    while (isdigit(*s) || *s == '.') {
        if (*s == '.') {
            isDecimal = true;
        } else if (isDecimal) {
            decimal *= 0.1;
            num += (*s - '0') * decimal;
        } else {
            num = num * 10 + (*s - '0');
        }
        s++;
    }
    return num;
}

// 执行计算（二元操作）
double calculateBinary(double op1, OperatorType op, double op2) {
    switch (op) {
    case OperatorType::ADD: return op1 + op2;
    case OperatorType::SUB: return op1 - op2;
    case OperatorType::MUL: return op1 * op2;
    case OperatorType::DIV:
        if (op2 == 0) {
            throw std::runtime_error("Division by zero");
        }
        return op1 / op2;
    case OperatorType::POW: return std::pow(op1, op2);
    default: throw std::runtime_error("Invalid binary operator");
    }
}

// 执行计算（一元操作）
double calculateUnary(OperatorType op, double opnd) {
    switch (op) {
    case OperatorType::FACTORIAL: {
        int n = static_cast<int>(opnd);
        if (n < 0 || n!= opnd) {
            throw std::runtime_error("Factorial requires non - negative integer.");
        }
        double result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }
    case OperatorType::SIN: return std::sin(opnd);
    case OperatorType::COS: return std::cos(opnd);
    case OperatorType::TAN: return std::tan(opnd);
    case OperatorType::LOG10: return std::log10(opnd);
    case OperatorType::LN: return std::log(opnd);
    case OperatorType::NEGATIVE: return -opnd;
    default: throw std::runtime_error("Invalid unary operator");
    }
}

// 计算表达式的值
double evaluateExpression(const char* expression) {
    std::stack<double> operands;
    std::stack<OperatorType> operators;
    operators.push(OperatorType::END);

    const char* s = expression;
    while (*s!= '\0' || operators.top()!= OperatorType::END) {
        if (isdigit(*s) || *s == '-' && (s == expression ||!isdigit(*(s - 1)) && * (s - 1)!= ')')) {
            double num = readNumber(s);
            operands.push(num);
        } else {
            OperatorType currentOp = charToOperatorType(*s);
            if (currentOp == OperatorType::LPAR) {
                operators.push(currentOp);
                s++;
            } else if (currentOp == OperatorType::RPAR) {
                while (operators.top()!= OperatorType::LPAR) {
                    OperatorType op = operators.top();
                    operators.pop();
                    if (op == OperatorType::FACTORIAL || op == OperatorType::SIN || op == OperatorType::COS || op == OperatorType::TAN || op == OperatorType::LOG10 || op == OperatorType::LN || op == OperatorType::NEGATIVE) {
                        double opnd = operands.top();
                        operands.pop();
                        operands.push(calculateUnary(op, opnd));
                    } else {
                        double op2 = operands.top();
                        operands.pop();
                        double op1 = operands.top();
                        operands.pop();
                        operands.push(calculateBinary(op1, op, op2));
                    }
                }
                operators.pop(); // 弹出 '('
                s++;
            } else {
                int prioComp = comparePriority(operators.top(), currentOp);
                if (prioComp == -1) {
                    operators.push(currentOp);
                    s++;
                } else if (prioComp == 1) {
                    OperatorType op = operators.top();
                    operators.pop();
                    if (op == OperatorType::FACTORIAL || op == OperatorType::SIN || op == OperatorType::COS || op == OperatorType::TAN || op == OperatorType::LOG10 || op == OperatorType::LN || op == OperatorType::NEGATIVE) {
                        double opnd = operands.top();
                        operands.pop();
                        operands.push(calculateUnary(op, opnd));
                    } else {
                        double op2 = operands.top();
                        operands.pop();
                        double op1 = operands.top();
                        operands.pop();
                        operands.push(calculateBinary(op1, op, op2));
                    }
                } else {
                    throw std::runtime_error("Invalid expression");
                }
            }
        }
    }

    return operands.top();
}

// 测试表达式计算器
void testExpressionCalculator() {
    std::string expressions[] = {"1+2*3", "(1+2)*3", "sin(0.5)+cos(0.5)", "log(100)", "2-10", "1+sin(5)"};
    for (const auto& exp : expressions) {
        try {
            double result = evaluateExpression(exp.c_str());
            std::cout << "表达式: " << exp << ", 结果: " << result << std::endl;
        } catch (const std::runtime_error& error) {
            std::cerr << "表达式: " << exp << ", 错误: " << error.what() << std::endl;
        }
    }
}
