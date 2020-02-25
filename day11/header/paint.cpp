#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdio.h>

#include "paint.h"

int grid[length][length] = {0};
int painted[length][length] = {0};
std::pair<int,int> position = {length/2,length/2};
int iterator = 1;

int camera_stored = 1;
int camera_live = 1;

int camera() {
    return camera_stored;
}

void part1() {
    for(int y = 0; y < length; y++) {
        for(int x = 0; x < length; x++) {
            grid[y][x] = 1;
        }
    }
}

void count() {
    int counter = 0;
    for(int y = 0; y < length; y++) {
        for(int x = 0; x < length; x++) {
            if(painted[y][x]) {
                counter++;
            }
        }
    }

    std::cout << counter << std::endl;
}

void print(int grid[length][length]) {
    /*std::ofstream file;
    file.open("output.txt", std::ios_base::app);

    for(int y = 0; y < length; y++) {
        for(int x = 0; x < length; x++) {
            switch(grid[y][x]) {
                case 0 : 
                    file << ".";
                    break;
                case 1 : 
                    file << "#";
                    break;
                case 2 : 
                    file << "<";
                    break;
                case 3 : 
                    file << "^";
                    break;
                case 4 : 
                    file << ">";
                    break;
                case 5 : 
                    file << "v";
                    break;
            }
        }
        file << std::endl;
    }

    file.close(); 
    */
}

void print_painted() {
    std::ofstream file;
    file.open("output.txt", std::ios_base::app);

    for(int y = 0; y < length; y++) {
        for(int x = 0; x < length; x++) {
            switch(painted[y][x]) {
                case 0 : 
                    file << ".";
                    break;
                case 1 : 
                    file << "#";
                    break;
                case 2 : 
                    file << "<";
                    break;
                case 3 : 
                    file << "^";
                    break;
                case 4 : 
                    file << ">";
                    break;
                case 5 : 
                    file << "v";
                    break;
            }
        }
        file << std::endl;
    }

    file.close(); 
}

void print_grid() {
    std::ofstream file;
    file.open("output.txt", std::ios_base::app);

    file << std::endl;

    for(int y = 0; y < length; y++) {
        for(int x = 0; x < length; x++) {
            switch(grid[y][x]) {
                case 0 : 
                    file << ".";
                    break;
                case 1 : 
                    file << "#";
                    break;
                case 2 : 
                    file << "<";
                    break;
                case 3 : 
                    file << "^";
                    break;
                case 4 : 
                    file << ">";
                    break;
                case 5 : 
                    file << "v";
                    break;
            }
        }
        file << std::endl;
    }

    file.close(); 
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

//white - right
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

    if(position.second < 0 || position.second > length) {
        std::cout << "error1" << std::endl;
        exit(3);
    }
    if(position.first < 0 || position.first > length) {
        std::cout << "error2" << std::endl;
        exit(3);
    }
    
    camera_stored = camera_live;
    camera_live = grid[position.first][position.second];

    grid[position.first][position.second] = symbol;

    //print(grid);
    //std::cout << std::endl;
}
