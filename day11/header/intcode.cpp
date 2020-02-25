
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

#include "intcode.h"

#include "paint.h"

std::vector<long> program::read() {
    std::vector<long> output;

    std::ifstream read;
    read.open("input.txt", std::ios_base::app); 

    long input; //local
    char remove;

    while(!read.eof()) {
        read >> input; //intcode
        output.push_back(input); //store

        read >> remove; //throw ','
    }

    read.close();

    return output;
}

long program::get_duration() {
    return intcode.size();
}  
        
program::program() {
    intcode.reserve(10000);
    for(auto element : intcode) {
        element = 0;
    }

    intcode = read();
}    

int iterator2 = 0;

void program::run() {
    printVector(intcode);

    bool firstOutput, secondOutput;
    bool first = true;

    //std::ofstream file;
    //file.open("output.txt", std::ios_base::app);

    for(; iterator<intcode.size(); ) {       
        iterator2++;

        switch (intcode[iterator]%100) {

            case 1 : //add
                intcode[find(intcode, iterator, 3)] = intcode[find(intcode, iterator, 1)]+ intcode[find(intcode, iterator, 2)];
                iterator += 4;
                break;
                            
            case 2 : //multiply
                intcode[find(intcode, iterator, 3)] = intcode[find(intcode, iterator, 1)]* intcode[find(intcode, iterator, 2)];
                iterator += 4;
                break;

            case 3 : //input
                intcode[find(intcode, iterator, 1)] = camera();
                //file << camera() << std::endl;
                iterator += 2;
                break;

            case 4 : //output
                //file << intcode[find(intcode, iterator, 1)] << std::endl;

                if(first){
                    firstOutput = intcode[find(intcode, iterator, 1)];
                    first = false;
                }   
                else {
                    secondOutput = intcode[find(intcode, iterator, 1)];
                    draw(firstOutput,secondOutput); //first and second are swapped around?
                    first = true;
                }
                
                iterator += 2;
                break;

            case 5 : //jump-if-true
                if(intcode[find(intcode, iterator, 1)] != 0) {
                    iterator = intcode[find(intcode, iterator, 2)];
                }
                else {
                    iterator += 3;
                }
                break;

            case 6 : //jump-if-false
                if(intcode[find(intcode, iterator, 1)]== 0) {
                    iterator = intcode[find(intcode, iterator, 2)];
                }
                else {
                    iterator += 3;
                }
                break;
                        
            case 7 : //less than
                if(intcode[find(intcode, iterator, 1)]< intcode[find(intcode, iterator, 2)]) {
                    intcode[find(intcode, iterator, 3)] = 1;
                }
                else {
                    intcode[find(intcode, iterator, 3)] = 0;
                }
                iterator += 4;
                break;

            case 8 : //equals
                if(intcode[find(intcode, iterator, 1)]== intcode[find(intcode, iterator, 2)]) {
                    intcode[find(intcode, iterator, 3)] = 1;
                }
                else {
                    intcode[find(intcode, iterator, 3)] = 0;
                }
                iterator += 4;                
                break;

            case 9 : //adjusts the relative base
                relative_base += intcode[find(intcode, iterator, 1)];
                iterator += 2;
                break;

            case 99 : //hault
                iterator = intcode.size();
                return;

            default : //error
                std::cerr << "intcode unkown: " << intcode[iterator] << std::endl;
                return;
        }
    } 

    std::cout << iterator2 << std::endl;

    //file.close(); 
}

void printArray(std::vector<long> const & input) {
    for(long element : input) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

//might clean this up a bit
//ugly syntax

//needs a bit of a refactor
long program::find(std::vector<long> const & _inputVector, long _iterator, long _offset) {
    long mode = _inputVector[_iterator];
    mode /= 10*pow(10, _offset); 
    
    mode %= 10;

    if(_iterator+_offset > _inputVector.capacity()) {
        std::cerr << "too small" << std::endl;
    }

    if(mode == 0) {
        return _inputVector[_iterator+_offset];
    }
    else if(mode == 1) {
        return _iterator+_offset;
    }
    else if(mode == 2) {
        return _inputVector[_iterator+_offset]+relative_base;
    }
    else {
        std::cerr << "mode unknown" << std::endl;
        return -1;
    }

}

void printVector(std::vector<long> const & _inputVector) {
    /*
    std::ofstream file;
    file.open("intcode.txt", std::ios_base::app);
    
    for(auto element : _inputVector) {
        file << element << " ";
    }
    file << std::endl;

    file.close();
    */ 
}
