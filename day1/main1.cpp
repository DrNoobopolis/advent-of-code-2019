
#include <iostream>
#include <fstream>
#include <chrono>

void lessmem(int &);
void recursion(int &);

int total = 0;

/*
adventofcode.com/2019/day/2

godbolt.org/
youtube.com/watch?v=soeFwz0cOqU

github.com/

valgrind
*/

int main() {
    auto start = std::chrono::steady_clock::now();

    std::ifstream read;
    read.open("saved.txt");

    int mass = 0;
    
    while(!read.eof()) {
        read >> mass;
        
        //0.000212
        
        lessmem(mass);
        //recursion(mass); 
    }
    
    read.close();
    
    std::cout << total << std::endl; //4836845
    
    auto end = std::chrono::steady_clock::now();    
    double duration = std::chrono::duration<double>(end-start).count();
    std::cout << std::fixed << duration << std::endl;  

    return 0;
}

void recursion(int &input) {
    input = input/3-2;

    if(input < 1) {
        return;
    }

    total += input;
    
    recursion(input);
}

void lessmem(int &input) {
    while(input > 0) {
        input = input/3-2;

        if(input < 1) {
            break; //continue;
        }       

        total += input;
    }

    return;
}
