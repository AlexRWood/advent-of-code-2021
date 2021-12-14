#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>

int solution(std::string s);

struct bingoBoard {
    int sumOfNums = 0;
    std::unordered_map<int, struct bingoSquare> board {};
    std::vector<int> remainingInRows{5, 5, 5, 5, 5};
    std::vector<int> remainingInColumns{5, 5, 5, 5, 5};
};

struct bingoSquare {
    int num;
    int row;
    int column;
};

int playBingo(std::vector<int> &numsCalled, std::vector<bingoBoard> &boards);

int main() {
    std::cout << solution("test.txt") << '\n';
    std::cout << solution("input.txt") << '\n';
}

int solution(std::string s) {
    std::ifstream input{s, std::ifstream::in};
    int num {};
    input >> num;

    std::vector<int> calledNums{};
    calledNums.push_back(num);
    char checker {};
    checker = input.get();
    while(checker != '\n'){
        input >> num;
        calledNums.push_back(num);
        checker = input.get();
    }
    std::vector<bingoBoard> boards {};
    while(!input.eof()) {
        bingoBoard board {};
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                int x;
                input >> x;
                bingoSquare square {};
                square.num = x;
                square.row = i;
                square.column = j;
                board.board.insert({x, square});
                board.sumOfNums += x;
            }
        }
        boards.push_back(board);
    }
    for(auto x: boards) {
    }
    return playBingo(calledNums, boards);
}

int playBingo(std::vector<int> &numsCalled, std::vector<bingoBoard> &boards) {
    for(int x : numsCalled) {
        for(bingoBoard &y : boards) {
            if(y.board.find(x) != y.board.end()) {
                bingoSquare current = y.board.at(x);
                y.sumOfNums -= x;
                y.remainingInColumns.at(current.column)--;
                y.remainingInRows.at(current.row)--;
                if(y.remainingInColumns.at(current.column) == 0) { return x*y.sumOfNums; }
                if(y.remainingInRows.at(current.row) == 0) { return x*y.sumOfNums; }
            }
        }
    }
    return 0;
}
