#include <iostream>
#include <string>
#include <stack>

class solution {
  public:
    int calculate(const std::string & s) {
        size_t begin = 0, end;
        std::stack<int> st;
        while (begin < s.size() && begin != std::string::npos) {
            if (isdigit(s[begin])) {
                end = s.find_first_not_of("0123456789", begin);
                st.push(stoi(s.substr(begin, end-begin)));
                begin = end;
            }
            else if (s[begin] == '(') {
                end = findClosingParen(s, begin);
                st.push(calculate(s.substr(begin+1, end-begin-1)));
                begin = end+1;
            }
            else if (s[begin] == '+') {
                int op1 = st.top();
                st.pop();
                int op2 = calculate(s.substr(begin+1));
                st.push(op1+op2);
                begin = std::string::npos;
            }
            else if (s[begin] == '-') {
                int op1 = st.top(), op2;
                st.pop();
                size_t next = s.find_first_not_of("- ", begin);
                if (s[next] == '(') {
                    end = findClosingParen(s,next);
                    op2 = calculate(s.substr(next+1, end-next-1));
                    begin = end+1;
                }
                else {
                    end = s.find_first_not_of("0123456789", next);
                    op2 = stoi(s.substr(next, end-next));
                    begin = end;
                }
                st.push(op1-op2);
            }
            else if (s[begin] == ' ')
                begin = s.find_first_not_of(' ', begin+1);
        }
        return st.top();
    }

  private:
    size_t findClosingParen(const std::string &s, size_t begin) {
        size_t end = s.find_first_of(')', begin);
        while (end != std::string::npos && !isValidParen(s, begin, end))
            end = s.find_first_of(')', end+1);
        return end;
    }

    bool isValidParen(const std::string &s, size_t begin, size_t end) {
        std::stack<char> st;
        size_t idx = begin;
        while (idx <= end) {
            if (st.empty()) {
                if (s[idx] == '(')
                    st.push(s[idx]);
                else if (s[idx] == ')')
                    return false;
            }
            else {
                if (s[idx] == '(')
                    st.push(s[idx]);
                else if (s[idx] == ')') {
                    st.pop();
                }                    
            }
            idx++;
        }
        return st.empty();
    }
};

int main() {
    // std::string expr{"1 + 1"};
    // std::string expr{"2-1 + 2"};
    std::string expr{"(1+(4+5+2)-3)-(6-8)"};

    solution soln;
    int result = soln.calculate(expr);
    std::cout << expr << " = " << result << std::endl;
}
