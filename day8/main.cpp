
/*
left-to-right, then top-to-bottom, layer-by-layer

least #0
return #1 * #2
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

int main() {
    std::ifstream read;
            
    read.open("input.txt");

    std::vector<int> best_image;
    std::vector<int> current_image;
    char pixel;
    int least_zeros = 25*6;
    int current_zeros = 0;
    int clock = 0;

    while(!read.eof()) {
        read >> pixel;
        clock++;

        if(pixel == '0') {
            current_zeros++;
        }
        else {
            current_image.push_back(int(pixel) - 48);
        }

        if(clock == 25*6) {
            clock = 0;

            if(current_zeros < least_zeros) {
                least_zeros = current_zeros; 
                best_image = current_image;
            }

            current_zeros = 0;
            current_image.clear();
        }
    }

    read.close();

    int output = std::count(best_image.begin(), best_image.end(), 1) * std::count(best_image.begin(), best_image.end(), 2);
    std::cout << output << std::endl;

    return 0;
}
