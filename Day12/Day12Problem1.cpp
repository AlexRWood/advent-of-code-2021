#include<string>
#include<vector>
#include<unordered_map>
#include<fstream>
#include<iostream>

struct Cave {
    std::string name {};
    std::vector<Cave> adjacentCaves {};
    bool isSmall {false};
};

void readFile(std::string &s, std::unordered_map<std::string, Cave> &m);
int solution(std::string s);
int navigate(std::unordered_map<std::string, Cave> &listOfCaves, std::unordered_map<std::string, bool> &visitedCaves, Cave &currentLocation);

int main() {
    int testResult {solution("test1.txt")};
    assert(testResult == 10);
    testResult = solution("test2.txt");
    assert(testResult == 19);
    testResult = solution("test3.txt");
    assert(testResult == 226);
    std::cout << solution("input.txt") << std::endl;
}

int solution(std::string s) {
    int score {0};
    
    Cave start {};
    start.name = "start";
    start.isSmall = true;
    std::unordered_map<std::string, Cave> listOfCaves {};
    Cave end {};
    end.name = "end";
    end.isSmall = true;

    listOfCaves.insert({"start", start});
    listOfCaves.insert({"end", end});

    readFile(s, listOfCaves);

    std::unordered_map<std::string, bool> visitedCaves;
    visitedCaves.insert({"start", true});

    score = navigate(listOfCaves, visitedCaves, listOfCaves.at("start"));
    return score;
}

void readFile(std::string &s, std::unordered_map<std::string, Cave> &m) {
    std::ifstream input {s, std::ifstream::in};
    while(!input.eof()) {
        std::string caveOneName {};
        std::string caveTwoName {};
        std::getline(input, caveOneName, '-');
        std::getline(input, caveTwoName);


        if(m.find(caveOneName) == m.end()) {
            Cave caveOne {};
            caveOne.name = caveOneName;
            caveOne.isSmall = ('a' <= caveOneName.at(0) && caveOneName.at(0) <= 'z');
            m.insert({caveOneName, caveOne});
        }
        if(m.find(caveTwoName) == m.end()) {
            Cave caveTwo {};
            caveTwo.name = caveTwoName;
            caveTwo.isSmall = ('a' <= caveTwoName.at(0) && caveTwoName.at(0) <= 'z');
            m.insert({caveTwoName, caveTwo});
        }
        
        m.at(caveOneName).adjacentCaves.push_back(m.at(caveTwoName));
        m.at(caveTwoName).adjacentCaves.push_back(m.at(caveOneName));
    }
}

int navigate(std::unordered_map<std::string, Cave> &listOfCaves, std::unordered_map<std::string, bool> &visitedCaves, Cave &currentLocation) {
    int score {0};
    if(currentLocation.name == "end") {

        return (score + 1);
    }
    for(auto &cave : currentLocation.adjacentCaves) {
        if(cave.isSmall && visitedCaves.find(cave.name) == visitedCaves.end()) {
            std::unordered_map<std::string, bool> newVisitedCaves = visitedCaves;
            newVisitedCaves.insert({cave.name, true});
            score += navigate(listOfCaves, newVisitedCaves, listOfCaves.at(cave.name));
        }
        else if(!cave.isSmall) {
            score += navigate(listOfCaves, visitedCaves, listOfCaves.at(cave.name));
        }
    }
    return score;
}