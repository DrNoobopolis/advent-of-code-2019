
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

std::vector<int> read();
void printVector(std::vector<int> const &);
int find(std::vector<int> const &, int, int);

int main() {

    std::vector<int> userProgram = read();

    //printVector(userProgram);

    for(int it=0; it<userProgram.size(); ) {
        
        switch (userProgram[it]%100) {
            case 1 : 
                //userProgram[it+3] MUST contain an address to return the output to
                //userProgram[it+3] -> userProgram[it+3].type == 0
                
                userProgram[userProgram[it+3]] = find(userProgram, it, 1) + find(userProgram, it, 2);
                it += 4;
                break;
                    
            case 2 :
                userProgram[userProgram[it+3]] = find(userProgram, it, 1) * find(userProgram, it, 2);
                it += 4;
                break;

            case 3 :
                std::cin >> userProgram[userProgram[it+1]];
                it += 2;
                break;

            case 4:
                std::cout << find(userProgram, it, 1) << std::endl;
                it += 2;
                break;

            case 5:
                if(find(userProgram, it, 1) != 0) {
                    it = find(userProgram, it, 2);
                }
                else {
                    it += 3;
                }
                break;

            case 6:
                if(find(userProgram, it, 1) == 0) {
                    it = find(userProgram, it, 2);
                }
                else {
                    it += 3;
                }
                break;
                
            case 7:
                if(find(userProgram, it, 1) < find(userProgram, it, 2)) {
                    userProgram[userProgram[it+3]] = 1;
                }
                else {
                    userProgram[userProgram[it+3]] = 0;
                }
                it += 4;
                break;


            case 8:
                if(find(userProgram, it, 1) == find(userProgram, it, 2)) {
                    userProgram[userProgram[it+3]] = 1;
                }
                else {
                    userProgram[userProgram[it+3]] = 0;
                }
                it += 4;                
                break;

            case 99 :
                it = userProgram.size(); //GOTO
                break;

            default:
                std::cerr << "error" << std::endl;
                it = userProgram.size(); //GOTO
                break;
        }

        //std::cout << std::endl;
        //printVector(userProgram);
    }    

    //printVector(userProgram);

    return 0;
}

int find(std::vector<int> const & _inputVector, int _iterator, int _offset) {

    //_offset -> _offset >= 1
    //type -> (type == 0) || (type == 1)
    
    //determines the type of the element at _inputVector[_iterator+_offset] 

    //type is 0 by default (_inputVector[_iterator] < 10*pow(10, _offset))

    int type = _inputVector[_iterator]; //first element (containing opcode and type)
    type /= 10*pow(10, _offset); //access particular digit
    
    //type %= 2; //replaced, previous obfuscates user error
    type %= 10;

    if(type == 0) {
        return _inputVector[_inputVector[_iterator+_offset]];
    }
    else if(type == 1) {
        return _inputVector[_iterator+_offset];
    }
    else {
        std::cerr << "variable at address " << _iterator+_offset << " has undefined type" << std::endl;
        return -1; //exception handling
    }

}

void printVector(std::vector<int> const & _inputVector) {
    for(auto element : _inputVector) {
        std::cout << element << std::endl;
    }
}

std::vector<int> read() {
    std::vector<int> outputVector;
    
    std::ifstream read;
    
    read.open("input.txt");

    int temp;
    char bin;
    while(!read.eof()) {
        read >> temp;
        outputVector.push_back(temp);
        read >> bin;
    }

    read.close();

    return outputVector;
}
