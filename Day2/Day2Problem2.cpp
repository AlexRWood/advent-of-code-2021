#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
using std::string;

void updatePosition(string s, int magnitude, int& y, int& z, int& aim);

int main() {
    int yPosition = 0;
    int zPosition = 0;
    int aim = 0;
    std::ifstream input("input.txt", std::ifstream::in);
    string direction;
    int magnitude;
    input >> direction;
    input >> magnitude;
    updatePosition(direction, magnitude, yPosition, zPosition, aim);
    while(!input.eof()) {
        input >> direction;
        input >> magnitude;
        updatePosition(direction, magnitude, yPosition, zPosition, aim);
    }
    input.close();
    std::cout << yPosition*zPosition << '\n';
}

void updatePosition(string s, int magnitude, int& y, int& z, int& aim) {
   if(s == "down") {
       aim += magnitude;
   }
   else {
       if(s == "up") { aim -= magnitude; }
       else { 
           y += magnitude;
           z += (aim*magnitude);
        }
   }
}
