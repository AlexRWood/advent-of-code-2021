#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using std::string;

int main() {
    std::ifstream input;
    input.open("input.txt", std::ifstream::in);
    int window1;
    int window2;
    int window3;
    int window4;
    int previous;
    int next;
    int count {0};
    input >> window1;
    input >> window2;
    input >> window3;
    input >> window4;
    previous = window1 + window2 + window3;
    next = window2 + window3 + window4;
    if(previous < next) { count++; }
    while(!input.eof()) {
        previous = previous - window1 + window4;
        window1 = window2;
        window2 = window3;
        window3 = window4;
        input >> window4;
        next = next - window1 + window4;
        if(previous < next) { count++; }
    }
    std::cout << count << '\n';
    input.close();
}