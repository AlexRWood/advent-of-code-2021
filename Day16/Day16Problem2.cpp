#include<iostream>
#include<string>
#include<fstream>
#include<vector>

struct Packet {
    int version {0};
    int type {0};
    int64_t literal {0};
    std::vector<Packet> subPackets {};
};

void readInput(std::vector<char> &binaryVec, std::string s);
void readPacket(std::vector<char> &binaryVec, int &pos, int &end, std::vector<Packet> &packetList);
void parseLiteral(Packet &pckt, std::vector<char> &binaryVec, int &pos);
int64_t solution (std::string s);
int64_t calculate (Packet &pckt);

int main() {
    int64_t result {solution("problem2test1.txt")};
    assert(result == 3);
    result = solution("problem2test2.txt");
    assert(result == 54);
    result = solution("problem2test3.txt");
    assert(result == 7);
    result = solution("problem2test4.txt");
    assert(result == 9);
    result = solution("problem2test5.txt");
    assert(result == 1);
    result = solution("problem2test6.txt");
    assert(result == 0);
    result = solution("problem2test7.txt");
    assert(result == 0);
    result = solution("problem2test8.txt");
    assert(result == 1);
    result = solution("input.txt");
    std::cout << result << std::endl;
}

int64_t solution(std::string s) {
    std::vector<char> binaryVec {};
    readInput(binaryVec, s);
    std::vector<Packet> packetList {};
    int pos{0};
    int end {static_cast<int>(binaryVec.size()-1)};
    readPacket(binaryVec, pos, end, packetList);
    int64_t score {0};
    score = calculate(packetList[0]);
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
    if(pckt.type == 4) { //Read literal
        parseLiteral(pckt, binaryVec, pos);
    }
    else { //Read Operator Packet
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
                readPacket(binaryVec, currentBitPos, endPos, pckt.subPackets);
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
                readPacket(binaryVec, pos, end, pckt.subPackets);
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
    int64_t exponentiator {1};
    for(int i {static_cast<int>(literalInterpreter.size()-1)}; i >= 0; i--) {
        if(literalInterpreter[i] == '1')  {
            pckt.literal += exponentiator;
        }
        exponentiator *= 2;
    }
}

int64_t calculate (Packet &pckt) {
    int64_t result {0};
    if(pckt.type == 4) {
        return pckt.literal;
    }
    else {
        switch(pckt.type) {
            case 0:
                for(auto &x : pckt.subPackets) {
                    result += (calculate(x));
                }
                break;
            case 1:
                result = 1;
                for(auto &x : pckt.subPackets) {
                    result *= calculate(x);
                }
                break;
            case 2:
                result = INT64_MAX;
                for(auto &x : pckt.subPackets) {
                    result = std::min(result, calculate(x));
                }
                break;
            case 3:
                result = INT64_MIN;
                for(auto &x : pckt.subPackets) {
                    result = std::max(result, calculate(x));
                }
                break;
            case 5:
                result = (calculate(pckt.subPackets[0]) > calculate(pckt.subPackets[1])) ? 1 : 0;
                break;
            case 6:
                result = (calculate(pckt.subPackets[0]) < calculate(pckt.subPackets[1])) ? 1 : 0;
                break;
            case 7:
                result = (calculate(pckt.subPackets[0]) == calculate(pckt.subPackets[1])) ? 1 : 0;
                break;
        }
    }
    return result;
}