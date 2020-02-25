
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

#include "intcode.h"

std::vector<int> program::read() {
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

int program::get_duration() {
    return intcode.size();
} 
        
program::program(int input2) {
    intcode = read();
    phase = input2;
}    
        
program::program() {
    intcode = read();
}    

void program::run(int & input_output) {    
    for(; iterator<intcode.size(); ) {
        switch (intcode[iterator]%100) {
            case 1 : //add
                intcode[intcode[iterator+3]] = find(intcode, iterator, 1) + find(intcode, iterator, 2);
                iterator += 4;
                break;
                            
            case 2 : //multiply
                intcode[intcode[iterator+3]] = find(intcode, iterator, 1) * find(intcode, iterator, 2);
                iterator += 4;
                break;

            case 3 : //input
                if(first) {
                    intcode[intcode[iterator+1]] = phase;
                    first = false;
                }
                else {
                    intcode[intcode[iterator+1]] = input_output;
                }
                iterator += 2;
                break;

            case 4 : //output
                input_output = find(intcode, iterator, 1);
                iterator += 2;
                return;

            case 5 : //a
                if(find(intcode, iterator, 1) != 0) {
                    iterator = find(intcode, iterator, 2);
                }
                else {
                    iterator += 3;
                }
                break;

            case 6 : //a
                if(find(intcode, iterator, 1) == 0) {
                    iterator = find(intcode, iterator, 2);
                }
                else {
                    iterator += 3;
                }
                break;
                        
            case 7 : //a
                if(find(intcode, iterator, 1) < find(intcode, iterator, 2)) {
                    intcode[intcode[iterator+3]] = 1;
                }
                else {
                    intcode[intcode[iterator+3]] = 0;
                }
                iterator += 4;
                break;

            case 8 : //a
                if(find(intcode, iterator, 1) == find(intcode, iterator, 2)) {
                    intcode[intcode[iterator+3]] = 1;
                }
                else {
                    intcode[intcode[iterator+3]] = 0;
                }
                iterator += 4;                
                break;

            case 99 : //hault
                //std::cout << "boom" << std::endl;
                iterator = intcode.size();
                return;

            default : //error
                std::cerr << "intcode unkown: " << intcode[iterator] << std::endl;
                return;
        }
    }  
}

void printArray(std::vector<int> const & input) {
    for(int element : input) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

std::vector<program> generate(std::vector<int> input) {
    std::vector<program> collection;

    for(auto temp : input) {
        collection.push_back(program(temp));
    }

    return collection;
}

int batch(std::vector<int> phase_settings) {    
    
    std::vector<program> programs = generate(phase_settings);

    int output=0;

    //could be written alot more succinctly
    while(std::min_element(programs.begin(), programs.end(), [](const program& a, const program& b){return a.iterator < b.iterator;})->iterator < duration) {
        
        //be careful, must ensure element is passed by reference 
        for(program& element : programs) { 
            element.run(output);
        }
    }

    return output;
}

int program::find(std::vector<int> const & _inputVector, int _iterator, int _offset) {
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
