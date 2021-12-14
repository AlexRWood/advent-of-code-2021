#include<string>
#include<vector>
#include<fstream>
#include<iostream>

int solution(std::string s);
void readFile(std::string &s, std::vector<std::vector<int>> &v);
void checkEdges(std::vector<std::vector<int>> &v, int &score);
void checkInner(std::vector<std::vector<int>> &v, int &score);

int main() {
    std::cout << solution("test.txt") << std::endl;
}

int solution(std::string s) {
    std::vector<std::vector<int>> heightMap {};
    readFile(s, heightMap);
    int score {0};
    checkEdges(heightMap, score);
    return score;
}

void readFile(std::string &s, std::vector<std::vector<int>> &v) {
    std::ifstream input{s, std::ifstream::in};
    std::string line {};
    while(!input.eof()) {
        std::getline(input, line);
        std::vector<int> inner;
        for(auto x : line) {
            inner.push_back(x - '0');
        }
        v.push_back(inner);
    }
}

void checkEdges(std::vector<std::vector<int>> &v, int &score) {
    const u_long rightmostColumn {v[0].size()-1};
    const u_long bottomRow {v.size()-1};
    const int topRow {0};
    const int leftmostColumn {0};
   if(v[topRow][leftmostColumn] < v[topRow][leftmostColumn + 1] && v[topRow][leftmostColumn] < v[topRow + 1][leftmostColumn]) {
       score += (v[topRow][leftmostColumn] + 1);
   }
   if(v[topRow][rightmostColumn] < v[topRow][rightmostColumn-1] && v[topRow][rightmostColumn] < v[topRow + 1][rightmostColumn]) {
       score += (v[topRow][rightmostColumn] + 1);
   }
   if(v[bottomRow][leftmostColumn] < v[bottomRow][leftmostColumn + 1] && v[bottomRow][leftmostColumn] < v[bottomRow - 1][leftmostColumn]) {
       score += (v[bottomRow][leftmostColumn] + 1);
   }
   if(v[bottomRow][rightmostColumn] < v[bottomRow][rightmostColumn - 1] && v[bottomRow][rightmostColumn] < v[bottomRow-1][rightmostColumn]) {
       score += (v[bottomRow][rightmostColumn] + 1);
   }
   bool smallerThanLeft {false};
   bool smallerThanRight {false};
   bool smallerThanUp {false};
   bool smallerThanDown {false};

    for(int32_t i {1}; i < rightmostColumn; i++) {
        smallerThanDown = v[topRow][i] < v[topRow+1][i];
        smallerThanLeft = v[topRow][i] < v[topRow][i-1];
        smallerThanRight = v[topRow][i] < v[topRow][i+1];
        if(smallerThanDown && smallerThanLeft && smallerThanRight) {
            score += (v[topRow][i] + 1);
        }
    }

}

void checkInner(std::vector<std::vector<int>> &v, int &score) {
    //TODO
}