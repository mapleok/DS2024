#include <vector>
#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>

// 计算柱状图中最大矩形面积
int largestRectangleArea(const std::vector<int>& heights) {
    std::stack<int> stack;
    int maxArea = 0;
    int i = 0;
    int n = heights.size();

    while (i < n) {
        if (stack.empty() || heights[i] >= heights[stack.top()]) {
            stack.push(i);
            i++;
        } else {
            int topIndex = stack.top();
            stack.pop();
            int width = stack.empty()? i : i - stack.top() - 1;
            int area = heights[topIndex] * width;
            maxArea = std::max(maxArea, area);
        }
    }

    while (!stack.empty()) {
        int topIndex = stack.top();
        stack.pop();
        int width = stack.empty()? n : n - stack.top() - 1;
        int area = heights[topIndex] * width;
        maxArea = std::max(maxArea, area);
    }

    return maxArea;
}

// 随机生成数据并测试柱状图面积计算
void testLargestRectangleArea() {
    std::srand(static_cast<unsigned int>(time(nullptr)));
    const int numTests = 10;
    const int maxLength = 105;
    const int maxHeight = 104;

    for (int k = 0; k < numTests; k++) {
        int length = std::rand() % maxLength + 1;
        std::vector<int> heights(length);
        for (int i = 0; i < length; i++) {
            heights[i] = std::rand() % maxHeight;
        }

        std::cout << "测试 " << k + 1 << " - 高度: ";
        for (int height : heights) {
            std::cout << height << " ";
        }
        std::cout << ", 最大矩形面积: " << largestRectangleArea(heights) << std::endl;
    }
}

int main() {
    std::cout << "表达式计算器测试:\n";
    testExpressionCalculator();
    std::cout << "\n柱状图最大矩形面积计算测试:\n";
    testLargestRectangleArea();
    return 0;
}
