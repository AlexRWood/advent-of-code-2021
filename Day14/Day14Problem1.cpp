#include<string>
#include<fstream>
#include<unordered_map>
#include<vector>
#include<iostream>

int64_t solution(std::string s);
void readFile(std::string s, std::string &starter, std::unordered_map<std::string, char> &converter, std::vector<std::string> &pairs);

void step(std::vector<std::string> &pairs,
    std::unordered_map<std::string, char> &converter, 
    std::unordered_map<std::string, int64_t> &pairCounts, 
    std::unordered_map<char, int64_t> &charCount
);

int main() {
    int64_t testResult {0};
    testResult = solution("test.txt");
    assert(testResult == 1588);
    int64_t result {0};
    result = solution("input.txt");
    std::cout << result << std::endl;
}

int64_t solution(std::string s) {
    int64_t score {0};
    std::string starter {""};
    std::unordered_map<std::string, int64_t> pairCounts {};
    std::vector<std::string> pairs {};
    std::unordered_map<std::string, char> converter {};
    std::unordered_map<char, int64_t> charCount {};
    readFile(s, starter, converter, pairs);
    char previous {starter.at(0)};
    charCount.insert({previous, 1});
    for(int64_t i {1}; i < starter.size(); i++) {
        char current {starter.at(i)};
        if(charCount.find(current) == charCount.end()) {
            charCount.insert({current, 1});
        }
        else {
            charCount.at(current)++;
        }
        std::string group {""};
        group += previous;
        group += current;
        if(pairCounts.find(group) == pairCounts.end()) {
            pairCounts.insert({group, 1});
        }
        else {
            pairCounts.at(group)++;
        }
        previous = current;
    }
    for(int64_t i {1}; i <= 10; i++) {
        step(pairs, converter, pairCounts, charCount);
    }
    int64_t min {INT64_MAX};
    int64_t max {INT64_MIN};
    for(auto &x : pairs) {
        for(auto &y : x) {
            min = std::min(min, charCount.at(y));
            max = std::max(max, charCount.at(y));
        }
    }
    score = max - min;
    return score;
}

void readFile(std::string s, std::string &starter, std::unordered_map<std::string, char> &converter, std::vector<std::string> &pairs) {
    std::ifstream input {s, std::ifstream::in};
    input >> starter;

    while(!input.eof()) {
        std::string pairRule {""};
        input >> pairRule;
        pairs.push_back(pairRule);
        input.ignore(4);
        char inserted {};
        input >> inserted;
        converter.insert({pairRule, inserted});
    }
    pairs.pop_back();
}

void step(std::vector<std::string> &pairs, 
    std::unordered_map<std::string, char> &converter, 
    std::unordered_map<std::string, int64_t> &pairCounts, 
    std::unordered_map<char, int64_t> &charCount
) {
    std::vector<std::pair<std::string, int64_t>> newCount {};
    for(auto &x : pairs) {
        if(pairCounts.find(x) != pairCounts.end()) {
            int64_t num {pairCounts.at(x)};
            char c {converter.at(x)};
            if(charCount.find(c) == charCount.end()) {
                charCount.insert({c, num});
            }
            else {
                charCount.at(c) += num;
            }


            std::string newOne {""};
            newOne += x.at(0);
            newOne += c;
            std::string newTwo {""};
            newTwo += c;
            newTwo += x.at(1);

            newCount.push_back({newOne, num});
            newCount.push_back({newTwo, num});

            pairCounts.at(x) = 0;
        }
    }
    for(auto &x : newCount) {
        if(pairCounts.find(x.first) == pairCounts.end()) {
            pairCounts.insert({x.first, x.second});
        }
        else {
            pairCounts.at(x.first) += x.second;
        }
    }
}