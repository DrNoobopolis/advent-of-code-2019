
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdio.h>

#include "intcode.h"
#include "paint.h"

int main() {
    std::ofstream file;
    file.open("output.txt");
    file.close();
    //file.open("intcode.txt");
    //file.close(); 

    //part1();

    program single;
    single.run();

    count();
    print_painted();
    print_grid();

    //this whole thing is kind of messed up

    //output code
    //BFEAGHAF

    //painted
    //249

    return 0;
}
