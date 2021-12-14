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
    std::cout << solution("input.txt") << std::endl;
}

int solution(std::string s) {
    std::vector<std::vector<int>> heightMap {};
    readFile(s, heightMap);
    int score {0};
    checkEdges(heightMap, score);
    checkInner(heightMap, score);
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

    for(int i {1}; i < rightmostColumn; i++) {
        const int height = v[topRow][i];
        smallerThanDown = height < v[topRow+1][i];
        smallerThanLeft = height < v[topRow][i-1];
        smallerThanRight = height < v[topRow][i+1];
        if(smallerThanDown && smallerThanLeft && smallerThanRight) {
            score += (height + 1);
        }
    }
    for(int i {1}; i < bottomRow; i++) {
        const int height = v[i][leftmostColumn];
        smallerThanDown = height < v[i + 1][leftmostColumn];
        smallerThanRight = height < v[i][leftmostColumn + 1];
        smallerThanUp = height < v[i - 1][leftmostColumn];
        if(smallerThanDown && smallerThanRight && smallerThanUp) {
            score += (height + 1);
        }
    }
    for(int i {1}; i < rightmostColumn; i++) {
        const int height = v[bottomRow][i];
        smallerThanLeft = height < v[bottomRow][i - 1];
        smallerThanRight = height < v[bottomRow][i + 1];
        smallerThanUp = height < v[bottomRow - 1][i];
        if(smallerThanLeft && smallerThanRight && smallerThanUp) {
            score += (height + 1);
        }
    }
    for(int i {1}; i < bottomRow; i++) {
        const int height = v[i][rightmostColumn];
        smallerThanLeft = height < v[i][rightmostColumn - 1];
        smallerThanDown = height < v[i + 1][rightmostColumn];
        smallerThanUp = height < v[i - 1][rightmostColumn];
        if(smallerThanLeft && smallerThanDown && smallerThanUp) {
            score += (height + 1);
        }
    }



}

void checkInner(std::vector<std::vector<int>> &v, int &score) {
    bool smallerThanRight {false};
    bool smallerThanLeft {false};
    bool smallerThanUp {false};
    bool smallerThanDown {false};
    for(int i {1}; i < v.size() - 1; i++) {
        for(int j {1}; j < v[i].size() - 1; j++) {
            const int height {v[i][j]};
            smallerThanDown = height < v[i + 1][j];
            smallerThanUp = height < v[i - 1][j];
            smallerThanLeft = height < v[i][j - 1];
            smallerThanRight = height < v[i][j + 1];
            if(smallerThanDown && smallerThanLeft && smallerThanRight && smallerThanUp) {
                score += (height + 1);
            }
        }
    }
}