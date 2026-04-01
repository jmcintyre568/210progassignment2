#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>

#include "ArrayStack.h"

using namespace std;

// Token

struct Token {
    string value;   // number, operator, or parenthesis
};

// Tokenizer
//breaks input into tokens
vector<Token> tokenize(const string& line) {
    vector<Token> tokens;
    // TODO
    int i = 0;
    while (i < (int)line.size()) {
        //ignore whitespace
        if (isspace(line[i])) {
            i++;
            continue;
        }
        //multi digit int case
        if (isdigit(line[i])) {
            string num;
            while (i<(int)line.size() && isdigit(line[i])) {
                num += line[i++];
            }
            tokens.push_back(Token{num});
        }
        //single characters
        else {
            tokens.push_back({string(1, line[i++])});
        }
    }
    return tokens;
}

// Helpers

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

int precedence(const string& op) {
    // TODO
    if (op == "*" || op == "/") {
        return 2;
    }
    if (op=="+" || op=="-") {
        return 1;
    }
    return 0;
}
//returns true if string is non negative int
bool isNumber(const string& s) {
    if (s.empty()) {
        return false;
    }
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

void printOut(double val) {
    //if value is whole print as int
    if (val==static_cast<long long >(val)) {
        cout << static_cast<long long >(val);
    } else {
        cout << val << endl;
    }
}

// Detection
//each number is +1 depth each operator requires depth to be 2 or greater and reduces by 1; no parens allowed
bool isValidPostfix(const vector<Token>& tokens) {
    // TODO
    if (tokens.empty()) {
        return false;
    }
    int depth =0;
    for (const Token& token : tokens) {
        if (token.value == "(" || token.value == ")") {
            return false;
        }
        if (isNumber(token.value)) {
            depth++;
        } else if (isOperator(token.value)) {
            if (depth<2) return false;
            depth--;
        } else {
            return false;
        }

    } return depth == 1;

}

bool isValidInfix(const vector<Token>& tokens) {
    // TODO
    if (tokens.empty()) {
        return false;
    }
    bool hasOp = false;
    for (const Token& token : tokens) {
        if (isOperator(token.value)) {
            hasOp = true;
            break;
        }
    }
    if (!hasOp) {
        return false;
    }
    // unrecognized token check
    for (const Token& token : tokens) {
        if (!isNumber(token.value)&& !isOperator(token.value) && token.value != "(" && token.value != ")") {
            return false;
        }
    }
    //track unmatched open parens
    ArrayStack<string> parenthesisStack;
    //expect open paren or number
    bool expectOperator = false;

    for (const Token& token : tokens) {
        if (!expectOperator) {
            if (isNumber(token.value)) {
                expectOperator = true;
            }
            else if (token.value == "(") {
                parenthesisStack.push("(");
            }
            else {
                return false;
            }

        } else {
            if (isOperator(token.value)) {
                expectOperator = false;
            } else if (token.value == ")") {
                if (parenthesisStack.empty()) return false;
                parenthesisStack.pop();
            } else {
                return false;
            }
        }
    }
    return expectOperator && parenthesisStack.empty();
}

// Conversion

vector<Token> infixToPostfix(const vector<Token>& tokens) {
    vector<Token> output;
    ArrayStack<Token> operatorStack;
    for (const Token& token : tokens) {
        if (isNumber(token.value)) {
            output.push_back(token);
        } else if (isOperator(token.value)) {
            while (!operatorStack.empty() && isOperator(operatorStack.top().value) && precedence(operatorStack.top().value) >= precedence(token.value)) {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(token);
        } else if (token.value == "(") {
            operatorStack.push(token);
        }
        else if (token.value == ")") {
            while (!operatorStack.empty() && operatorStack.top().value != "(") {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }
            if (!operatorStack.empty()) {
                operatorStack.pop();
            }
        }

    }
    while (!operatorStack.empty()) {
        output.push_back(operatorStack.top());
        operatorStack.pop();
    }
    return output;



    // TODO

}

// Evaluation

double evalPostfix(const vector<Token>& tokens) {
    ArrayStack<double> stack;
    for (const Token& token : tokens) {
        if (isNumber(token.value)) {
            stack.push(stod(token.value));
        } else if (isOperator(token.value)) {
            double rightop = stack.top();
            stack.pop();
            double leftop = stack.top();
            stack.pop();
            if (token.value == "+") {
                stack.push(leftop + rightop);
            } else if (token.value == "-") {
                stack.push(leftop - rightop);
            } else if (token.value == "*") {
                stack.push(leftop * rightop);
            } else if (token.value == "/") {
                stack.push(leftop / rightop);
            }
        }
    }
    // TODO
    return stack.top();
}

// Main

int main() {
    string line;
    getline(cin, line);

    vector<Token> tokens = tokenize(line);

    if (isValidPostfix(tokens)) {
        cout << "FORMAT: POSTFIX\n";
        cout << "RESULT: ";
        printOut(evalPostfix(tokens));
        cout << "\n" << endl;
    }
    else if (isValidInfix(tokens)) {
        vector<Token> postfix = infixToPostfix(tokens);
        cout << "FORMAT: INFIX\n";
        cout << "POSTFIX: ";
        for (int i=0; i<(int)postfix.size(); i++) {
            if (i>0) cout << " ";
            cout << postfix[i].value;
        }
        cout << "\n";
        cout << "RESULT: ";
        printOut(evalPostfix(postfix));
        cout << "\n" << endl;
    }
    else {
        cout << "FORMAT: NEITHER\n";
        cout << "ERROR: invalid expression\n";
    }

    return 0;
}
