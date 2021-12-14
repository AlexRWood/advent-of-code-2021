#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<numeric>
#include<algorithm>
int solution(std::string s);

int main() {
    std::cout << solution("test.txt") << std::endl;
    std::cout << solution("input.txt") << std::endl;
}

int solution(std::string s) {
    std::ifstream input{s, std::ifstream::in};
    std::vector<int> horizontalPositions{};
    while(!input.eof()) {
        int current {};
        input >> current;
        horizontalPositions.push_back(current);
        input.ignore(1);
    }
    std::sort(horizontalPositions.begin(), horizontalPositions.end());
    int initialPosition = horizontalPositions.at(horizontalPositions.size()/2);
    int fuelUsed {};
    for(auto x: horizontalPositions) {
        fuelUsed += std::abs(initialPosition - x);
    }
    return fuelUsed;
}