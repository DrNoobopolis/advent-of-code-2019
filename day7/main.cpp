
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

std::vector<int> read();
void printVector(std::vector<int> const &);
int find(std::vector<int> const &, int, int);
void run(int &, int, int);
int batch(int, int, int, int, int);

int main() {

    int myints[] = {0, 1, 2, 3, 4};

    int highest = batch(myints[0], myints[1], myints[2], myints[3], myints[4]);

    while(std::next_permutation(myints,myints+5)) {
        int current = batch(myints[0], myints[1], myints[2], myints[3], myints[4]);

        if(current > highest) {
            highest = current;
        }
    }

    std::cout << highest << std::endl;   

    return 0;
}

int batch(int A, int B, int C, int D, int E) {
    int output = 0;
    
    run(output, A, output);
    run(output, B, output);
    run(output, C, output);
    run(output, D, output);
    run(output, E, output);

    return output;
}

void run(int &output, int phase, int input) {
    std::vector<int> userProgram = read();

    bool first = true;

    for(int it=0; it<userProgram.size(); ) {
        
        switch (userProgram[it]%100) {
            case 1 : 
                userProgram[userProgram[it+3]] = find(userProgram, it, 1) + find(userProgram, it, 2);
                it += 4;
                break;
                    
            case 2 :
                userProgram[userProgram[it+3]] = find(userProgram, it, 1) * find(userProgram, it, 2);
                it += 4;
                break;

            case 3 :
                //std::cin >> userProgram[userProgram[it+1]];
                if(first) {
                    userProgram[userProgram[it+1]] = phase;
                    first = false;
                }
                else {
                    userProgram[userProgram[it+1]] = input;
                }

                it += 2;
                break;

            case 4:
                //std::cout << find(userProgram, it, 1) << std::endl;
                output = find(userProgram, it, 1);
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
    }    
}

int find(std::vector<int> const & _inputVector, int _iterator, int _offset) {
    int type = _inputVector[_iterator];
    type /= 10*pow(10, _offset); 
    
    type %= 10;

    if(type == 0) {
        return _inputVector[_inputVector[_iterator+_offset]];
    }
    else if(type == 1) {
        return _inputVector[_iterator+_offset];
    }
    else {
        std::cerr << "variable at address " << _iterator+_offset << " has undefined type" << std::endl;
        return -1;
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
