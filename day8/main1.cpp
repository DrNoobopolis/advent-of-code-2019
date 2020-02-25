
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

int main() {
    std::ifstream read;
            
    read.open("input.txt");

    std::vector<int> current_image;
    char pixel;
    int clock = 0;

    while(!read.eof()) {
        read >> pixel;

        if(clock < 150) { //less than 150
            current_image.push_back(int(pixel) - 48);
        }
        
        if(clock > 149) { //150 and up
            if(current_image[clock%150] == 2) {
                current_image[clock%150] = int(pixel) - 48;
            }
        }

        clock++;
    }

    read.close();

    /*
    int zero = std::count(current_image.begin(), current_image.end(), 0);
    int one = std::count(current_image.begin(), current_image.end(), 1);
    int two = std::count(current_image.begin(), current_image.end(), 2);
    std::cout << zero << " " << one << " " << two << std::endl;
    */

    bool first = true;
    for(int y=0; y<150; y++) {
        if(y%25 == 0 && !first) {
            std::cout << std::endl;
        }
        first = false;

        if(current_image[y] == 1) {
            std::cout << "\u25A0";
        }
        else {
            std::cout << ".";
        }
    }
    std::cout << std::endl;

    return 0;
}
