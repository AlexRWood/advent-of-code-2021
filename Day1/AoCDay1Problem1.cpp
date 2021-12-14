#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using std::string;

int main() {
    std::ifstream input;
    input.open("input.txt", std::ifstream::in);
    int previous;
    int next;
    int count = 0;
    input >> previous;
    input >> next;
    if(previous < next) { count++; }
    while(!input.eof()) {
        previous = next;
        input >> next;
        if(previous < next) { count++; }
    }
    std::cout << count << '\n';
    input.close();
}