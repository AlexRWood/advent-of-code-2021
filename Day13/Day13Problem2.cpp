#include<set>
#include<string>
#include<vector>
#include<unordered_map>
#include<iostream>
#include<fstream>
#include<unordered_map>

int solution(std::string s);
void readFile(std::string s, std::vector<std::pair<int, int>>  &coordinates,  std::vector<std::pair<char, int>> &folds);
void verticalFold(std::vector<std::pair<int, int>>  &coordinates, int &xSize);
void horizontalFold(std::vector<std::pair<int, int>>  &coordinates, int &ySize);


int main() {
    std::cout << solution("input.txt") << std::endl;
}

int solution(std::string s) {
    int score {0};
    std::vector<std::pair<int, int>>  coordinates {};
    std::vector<std::pair<char, int>> folds {};
    bool nextFoldIsHorizontal {false};
    readFile(s, coordinates, folds);
    int ySize {0};
    int xSize {0};
    for(auto &x : folds) {
        if(xSize == 0 && x.first == 'x') {
            xSize = (x.second * 2) + 1;
        } 
        if(ySize == 0 && x.first == 'y') {
            ySize = (x.second * 2) + 1;
        }
        if(ySize != 0 && xSize != 0) {
            break;
        }
    }
    for(auto &x : folds) {
        if(x.first == 'x') {
            verticalFold(coordinates, xSize);
        }
        else {
            horizontalFold(coordinates, ySize);
        }
    }
    std::vector<std::vector<char>> outerVector {};
    for(int i {0}; i <= xSize; i++) {
        std::vector<char> inner(ySize + 1, '.');
        outerVector.push_back(inner);
    }
    for(auto &x : coordinates) {
        outerVector[x.first][x.second] = '#';
    }
    for(auto &x : outerVector) {
        for(auto &y : x) {
            std::cout << y << ' ';
        }
        std::cout << std::endl;
    }
    score = coordinates.size();
    return score;
}

void readFile(std::string s, std::vector<std::pair<int, int>>  &coordinates,  std::vector<std::pair<char, int>> &folds) {
    std::ifstream input {s, std::ifstream::in};
    while(input.peek() != '\n') {
        std::pair<int, int> point {};
        std::string firstPoint {};
        std::string secondPoint {};
        std::getline(input, firstPoint, ',');
        std::getline(input, secondPoint);
        point.first = std::stoi(firstPoint);
        point.second = std::stoi(secondPoint);
        coordinates.push_back(point);
    }
    while(!input.eof()) {
        std::pair<char, int> fold {};
        std::string line {};
        std::getline(input, line, '=');
        char axis = line.at(line.size()-1);
        std::getline(input, line);
        int number = std::stoi(line);
        fold.first = axis;
        fold.second = number;
        folds.push_back(fold);
    }
}

void verticalFold(std::vector<std::pair<int, int>>  &coordinates, int &xSize) {
    int halfwayPoint = xSize / 2;
    std::vector<std::pair<int, int>> newCoordinates {};
    std::unordered_map<int, std::unordered_map<int, bool>> map {};
    for(auto &x : coordinates) {
        if(x.first < halfwayPoint) {
            if(map.find(x.first) == map.end()) {
                std::unordered_map<int, bool> innerMap {};
                innerMap.insert({x.second, true});
                map.insert({x.first, innerMap});
                newCoordinates.push_back({x.first, x.second});
            }
            else if(map.at(x.first).find(x.second) == map.at(x.first).end()) {
                map.at(x.first).insert({x.second, true});
                newCoordinates.push_back({x.first, x.second});
            }
        }
        else {
            int newXPos = halfwayPoint - std::abs(x.first - halfwayPoint);
            if(map.find(newXPos) == map.end()) {
                std::unordered_map<int, bool> innerMap {};
                innerMap.insert({x.second, true});
                map.insert({newXPos, innerMap});
                newCoordinates.push_back({newXPos, x.second});
            }
            else if(map.at(newXPos).find(x.second) == map.at(newXPos).end()) {
                map.at(newXPos).insert({x.second, true});
                newCoordinates.push_back({newXPos, x.second});
            }
        }
    }
    xSize = halfwayPoint;
    coordinates = newCoordinates;
}

void horizontalFold(std::vector<std::pair<int, int>>  &coordinates, int &ySize) {
    int halfwayPoint = ySize / 2;
    std::vector<std::pair<int, int>> newCoordinates {};
    std::unordered_map<int, std::unordered_map<int, bool>> map {};
    for(auto &x : coordinates) {
        if(x.second < halfwayPoint) {
            if(map.find(x.first) == map.end()) {
                std::unordered_map<int, bool> innerMap {};
                innerMap.insert({x.second, true});
                map.insert({x.first, innerMap});
                newCoordinates.push_back({x.first, x.second});
            }
            else if(map.at(x.first).find(x.second) == map.at(x.first).end()) {
                map.at(x.first).insert({x.second, true});
                newCoordinates.push_back({x.first, x.second});
            }
        }
        else {
            int newYPos = halfwayPoint - std::abs(x.second - halfwayPoint);
            if(map.find(x.first) == map.end()) {
                std::unordered_map<int, bool> innerMap {};
                innerMap.insert({newYPos, true});
                map.insert({x.first, innerMap});
                newCoordinates.push_back({x.first, newYPos});
            }
            else if(map.at(x.first).find(newYPos) == map.at(x.first).end()) {
                map.at(x.first).insert({newYPos, true});
                newCoordinates.push_back({x.first, newYPos});
            }
        }
    }
    ySize = halfwayPoint;
    coordinates = newCoordinates;
}
