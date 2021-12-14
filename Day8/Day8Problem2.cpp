#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
struct readoutEntry {
    std::vector<std::string> numbers {};
    std::vector<std::string> outputValues {};
    std::vector<std::string> detangledOutputValues {};
    int detangledOutput {0};
    std::vector<std::string> fiveLong {};
    std::vector<std::string> sixLong {};
    int onePosition {0};
    int sevenPosition {0};
    std::unordered_map<char, char> detangler;
};

int solution(std::string s);
void readInputFile(std::string s, std::vector<readoutEntry>& v);
void categorizeEntires(readoutEntry& r);
void findBEFsegments(std::vector<readoutEntry>& v);
void findAsegment(std::vector<readoutEntry>& v);
void findCsegment(std::vector<readoutEntry>& v);
void findGsegment(std::vector<readoutEntry>& v);
void findDsegment(std::vector<readoutEntry>& v);
void detangle(std::vector<readoutEntry>& v);
void detangledToValue(std::vector<readoutEntry>& v);

int main() {
    std::cout << solution("test.txt") << std::endl;
}

int solution(std::string s) {
    std::vector<readoutEntry> entryList {};
    readInputFile(s, entryList);
    detangle(entryList);
    int ans {0};
    for(auto& entry : entryList) {
        for(auto& s : entry.detangledOutputValues) {
            std::cout << s << '\n';
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
            categorizeEntires(entry);
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

void categorizeEntires(readoutEntry& r) {
    int position = r.numbers.size()-1;
    switch (r.numbers.at(position).size()) {
        case 2:
            r.onePosition = position;
            break;
        case 3:
            r.sevenPosition = position;
            break;
        case 5:
            r.fiveLong.push_back(r.numbers.at(position));
            break;
        case 6:
            r.sixLong.push_back(r.numbers.at(position));
            break;
        default: 
            break;
    }
}

void findBEFsegments(std::vector<readoutEntry>& v) {
    std::unordered_map<char, int> count {};
    for(auto& entry : v) {
        for(auto& currentString : entry.numbers) {
            for(int i {0}; i < currentString.size(); i++) {
                if(count.find(currentString.at(i)) == count.end()) {
                    count.insert({currentString.at(i), 1});
                }
                else {
                    count.at(currentString.at(i))++;
                }
            }
        }
        std::string candidates = "abcdefg";
        for(int i {0}; i < candidates.size(); i++) {
            int numOfNumsLightIsOn {count.at(candidates.at(i))};
            switch (numOfNumsLightIsOn) {
                case 6:
                    entry.detangler.insert({candidates.at(i), 'b'});
                    break;
                case 4:
                    entry.detangler.insert({candidates.at(i), 'e'});
                    break;
                case 9:
                    entry.detangler.insert({candidates.at(i), 'f'});
                    break;
                default:
                    break;
            }
        }
    }
}

void findAsegment(std::vector<readoutEntry>& v) {
    for(auto& entry : v) {
        std::string sevenString = entry.numbers.at(entry.sevenPosition);
        std::string oneString = entry.numbers.at(entry.onePosition);
        std::unordered_map<char, bool> m {};
        for(int i {0}; i < oneString.size(); i++) {
            m.insert({oneString.at(i), true});
        }
        for(auto x : sevenString) {
            if(m.find(x) == m.end()) {
                entry.detangler.insert({x, 'f'});
                break;
            }
        }
    }
}

void findCsegment(std::vector<readoutEntry>& v) {
    for(auto& entry : v) {
        std::string oneString = entry.numbers.at(entry.onePosition);
        for(auto x : oneString) {
            if(entry.detangler.find(x) == entry.detangler.end()) {
                entry.detangler.insert({x, 'c'});
            }
        }
    }
}

void findGsegment(std::vector<readoutEntry>& v) {
    for(auto& entry : v) {
        for(auto& s : entry.sixLong) {
            int count {0};
            char potential {'a'};
            for(auto c : s) {
                if(entry.detangler.find(c) != entry.detangler.end()) {
                    count++;
                    potential = c;
                }
            }
            if(count == 1) {
                entry.detangler.insert({potential, 'g'});
            }
        }
    }
}

void findDsegment(std::vector<readoutEntry>& v) {
    for(auto& entry : v) {
        std::string s {"abcdefg"};
        for(auto c : s) {
            if(entry.detangler.find(c) == entry.detangler.end()) {
                entry.detangler.insert({c, 'd'});
            }
        }
    }
}

void detangle(std::vector<readoutEntry>& v) {
    findBEFsegments(v);
    findAsegment(v);
    findCsegment(v);
    findGsegment(v);
    findDsegment(v);
    for(auto& entry : v) {
        for(auto s : entry.outputValues) {
            std::string detangled {};
            for(auto c : s) {
                detangled.push_back(entry.detangler.at(c));
            }
            std::sort(detangled.begin(), detangled.end());
            entry.detangledOutputValues.push_back(detangled);
        }
    }
}

int wiresToNumber(std::string s) {
    switch(s.size()) {
        case 2:
            return 1;
        case 3:
            return 7;
        case 4: 
            return 4;
        case 7:
            return 8;
        case 6:
            if(s ==  "abcefg") {
                return 0;
            }
            else if(s == "abdefg") {
                return 6;
            }
            else {
                return 9;
            }
        case 5:
            if(s == "acdeg") {
                return 2;
            }
            else if(s == "acdfg") {
                return 3;
            }
            else {
                return 5;
            }
    }
    return 0;
}

void detangledToValue(std::vector<readoutEntry>& v) {
    for(auto& entry : v) {
        int magnitude {1000};
        for(auto s : entry.detangledOutputValues) {
            entry.detangledOutput += (magnitude*wiresToNumber(s));
            magnitude /= 10;
        }
    }
}