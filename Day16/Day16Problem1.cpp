#include<iostream>
#include<string>
#include<fstream>
#include<vector>

struct Packet {
    int version {0};
    int type {0};
    int literal {0};
};

void readInput(std::vector<char> &binaryVec, std::string s);
void readPacket(std::vector<char> &binaryVec, int &pos, int &end, std::vector<Packet> &packetList);
void parseLiteral(Packet &pckt, std::vector<char> &binaryVec, int &pos);
int solution (std::string s);

int main() {
    int result {solution("test1.txt")};
    assert(result == 16);
    result = solution("test2.txt");
    assert(result == 12);
    result = solution("test3.txt");
    assert(result == 23);
    result = solution("test4.txt");
    assert(result == 31);
    result = solution("input.txt");
    std::cout << result << std::endl;
}

int solution(std::string s) {
    std::vector<char> binaryVec {};
    readInput(binaryVec, s);
    std::vector<Packet> packetList {};
    int pos{0};
    int end {static_cast<int>(binaryVec.size()-1)};
    readPacket(binaryVec, pos, end, packetList);
    int score {0};
    for(auto &x : packetList) {
        score += x.version;
    }
    return score;
}

void readInput(std::vector<char> &binaryVec, std::string s) {
    std::ifstream input {s, std::ifstream::in};
    std::string line {};
    std::getline(input, line);
    for(auto c : line) {
        if('A' <= c && c <= 'F') {
            char bits = (c - '0' - 7);
            ((bits & 0b00001000) > 0) ? binaryVec.push_back('1') : binaryVec.push_back('0');
            ((bits & 0b00000100) > 0) ? binaryVec.push_back('1') : binaryVec.push_back('0');
            ((bits & 0b00000010) > 0) ? binaryVec.push_back('1') : binaryVec.push_back('0');
            ((bits & 0b00000001) > 0) ? binaryVec.push_back('1') : binaryVec.push_back('0');
        }
        else {
            char bits = (c - '0');
            ((bits & 0b00001000) > 0) ? binaryVec.push_back('1') : binaryVec.push_back('0');
            ((bits & 0b00000100) > 0) ? binaryVec.push_back('1') : binaryVec.push_back('0');
            ((bits & 0b00000010) > 0) ? binaryVec.push_back('1') : binaryVec.push_back('0');
            ((bits & 0b00000001) > 0) ? binaryVec.push_back('1') : binaryVec.push_back('0');

        }
    }
}

void readPacket(std::vector<char> &binaryVec, int &pos, int &end, std::vector<Packet> &packetList) {
    Packet pckt {};
    int magnitude {4};
    for(int i {0}; i < 3; i++) {
        if(binaryVec[pos] == '1') {
            pckt.version += magnitude;
        }
        pos++;
        magnitude /= 2;
    }
    magnitude = 4;
    for(int i {0}; i < 3; i++) {
        if(binaryVec[pos] == '1') {
            pckt.type += magnitude;
        }
        pos++;
        magnitude /= 2;
    }
    magnitude = 1;
    if(pckt.type == 4) {
        parseLiteral(pckt, binaryVec, pos);
    }
    else {
        char operatorTypeID {binaryVec[pos]};
        pos++;
        if(operatorTypeID == '0') { //Length in Bits
            std::vector<char> lengthInBits {};
            //Read total length in bits of subpacket
            for(int i {0}; i < 15; i++) {
                (binaryVec[pos] == '1') ? lengthInBits.push_back('1') : lengthInBits.push_back('0');
                pos++;
            }
            //Convert length in bits in binary to int
            int length {0};
            for(int i {static_cast<int>(lengthInBits.size()-1)}; i >= 0; i--) {
                if(lengthInBits[i] == '1') {
                    length += magnitude;
                }
                magnitude *= 2;
            }
            int currentBitPos {pos};
            int endPos {length + currentBitPos}; 
            while(currentBitPos < endPos) {
                readPacket(binaryVec, currentBitPos, endPos, packetList);
            }
            pos = currentBitPos;
        }
        else { //Lenght in packets
            int numOfPackets {0};
            std::vector<char> packetLengthInBinary {};
            for(int i {0}; i < 11; i++) {
                (binaryVec[pos] == '1') ? packetLengthInBinary.push_back('1') : packetLengthInBinary.push_back('0');
                pos++;
            }
            magnitude = 1;
            for(int i {static_cast<int>(packetLengthInBinary.size()-1)}; i >= 0; i--) {
                if(packetLengthInBinary[i] == '1') {
                    numOfPackets += magnitude;
                }
                magnitude *= 2;
            }
            for(int i {0}; i < numOfPackets; i++) {
                readPacket(binaryVec, pos, end, packetList);
            }
        }
    }
    packetList.push_back(pckt);
}

void parseLiteral(Packet &pckt, std::vector<char> &binaryVec, int &pos) {
    std::vector<char> literalInterpreter {};
    while(binaryVec[pos] == '1') {
        pos++;
        for(int i {0}; i < 4; i++) {
            (binaryVec[pos] == '1') ? literalInterpreter.push_back('1') : literalInterpreter.push_back('0');
            pos++;
        }
    }
    pos++;
    for(int i {0}; i < 4; i++) {
        (binaryVec[pos] == '1') ? literalInterpreter.push_back('1') : literalInterpreter.push_back('0');
        pos++;
    }
    int exponentiator {1};
    for(int i {static_cast<int>(literalInterpreter.size()-1)}; i >= 0; i--) {
        if(literalInterpreter[i] == '1')  {
            pckt.literal += exponentiator;
        }
        exponentiator *= 2;
    }
}