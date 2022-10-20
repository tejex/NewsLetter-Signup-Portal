

#include "functions.h"
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

// Group Members: Bamlak Deju, Apurv Patwardhan, Temuulen Nyamdavaa  
using namespace std;

stack<string> operators;
vector<string> output;

map<string, int> priority;

vector<string> split(const string &s, char delimiter) {
  stringstream ss(s);
  string item;
  vector<string> result;
  while (getline(ss, item, delimiter)) {
    result.push_back(item);
  }
  return result;
}

void functions::interaction() {
  cout << "-----------------------------------------------" << endl;
  cout << "Hello, please enter your arithmetic expression: ";
}

bool _isOperator(string s) {
  return s == "+" || s == "-" || s == "*" || s == "/" || s == "^";
}

vector<string> functions::infixToPostfix(vector<string> s) {
  stack<string> operators;
  vector<string> output;
  int size = s.size();

  for (int i = 0; i < size; i++) {

    if (s[i] == "(") {
      operators.push(s[i]);

    }

    else if (s[i] == ")") {
      while (operators.top() != "(") {
        output.push_back(operators.top());
        operators.pop();
      }
      operators.pop();

    } else if (!_isOperator(s[i])) {
      output.push_back(s[i]);
    }

    else if (operators.empty()) {
      operators.push(s[i]);

    } else if (_isOperator(s[i])) {

      if (priority[operators.top()] < priority[s[i]]) {
        operators.push(s[i]);

      } else {
        while (!operators.empty() &&
               priority[operators.top()] >= priority[s[i]]) {
          output.push_back(operators.top());
          operators.pop();
        }
        operators.push(s[i]);
      }
    }
  }

  while (!operators.empty()) {
    output.push_back(operators.top());
    operators.pop();
  }

  for (int i = 0; i < output.size(); i++)
    cout << output[i] << " ";
  cout << endl;

  return output;
}

int power(int x, int y) {
  int result = 1;
  for (int i = 1; i <= y; i++)
    result *= x;
  return result;
}

int evaluate(vector<string> postfix) {
  stack<int> n;
  for (int i = 0; i < postfix.size(); i++) {
    if (!_isOperator(postfix[i])) {
      n.push(stoi(postfix[i]));
      continue;
    }
    int n1 = n.top();
    n.pop();
    int n2 = n.top();
    n.pop();
    if (postfix[i] == "+") {
      n.push(n2 + n1);

    } else if (postfix[i] == "-") {
      n.push(n2 - n1);

    } else if (postfix[i] == "*") {
      n.push(n2 * n1);

    } else if (postfix[i] == "/") {
      n.push(n2 / n1);

    } else if (postfix[i] == "^") {
      n.push(power(n2, n1));
    }
  }

  return n.top();
}

int main() {

  priority["("] = 0;
  priority["+"] = 1;
  priority["-"] = 1;
  priority["*"] = 2;
  priority["/"] = 2;
  priority["^"] = 3;

  functions F = functions();
  F.interaction();
  string a;
  getline(cin, a);
  vector<string> b = split(a, ' ');
  vector<string> s;
  for (int i = 0; i < b.size(); i++) {
    // cout << b[i] << endl;
    s.push_back(b[i]);
  }
  // cout << " "<< endl;
  cout << evaluate(F.infixToPostfix(s)) << endl;
}
