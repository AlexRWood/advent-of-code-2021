#include<string>
#include<iostream>
#include<fstream>
#include<cmath>

int solution(std::string s);
void readFile(std::string s, int &minX, int &maxX, int &minY, int &maxY);

int main() {
    int result {0};
    result = solution("test.txt");
    assert(result == 45);
    result = solution("input.txt");
    std::cout << result << std::endl;
}

int solution(std::string s) {
    int score {0};
    int minTargetX {0};
    int maxTargetX {0};
    int minTargetY {0};
    int maxTargetY {0};
    readFile(s, minTargetX, maxTargetX, minTargetY, maxTargetY);

    int startingXVelocity {0};
    int xPos {0};
    int i {0};
    while(!(minTargetX <= xPos && xPos <= maxTargetX)) {
        xPos += i;
        i++;
    }
    i--;
    int yPos {0};
    for(int j {1}; j < 10000; j++) {
        int maxHeight {(j+static_cast<int>(std::pow(j, 2)))/2};
        int currentHeight {maxHeight};
        int gravity {1};
        while(currentHeight >= minTargetY) {
            if(minTargetY <= currentHeight && currentHeight <= maxTargetY) {
                score = std::max(score, maxHeight);
            }
            currentHeight -= gravity;
            gravity++;
        }
    }
    startingXVelocity = i;
    return score;
}

void readFile(std::string s, int &minX, int &maxX, int &minY, int &maxY) {
    std::ifstream input {s, std::ifstream::in};
    input.ignore(100, '=');
    input >> minX;
    input.ignore(2);
    input >> maxX;
    input.ignore(100, '=');
    input >> minY;
    input.ignore(2);
    input >> maxY;
}