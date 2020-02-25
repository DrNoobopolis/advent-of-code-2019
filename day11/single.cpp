
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdio.h>

void printArray(std::vector<long> const & input) {
    for(long element : input) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

void printVector(std::vector<long> const & _inputVector) {
    for(auto element : _inputVector) {
        std::cout << element << std::endl;
    }
}

struct program {
    private:
        std::vector<long> intcode;
        bool first = true;
        
        std::vector<long> read() {
            std::vector<long> output;

            std::ifstream read;
            read.open("input.txt"); 

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
        
        long find(std::vector<long> const & _inputVector, long _iterator, long _offset) {
            long mode = _inputVector[_iterator];
            mode /= 10*pow(10, _offset); 
            
            mode %= 10;

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
        
        long iterator = 0;        
        long relative_base = 0;

    public:   
        void run() {
            for(; iterator<intcode.size(); ) {        
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
                        long input;
                        std::cin >> input;
                        intcode[find(intcode, iterator, 1)] = input; //203

                        //broken now since LHS does not use find
                        //find should return an address anyway
                        //then modify intcode using that

                        iterator += 2;
                        break;

                    case 4 : //output
                        std::cout << intcode[find(intcode, iterator, 1)] << std::endl;
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
        }

        long get_duration() {
            return intcode.size();
        }  
        
        program() {
            intcode = read();
            intcode.reserve(1000);

            //std::bad_alloc, attempt to allocate too much memory
        }
};

const long duration = program().get_duration();

void print(int grid[5][5]) {
    for(int y = 0; y < 5; y++) {
        for(int x = 0; x < 5; x++) {
            switch(grid[y][x]) {
                case 0 : 
                    std::cout << ".";
                    break;
                case 1 : 
                    std::cout << "#";
                    break;
                case 2 : 
                    std::cout << "<";
                    break;
                case 3 : 
                    std::cout << "^";
                    break;
                case 4 : 
                    std::cout << ">";
                    break;
                case 5 : 
                    std::cout << "v";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

int change(int &it, bool right) {
    int arrow[] = {2, 3, 4, 5};

    int output;

    if(right) { //right
        it++;

        if(it == 4) {
            it = 0;
        }
    }
    else {
        it--;

        if(it == -1) {
            it = 3;
        }
    }

    return output =  arrow[it];
}

int grid[5][5] = {0};
bool painted[5][5] = {0};

std::pair<int,int> position = {2,2};

int iterator = 1;

void draw(bool white, bool right) {
    int symbol = change(iterator, right);

    grid[position.first][position.second] = white;
    painted[position.first][position.second] = 1;

    switch(symbol) {
        case 2: position.second--;
                break;
        case 3: position.first--;
                break;
        case 4: position.second++;
                break;
        case 5: position.first++;
                break;
    }

    if(position.second < 0 || position.second > 4) {
        std::cout << "error1" << std::endl;
        exit(3);
    }
    if(position.first < 0 || position.first > 4) {
        std::cout << "error2" << std::endl;
        exit(3);
    }
    
    grid[position.first][position.second] = symbol;

    print(grid);
    std::cout << std::endl;
}

//this is working better than modules

void batch() {
    draw(1,0); 
    
    draw(0,0);
    
    draw(1,0); 
    draw(1,0);
    
    draw(0,1);
    draw(1,0);
    draw(1,0);
    
    int counter = 0;
    for(int y = 0; y < 5; y++) {
        for(int x = 0; x < 5; x++) {
            if(painted[y][x]) {
                counter++;
            }
        }
    }

    std::cout << counter << std::endl;
}

void fail() {
    draw(1,0); 
    draw(1,0);
    draw(1,1); 
    draw(1,0);
    draw(1,1);
    draw(1,0);
    draw(1,0);
}


int main() { 
    batch();
    //fail();

    program single;
    single.run();

    return 0;
}


//now need to figure out how the intcode computer can 
//talk to this painter robot

//need to clean up both code bases independently and 
//write documentation

/*
input
camera

output
move drone

*/
