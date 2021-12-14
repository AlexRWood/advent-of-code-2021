#include<iostream>
#include<fstream>
#include<vector>
#include<string>

int findOxygenRating(std::vector<std::string> &candidates);
int findCO2Rating(std::vector<std::string> &candidates);

int findCO2Rating();

int solution(std::string fileName);

int main() {
    std::cout << solution("test.txt") << '\n';
    std::cout << solution("input.txt") << '\n';
}


int solution(std::string fileName) {
    std::ifstream input;
    input.open(fileName, std::ifstream::in);
    std::string s;
    input >> s;
    int length = s.length();
    std::vector<std::string> zeroCandidates;
    std::vector<std::string> oneCandidates;
    if(s.at(0) == '1') { oneCandidates.push_back(s); }
    else { zeroCandidates.push_back(s); }
    while(!input.eof()) {
        input >> s;
        if(s.at(0) == '1') { oneCandidates.push_back(s); }
        else { zeroCandidates.push_back(s); }
    }
    std::vector<std::string> oxygenCandidates;
    std::vector<std::string> CO2Candidates;
    if(zeroCandidates.size() <= oneCandidates.size()) {
        oxygenCandidates = oneCandidates;
        CO2Candidates = zeroCandidates;
    }
    else if(zeroCandidates.size() > oneCandidates.size()) {
        oxygenCandidates = zeroCandidates;
        CO2Candidates = oneCandidates;
    }
    return (findOxygenRating(oxygenCandidates)*findCO2Rating(CO2Candidates));
}

int findOxygenRating(std::vector<std::string> &candidates) {
    int position = 1;
    int oxygenRating = 0;
    while(candidates.size() > 1) {
        std::vector<std::string> oneCandidates;
        std::vector<std::string> zeroCandidates;
        for(auto x : candidates) {
            if (x.at(position) == '1') { oneCandidates.push_back(x); }
            else { zeroCandidates.push_back(x); }
        }
        candidates = (oneCandidates.size() >= zeroCandidates.size()) ? oneCandidates : zeroCandidates;
        position++;
    }
    int exponentiator = 1;
    for(int i = candidates.at(0).size()-1; i >= 0; i--) {
        if(candidates.at(0).at(i) == '1') { oxygenRating += exponentiator; }
        exponentiator *= 2;
    }
    return oxygenRating;
}

int findCO2Rating(std::vector<std::string> &candidates) {
    int position = 1;
    int CO2Rating = 0;
    while(candidates.size() > 1) {
        std::vector<std::string> oneCandidates;
        std::vector<std::string> zeroCandidates;
        for(auto x : candidates) {
            if (x.at(position) == '1') { oneCandidates.push_back(x); }
            else { zeroCandidates.push_back(x); }
        }
        candidates = (oneCandidates.size() >= zeroCandidates.size()) ? zeroCandidates : oneCandidates;
        position++;
    }
    int exponentiator = 1;
    for(int i = candidates.at(0).size()-1; i >= 0; i--) {
        if(candidates.at(0).at(i) == '1') { CO2Rating += exponentiator; }
        exponentiator *= 2;
    }
    return CO2Rating;
}
