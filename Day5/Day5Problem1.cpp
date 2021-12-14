#include<string>
#include<fstream>
#include<utility>
#include<vector>
#include<iostream>
#include<unordered_map>
#include<algorithm>

int solution(std::string s);

struct point {
    int x;
    int y;
};

int main() {
    std::cout << solution("test.txt") << std::endl;
    std::cout << solution("input.txt") << std::endl;
}

int solution(std::string s) {
    std::ifstream input {s, std::ifstream::in};
    std::vector<std::pair<point, point>> lines;
    int x1, x2, y1, y2;
    while(!input.eof()) {
        input >> x1;
        input.get();
        input >> y1;
        point p1 {};
        p1.x = x1;
        p1.y = y1;
        input.ignore(4);
        input >> x2;
        input.get();
        input >> y2;
        point p2 {};
        p2.x = x2;
        p2.y = y2;
        std::pair<point, point> line {p1, p2};
        lines.push_back(line);
    }
    int dangerSpots = 0;
    std::unordered_map<int, std::unordered_map<int, int>> dangerZones;
    for(auto x : lines) {
        if(x.first.x == x.second.x) {
            for(int i = std::min(x.first.y, x.second.y); i <= std::max(x.first.y, x.second.y); i++) {
                if(dangerZones.find(x.first.x) == dangerZones.end()) {
                    std::unordered_map<int, int> innerDangerZones {};
                    dangerZones.insert({x.first.x, innerDangerZones});
                    dangerZones.at(x.first.x).insert({i, 1});
                }
                else {
                    if(dangerZones.at(x.first.x).find(i) == dangerZones.at(x.first.x).end()) {
                        dangerZones.at(x.first.x).insert({i, 1});
                    }
                    else if(dangerZones.at(x.first.x).at(i) == 1) {
                        dangerSpots++;
                        dangerZones.at(x.first.x).at(i)++;
                    }

                }
            }
        }
        else if(x.first.y == x.second.y) {
            for(int i = std::min(x.first.x, x.second.x); i <= std::max(x.first.x, x.second.x); i++) {
                if(dangerZones.find(i) == dangerZones.end()) {
                    std::unordered_map<int, int> innerDangerZones {};
                    dangerZones.insert({i, innerDangerZones});
                    dangerZones.at(i).insert({x.first.y, 1});
                }
                else {
                    if(dangerZones.at(i).find(x.first.y) == dangerZones.at(i).end()) {
                        dangerZones.at(i).insert({x.first.y, 1});
                    }
                    else if(dangerZones.at(i).at(x.first.y) == 1){
                        dangerSpots++; 
                        dangerZones.at(i).at(x.first.y)++;
                    }
                }
            }
        }
        else {
            int startingX {};
            int startingY {};
            int difference {}; 
            bool yGoesUp {true};
            if(x.first.x <= x.second.x) {
                startingX = x.first.x;
                startingY = x.first.y;
                difference = x.second.x - x.first.x;
                yGoesUp = (x.first.y < x.second.y) ? true : false;
            }
            else {
                startingX = x.second.x;
                startingY = x.second.y;
                difference = x.first.x - x.second.x;
                yGoesUp = (x.second.y < x.first.y) ? true : false;
            }
            for(int i = 0; i <= difference; i++) {
                int yOffSet {startingY};
                yOffSet = (yGoesUp) ? yOffSet+i : yOffSet-i;
                if(dangerZones.find(startingX+i) == dangerZones.end()) {
                    std::unordered_map<int, int> innerDangerZones {};
                    dangerZones.insert({startingX+i, innerDangerZones});
                    dangerZones.at(startingX+i).insert({yOffSet, 1});
                }
                else {
                    if(dangerZones.at(startingX+i).find(yOffSet) == dangerZones.at(startingX+i).end()) {
                        dangerZones.at(startingX+i).insert({yOffSet, 1});
                    }
                    else if(dangerZones.at(startingX+i).at(yOffSet) == 1){ 
                        dangerSpots++;
                        dangerZones.at(startingX+i).at(yOffSet)++;
                    }
                }

            }
        }
    }
    return dangerSpots;
}