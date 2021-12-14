#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<numeric>

int64_t solution(std::string s);

int main() {
    std::cout << solution("test.txt") << std::endl;
    std::cout << solution("input.txt") << std::endl;
}

int64_t solution(std::string s) {
    std::ifstream input {s, std::ifstream::in};
    std::vector<int64_t> fishTimers(9, 0);
    while(!input.eof()) {
        int64_t current {};
        input >> current;
        input.ignore(1);
        fishTimers.at(current)++;
    }
    int64_t spawners {fishTimers.at(0)};
    for(int i {1}; i <= 256; i++) {
        for(int j {0}; j < 8; j++) {
            fishTimers.at(j) = fishTimers.at(j + 1);
        }
        fishTimers.at(8) = 0;
        fishTimers.at(6) += spawners;
        fishTimers.at(8) += spawners;
        spawners = fishTimers.at(0);
    }
    int64_t sum{};
    for(int i {0}; i < fishTimers.size(); i++) { sum += fishTimers.at(i); }
    return sum; // TODO: return solution
}