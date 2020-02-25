
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

#include "intcode.h"

/*
intcode
    day 2
    day 5
    day 7
    day 9
        day 11
*/

int main() {
    std::vector<int> phase_settings = {5, 6, 7, 8, 9};
    std::vector<int> saved_configuration = phase_settings;
    int highest = batch(phase_settings);

    while(std::next_permutation(phase_settings.begin(), phase_settings.end())) {
        int current = batch(phase_settings);

        if(current > highest) {
            highest = current;
            saved_configuration = phase_settings;
        }
    }

    std::cout << highest << std::endl;   

    return 0;
}
