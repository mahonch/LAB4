#include <iostream>
#include <stack>
#include <string>
#include <cmath>

using namespace std;

bool isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        return true;
    }
    return false;
}

bool isNumericDigit(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    }
    if (c == '.') {
        return true;
    }
    return false;
}

int getOperatorWeight(char op) {
    int weight = -1;
    switch (op) {
    case '+':
    case '-':
        weight = 1;
        break;
    case '*':
    case '/':
        weight = 2;
        break;
    case '^':
        weight = 3;
        break;
    }
    return weight;
}

bool hasHigherPrecedence(char op1, char op2) {
    int op1Weight = getOperatorWeight(op1);
    int op2Weight = getOperatorWeight(op2);
    if (op1Weight == op2Weight) {
        if (op1 == '^') {
            return false;
        }
        return true;
    }
    return op1Weight > op2Weight ? true : false;
}

double evaluatePostfix(string expression) {
    stack<double> S;
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ' || expression[i] == ',') {
            continue;
        }
        else if (isOperator(expression[i])) {
            double operand2 = S.top();
            S.pop();
            double operand1 = S.top();
            S.pop();
            switch (expression[i]) {
            case '+':
                S.push(operand1 + operand2);
                break;
            case '-':
                S.push(operand1 - operand2);
                break;
            case '*':
                S.push(operand1 * operand2);
                break;
            case '/':
                S.push(operand1 / operand2);
                break;
            case '^':
                S.push(pow(operand1, operand2));
                break;
            }
        }
        else if (isNumericDigit(expression[i])) {
            string operand = "";
            while (i < expression.length() && (isNumericDigit(expression[i]))) {
                operand += expression[i];
                i++;
            }
            i--;
            S.push(stod(operand));
        }
    }
    return S.top();
}

string infixToPostfix(string expression) {
    stack<char> S;
    string postfix = "";
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ' || expression[i] == ',') {
            continue;
        }
        else if (isOperator(expression[i])) {
            while (!S.empty() && S.top() != '(' && hasHigherPrecedence(S.top(), expression[i])) {
                postfix += S.top();
                S.pop();
            }
            S.push(expression[i]);
        }
        else if (isNumericDigit(expression[i])) {
            string operand = "";
            while (i < expression.length() && (isNumericDigit(expression[i]))) {
                operand += expression[i];
                i++;
            }
            i--;
            postfix += operand;
            postfix += " ";
        }
        else if (expression[i] == '(') {
            S.push(expression[i]);
        }
        else if (expression[i] == ')') {
            while (!S.empty() && S.top() != '(') {
                postfix += S.top();
                S.pop();
            }
            S.pop();
        }
    }
    while (!S.empty()) {
        postfix += S.top();
        S.pop();
    }
    return postfix;
}

int main() {
    setlocale(LC_ALL, "Ru");
    string expression;
    cout << "Введите выражение: ";
    getline(cin, expression);
    string postfix = infixToPostfix(expression);
    cout << "Выражение в постфиксной записи: " << postfix << endl;
    double result = evaluatePostfix(postfix);
    cout << "Результат вычисления: " << result << endl;
    return 0;
}