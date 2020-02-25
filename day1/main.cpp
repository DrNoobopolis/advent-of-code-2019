
#include <iostream>
#include <fstream>

int main() {
    std::ifstream read;
    read.open("saved.txt");

    int total = 0;

    int mass;
    while(!read.eof()) {
        read >> mass;
    
        total += mass/3-2;
    }
    
    read.close();
    
    std::cout << total << std::endl; //3226488

    return 0;
}
