/*
ASSIGNMENT - 01
NAME - TAPAS RANJAN NAYAK
ROLL NO - 20CS01064
*/
#include <bits/stdc++.h>
using namespace std;

// function for priority check
int prec(char c) {
    if (c == '+' || c == '-') {
        return 1;
    }
    if (c == '*') {
        return 2;
    }
    return 3;
}

int main() {
    // Declaration of input string
    string input;

    // Taking the input
    cout << "Enter the infix expression:\n";
    cin >> input;

    // prgrame for infix to postfix
    vector<string> postfix;
    stack<char> st;
    int i = 0;

    while (i < input.length()) {
        // checking for different condition
        if (input[i] == '(') {
            st.push('(');
        } else if (input[i] == ')') {
            char upper = st.top();
            while (upper != '(') {
                postfix.push_back(string(1, upper));
                st.pop();
                upper = st.top();
            }
            st.pop();
        } else if ((input[i] == '+') || (input[i] == '-') ||
                   (input[i] == '*') || (input[i] == '/')) {
            while (!st.empty() && (st.top() != '(') &&
                   (prec(input[i]) <= prec(st.top()))) {
                postfix.push_back(string(1, st.top()));
                st.pop();
            }
            st.push(input[i]);
        } else {
            // Adding the number string to postfix
            string no;
            for (i; i < input.length(); i++) {
                if (input[i] <= '9' && input[i] >= '0') {
                    no += input[i];
                } else {
                    i--;
                    break;
                }
            }
            postfix.push_back(no);
        }
        i++;
    }

    // checking for any leftout operator
    while (!st.empty()) {
        postfix.push_back(string(1, st.top()));
        st.pop();
    }

    // Evaluating answer from postfix
    stack<string> s;
    for (int i = 0; i < postfix.size(); i++) {
        double first, sec;

        // Checking for differnt operator
        if ((postfix[i] == string(1, '+'))) {
            sec = stod(s.top());
            s.pop();
            first = stod(s.top());
            s.pop();
            s.push(to_string(first + sec));
        } else if ((postfix[i] == string(1, '-'))) {
            sec = stod(s.top());
            s.pop();
            first = stod(s.top());
            s.pop();
            s.push(to_string(first - sec));
        } else if ((postfix[i] == string(1, '*'))) {
            sec = stod(s.top());
            s.pop();
            first = stod(s.top());
            s.pop();
            s.push(to_string(first * sec));
        } else if ((postfix[i] == string(1, '/'))) {
            sec = stod(s.top());
            s.pop();
            first = stod(s.top());
            s.pop();
            s.push(to_string((double)first / (double)sec));
        } else {
            s.push(postfix[i]);
        }
    }

    // printing the answer
    double ans = stod(s.top());
    cout << "ANS: ";
    cout << fixed;
    cout << setprecision(4);
    cout << ans << "\n";
    s.pop();

    return 0;
}