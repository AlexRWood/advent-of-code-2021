#include<string>
#include<iostream>
#include<fstream>
#include<cmath>

int solution(std::string s);
void readFile(std::string s, int &minX, int &maxX, int &minY, int &maxY);

int main() {
    int result {0};
    result = solution("test.txt");
    assert(result == 112);
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

    for(int j {0}; j < 10000; j++) {
        for(int k {-5000}; k < 10000; k++) {
            int xVelocity {j};
            int yVelocity {k};
            int xPos {0};
            int yPos {0};
            while(xPos <= maxTargetX && yPos >= minTargetY) {
                bool inXTarget = (xPos <= maxTargetX && minTargetX <= xPos);
                bool inYTarget = (yPos <= maxTargetY && minTargetY <= yPos);
                if(inYTarget && inXTarget) {
                    score++;
                    break;
                }
                xPos += xVelocity;
                if(xVelocity > 0) {
                    xVelocity--;
                }
                else if(xVelocity < 0) {
                    xVelocity++;
                }
                yPos += yVelocity;
                yVelocity--;
            }
        }
    }
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