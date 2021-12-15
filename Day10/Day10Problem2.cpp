#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
int64_t solution(std::string s);
void readFile(std::string &s, std::vector<std::string> &v);
int64_t parseLine(std::string &s);

int main() {
    int64_t testResult = solution("test.txt");
    assert(testResult == 288957);
    std::cout << solution("input.txt") << std::endl;
}

int64_t solution(std::string s) {
    std::vector<int64_t> scores {};
    std::vector<std::string> lines {};
    readFile(s, lines);
    for(auto &x : lines) {
        int64_t currentLineScore {0};
        currentLineScore = parseLine(x);
        if(currentLineScore != 0) {
            scores.push_back(currentLineScore);
        }
    }
    std::sort(scores.begin(), scores.end());
    return scores[(scores.size() - 1)/2];
}

void readFile(std::string &s, std::vector<std::string> &v) {
    std::ifstream input {s, std::ifstream::in};
    while(!input.eof()) {
        std::string line;
        std::getline(input, line);
        v.push_back(line);
    }
}

int64_t parseLine(std::string &s) {
    std::vector<char> stack {};
    for(auto c : s) {
        if(c == ')' || c == ']' || c == '>' || c == '}') {
            switch (c) {
                case ')': 
                    if(stack[stack.size()-1] == '(') {
                        stack.pop_back();
                    }
                    else {
                        return 0;
                    }
                    break;
                case ']':
                    if(stack[stack.size()-1] == '[') {
                        stack.pop_back();
                    }
                    else {
                        return 0;
                    }
                    break;
                case '}':
                    if(stack[stack.size()-1] == '{') {
                        stack.pop_back();
                    }
                    else {
                        return 0;
                    }
                    break;
                case '>':
                    if(stack[stack.size()-1] == '<') {
                        stack.pop_back();
                    }
                    else {
                        return 0;
                    }
                    break;
            }
        }
        else {
            stack.push_back(c);
        }
    }
    int64_t score {0};
    while(stack.size() != 0) {
        char current {stack[stack.size() - 1]};
        stack.pop_back();
        switch (current) {
            case '[':
                score *= 5;
                score += 2;
                break;
            case '(':
                score *= 5;
                score += 1;
                break;
            case '{':
                score *= 5;
                score += 3;
                break;
            case '<':
                score *= 5;
                score += 4;
        }
    }
    return score;
}