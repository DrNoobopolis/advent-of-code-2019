
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

#include "intcode.h"

int main() {
    program single;

    std::vector<int> pinball;

    single.run(pinball);

    int max_x=0, max_y=0, counter=0;
    for(auto element : pinball) {
        if(counter == 0) {
            if(element > max_x) {
                max_x = element;
            }
        }
        else if(counter == 1) {
            if(element > max_y) {
                max_y = element;
            }
        }
        counter++;
        if(counter == 3) {
            counter = 0;
        }
    }

    int screen[max_y][max_x] = {0};

    int ans = 0;

    int x, y;
    counter = 0;
    for(auto element : pinball) {
        if(counter == 0) {
            x = element;
        }
        else if(counter == 1) {
            y = element;
        }
        else if(counter == 2) {
            screen[y][x] = element;
            
            if(element == 2) {
                ans++;
            }
        }
        counter++;  
        if(counter == 3) {
            counter = 0;
        }      
    }

    for(int yi = 0; yi < max_y; yi++) {
        for(int xi = 0; xi < max_x; xi++) {
            std::cout << screen[yi][xi] << " ";         
        }
        std::cout << std::endl;
    }

    std::cout << ans << std::endl;

}