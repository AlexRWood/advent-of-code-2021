#include<iostream>
#include<fstream>
#include<vector>
using std::string;

void updateCounts(string s, std::vector<int> &g, std::vector<int> &e);

int main() {
    std::ifstream test;
    std::ifstream input;
    test.open("test.txt", std::ifstream::in);
    input.open("input.txt", std::ifstream::in);
    string testInput;
    string realInput;
    test >> testInput;
    input >> realInput;
    std::vector<int> gammaCount(testInput.length(), 0);
    std::vector<int> epsilonCount(testInput.length(), 0);
    std::vector<int> realGammaCount(realInput.length(), 0);
    std::vector<int> realEpsilonCount(realInput.length(), 0);
    updateCounts(realInput, realGammaCount, realEpsilonCount);
    updateCounts(testInput, gammaCount, epsilonCount);
    while(!test.eof()) {
        test >> testInput;
        updateCounts(testInput, gammaCount, epsilonCount);
    }
    while(!input.eof()) {
        input >> realInput;
        updateCounts(realInput, realGammaCount, realEpsilonCount);
    }
    int exponentiator = 1;
    int epsilon = 0;
    int gamma = 0;
    for(int i = testInput.length()-1; i >= 0; i--) {
        if(gammaCount.at(i) > epsilonCount.at(i)) { gamma += exponentiator; }
        else { epsilon += exponentiator; }
        exponentiator *= 2;
    }
    exponentiator = 1;
    int realEpsilon = 0;
    int realGamma = 0;
    for(int i = realInput.length()-1; i >= 0; i--) {
        if(realGammaCount.at(i) > realEpsilonCount.at(i)) { realGamma += exponentiator; }
        else { realEpsilon += exponentiator; }
        exponentiator *= 2;
    }
    test.close();
    input.close();
    std::cout << (epsilon*gamma) << '\n';
    std::cout << (realEpsilon*realGamma) << '\n';
}

void updateCounts(string s, std::vector<int> &g, std::vector<int> &e) {
    for(int i = 0; i < s.length(); i++) {
        if(s.at(i) == '1') { g.at(i)++; }
        else { e.at(i)++; }
    }
}
