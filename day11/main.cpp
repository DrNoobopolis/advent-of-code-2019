
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdio.h>

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

    //program single;
    //single.run();

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
