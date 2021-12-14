#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
struct readoutEntry {
    std::vector<std::string> numbers {};
    std::vector<std::string> outputValues {};
    std::unordered_map<std::string, int> detangler;
};

int solution(std::string s);
void readInputFile(std::string s, std::vector<readoutEntry>& v);
void checkForSimpleDetangling(readoutEntry& r);

int main() {
    std::cout << solution("test.txt") << std::endl;
    std::cout << solution("input.txt") << std::endl;
}

int solution(std::string s) {
    std::vector<readoutEntry> entryList {};
    readInputFile(s, entryList);
    int ans {0};
    for(auto& candidate : entryList) {
        for(auto& currentString : candidate.outputValues) {
            if(candidate.detangler.find(currentString) != candidate.detangler.end()) {
                ans++;
            }
        }
    }
    return ans;
}

void readInputFile(std::string s, std::vector<readoutEntry>& v) {
    std::ifstream input {s, std::ifstream::in};
    while(!input.eof()) {
        readoutEntry entry;
        for(int i {0}; i < 10; i++) {
            std::string readInput;
            input >> readInput;
            std::sort(readInput.begin(), readInput.end());
            entry.numbers.push_back(readInput);
            checkForSimpleDetangling(entry);
        }
        input.ignore(3);
        for(int i {0}; i < 4; i++) {
            std::string readInput;
            input >> readInput;
            std::sort(readInput.begin(), readInput.end());
            entry.outputValues.push_back(readInput);
        }
        v.push_back(entry);
    }
    input.close();
}

void checkForSimpleDetangling(readoutEntry& r) {
    int position = r.numbers.size()-1;
    switch (r.numbers.at(position).size()) {
        case 2:
            r.detangler[r.numbers.at(position)] = 1;
            break;
        case 4:
            r.detangler[r.numbers.at(position)] = 4;
            break;
        case 3:
            r.detangler[r.numbers.at(position)] = 7;
            break;
        case 7:
            r.detangler[r.numbers.at(position)] = 8;
            break;
        default: 
            break;
    }
}