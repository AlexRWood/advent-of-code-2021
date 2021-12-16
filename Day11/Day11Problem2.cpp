#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<utility>
int solution(std::string s);
void readFile(std::string &s, std::vector<std::vector<int>> &v);
int step(std::vector<std::vector<int>> &v);


int main() {
    int testScore = solution("test.txt");
    assert(testScore == 195);
    std::cout << solution("input.txt") << std::endl;
}

int solution(std::string s) {
    int flashesAtCurrentStep {0};
    int numOfOctopi {0};
    std::vector<std::vector<int>> map {};
    readFile(s, map);
    for(int i {1}; i < map.size()-1; i++) {
        for(int j {1}; j < map[i].size()-1; j++) {
            numOfOctopi++;
        }
    }
    int score {0};
    while(flashesAtCurrentStep != numOfOctopi) {
        flashesAtCurrentStep = step(map);
        score++;
    }
    return score;
}

void readFile(std::string &s, std::vector<std::vector<int>> &v) {
    std::ifstream input {s, std::ifstream::in};
    //Manually do one line to have padding in map
    std::string line;
    std::getline(input, line);
    int sizeWithPadder = line.size() + 2;
    std::vector<int> rowPadding(sizeWithPadder, INT32_MIN);
    v.push_back(rowPadding);
    std::vector<int> row {};
    row.push_back(INT32_MIN);
    for(char c : line) {
        row.push_back(c - '0'); //Convert char to int
    }
    row.push_back(INT32_MIN);
    v.push_back(row);

    while(!input.eof()) {
        std::getline(input, line);
        std::vector<int> row {};
        row.push_back(INT32_MIN);
        for(auto c : line) {
            row.push_back(c - '0'); //Convert char to int
        }
        row.push_back(INT32_MIN);
        v.push_back(row);
    }
    std::vector<int> bottomPadder(sizeWithPadder, INT32_MIN);
    v.push_back(bottomPadder);
}

int step(std::vector<std::vector<int>> &v) {
    int score {0};
    std::vector<std::pair<int, int>> flashCandidates {};
    std::vector<std::pair<int, int>> restToZero {};
    //Increase all coordinates
    for(int i {1}; i < v.size()-1; i++) {
        for(int j {1}; j <v[i].size()-1; j++) {
            v[i][j]++;
            if(v[i][j] == 10) {
                std::pair<int, int> coordinate {i, j};
                flashCandidates.push_back(coordinate);
            }
        }
    }
    //Flash octopi
    while(flashCandidates.size() != 0) {
        std::pair<int, int> coordinate {flashCandidates[flashCandidates.size()-1]};
        flashCandidates.pop_back();

        v[coordinate.first - 1][coordinate.second - 1]++;
        if(v[coordinate.first - 1][coordinate.second - 1] == 10) {
            flashCandidates.push_back({coordinate.first-1, coordinate.second-1});
        }

        v[coordinate.first - 1][coordinate.second]++;
        if(v[coordinate.first - 1][coordinate.second] == 10) {
            flashCandidates.push_back({coordinate.first-1, coordinate.second});
        }

        v[coordinate.first - 1][coordinate.second + 1]++;
        if(v[coordinate.first - 1][coordinate.second + 1] == 10) {
            flashCandidates.push_back({coordinate.first-1, coordinate.second+1});
        }


        v[coordinate.first + 1][coordinate.second - 1]++;
        if(v[coordinate.first + 1][coordinate.second - 1] == 10) {
            flashCandidates.push_back({coordinate.first+1, coordinate.second-1});
        }

        v[coordinate.first + 1][coordinate.second]++;
        if(v[coordinate.first + 1][coordinate.second] == 10) {
            flashCandidates.push_back({coordinate.first+1, coordinate.second});
        }

        v[coordinate.first + 1][coordinate.second + 1]++;
        if(v[coordinate.first + 1][coordinate.second + 1] == 10) {
            flashCandidates.push_back({coordinate.first+1, coordinate.second+1});
        }

        v[coordinate.first][coordinate.second - 1]++;
        if(v[coordinate.first][coordinate.second - 1] == 10) {
            flashCandidates.push_back({coordinate.first, coordinate.second-1});
        }
        v[coordinate.first][coordinate.second + 1]++;
        if(v[coordinate.first][coordinate.second + 1] == 10) {
            flashCandidates.push_back({coordinate.first, coordinate.second+1});
        }
        restToZero.push_back(coordinate);
    }
    //Reset all octopi that flashed to zero
    for(auto &x : restToZero) {
        v[x.first][x.second] = 0;
        score++;
    }
    return score;
}