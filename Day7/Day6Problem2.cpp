#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<numeric>
#include<algorithm>

int solution(std::string s);
int checkRightCandidates(std::vector<int>& v, int position, int score);
int checkLeftCandidates(std::vector<int>& v, int position, int score);

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
    double average {};
    average = std::accumulate(horizontalPositions.begin(), horizontalPositions.end(), 0.0)/horizontalPositions.size();
    int initialPosition {static_cast<int>(std::round(average))};
    int fuelUsed {};
    for(auto x: horizontalPositions) {
        for(int i = 1; i <= std::abs(initialPosition-x); i++) {
            fuelUsed += i;
        }
    }
    return std::min(checkRightCandidates(horizontalPositions, initialPosition, fuelUsed), checkLeftCandidates(horizontalPositions, initialPosition, fuelUsed));
}

int checkRightCandidates(std::vector<int>& v, int position, int score) {
    int potential {};
    for(auto x : v) {
        for(int i = 1; i <= std::abs(position+1 - x); i++) {
            potential += i;
        }
    }
    while(potential < score) {
        position++;
        score = potential;
        potential = 0;
        for(auto x : v) {
            for(int i = 1; i <= std::abs(position+1 - x); i++) {
                potential += i;
            }
        }
    }
    return std::min(potential, score);
}

int checkLeftCandidates(std::vector<int>& v, int position, int score) {
    int potential {};
    for(auto x : v) {
        for(int i = 1; i <= std::abs(position-1 - x); i++) {
            potential += i;
        }
    }
    while(potential < score) {
        position--;
        score = potential;
        potential = 0;
        for(auto x : v) {
            for(int i = 1; i <= std::abs(position-1 - x); i++) {
                potential += i;
            }
        }
    }
    return std::min(potential, score);
}