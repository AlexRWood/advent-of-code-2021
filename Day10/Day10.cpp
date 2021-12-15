#include<string>
#include<iostream>
#include<vector>
#include<fstream>

int solution(std::string s);
void readFile(std::string &s, std::vector<std::string> &v);
int parseLine(std::string &s);

int main() {
    int testResult = solution("test.txt");
    assert(26397);
    std::cout << solution("input.txt") << std::endl;
}

int solution(std::string s) {
    int score {0};
    std::vector<std::string> lines {};
    readFile(s, lines);
    for(auto &x : lines) {
        score += parseLine(x);
    }
    return score;
}

void readFile(std::string &s, std::vector<std::string> &v) {
    std::ifstream input {s, std::ifstream::in};
    while(!input.eof()) {
        std::string line;
        std::getline(input, line);
        v.push_back(line);
    }
}

int parseLine(std::string &s) {
    std::vector<char> stack {};
    for(auto c : s) {
        if(c == ')' || c == ']' || c == '>' || c == '}') {
            switch (c) {
                case ')': 
                    if(stack[stack.size()-1] == '(') {
                        stack.pop_back();
                    }
                    else {
                        return 3;
                    }
                    break;
                case ']':
                    if(stack[stack.size()-1] == '[') {
                        stack.pop_back();
                    }
                    else {
                        return 57;
                    }
                    break;
                case '}':
                    if(stack[stack.size()-1] == '{') {
                        stack.pop_back();
                    }
                    else {
                        return 1197;
                    }
                    break;
                case '>':
                    if(stack[stack.size()-1] == '<') {
                        stack.pop_back();
                    }
                    else {
                        return 25137;
                    }
                    break;
            }
        }
        else {
            stack.push_back(c);
        }
    }
    return 0;
}