// homework2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <cctype>
#include <map>

using namespace std;

// 優先權映射
map<char, int> precedence = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2}
};

// 檢查括號是否對稱的函式
bool isBalanced(const string& expression) {
    stack<char> s;  // 使用堆疊來存放開括號
    for (char c : expression) {
        if (c == '(') {
            s.push(c);  // 遇到開括號，推入堆疊
        }
        else if (c == ')') {
            if (s.empty()) return false;  // 如果堆疊為空，則表示不對稱
            s.pop();  // 遇到閉括號，彈出堆疊頂端的開括號
        }
    }
    return s.empty();  // 如果堆疊空，表示括號對稱
}

// 將中序表示法轉換為後序表示法的函式
string infixToPostfix(const string& expression) {
    stack<char> s;  // 堆疊用來存放運算符
    string postfix;  // 存放後序表示法的結果
    for (char c : expression) {
        if (isdigit(c)) {
            postfix += c;  // 遇到數字，直接加到後序結果中
        }
        else if (c == '(') {
            s.push(c);  // 遇到開括號，推入堆疊
        }
        else if (c == ')') {
            // 遇到閉括號，將堆疊中的運算符彈出，直到遇到開括號
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();  // 將運算符加到後序結果
                s.pop();
            }
            s.pop();  // 去掉 '('
        }
        else {
            // 遇到運算符，處理優先級
            while (!s.empty() && precedence[s.top()] >= precedence[c]) {
                postfix += s.top();  // 將優先級高的運算符加到後序結果
                s.pop();
            }
            s.push(c);  // 將當前運算符推入堆疊
        }
    }
    // 將堆疊中剩餘的運算符全部彈出
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    return postfix;  // 返回後序表示法
}

// 計算後序表示法結果的函式
int evaluatePostfix(const string& postfix) {
    stack<int> s;  // 堆疊用來存放操作數
    for (char c : postfix) {
        if (isdigit(c)) {
            s.push(c - '0');  // 將字符數字轉為整數並推入堆疊
        }
        else {
            // 遇到運算符，從堆疊中彈出兩個數字進行計算
            int b = s.top(); s.pop();  // 取出第二個操作數
            int a = s.top(); s.pop();  // 取出第一個操作數
            switch (c) {
            case '+': s.push(a + b); break;  // 加法
            case '-': s.push(a - b); break;  // 減法
            case '*': s.push(a * b); break;  // 乘法
            case '/': s.push(a / b); break;  // 除法
            }
        }
    }
    return s.top();  // 返回堆疊頂端的計算結果
}

int main() {
    string expression;  // 用來儲存運算式
    char continueTesting;  // 用來決定是否繼續測試

    do {
        cout << "請輸入一個運算式（包含1~9和運算符號 +, -, *, /, (, )）：";
        cin >> expression;  // 讀取使用者輸入的運算式

        // 檢查括號是否對稱
        if (!isBalanced(expression)) {
            cout << expression << " 運算式的左右括號不對稱，無法繼續運算" << endl;
        }
        else {
            cout << expression << " 運算式的左右括號對稱" << endl;

            // 將中序運算式轉換為後序運算式
            string postfix = infixToPostfix(expression);
            cout << expression << " 運算式的後序表式法為： " << postfix << endl;

            // 計算後序運算式的結果
            int result = evaluatePostfix(postfix);
            cout << expression << " 運算式的運算結果為： " << result << endl;
        }

        // 詢問使用者是否繼續測試
        cout << "是否繼續測試？(Y/y: 繼續，其他鍵: 離開) ";
        cin >> continueTesting;

    } while (continueTesting == 'Y' || continueTesting == 'y');  // 根據使用者選擇重複或退出

    return 0;  // 程式結束
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
