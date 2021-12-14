#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
using std::string;

void updatePosition(string s, int magnitude, int& y, int& z);

int main() {
    int yPosition = 0;
    int zPosition = 0;
    std::ifstream input("input.txt", std::ifstream::in);
    string direction;
    int magnitude;
    input >> direction;
    input >> magnitude;
    updatePosition(direction, magnitude, yPosition, zPosition);
    while(!input.eof()) {
        input >> direction;
        input >> magnitude;
        updatePosition(direction, magnitude, yPosition, zPosition);
    }
    input.close();
    std::cout << yPosition*zPosition << '\n';
}

void updatePosition(string s, int magnitude, int& y, int& z) {
   if(s == "down") {
       z += magnitude;
   }
   else {
       if(s == "up") { z -= magnitude; }
       else { y += magnitude; }
   }
}
