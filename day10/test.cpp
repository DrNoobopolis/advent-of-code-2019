
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
//#include <math.h>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <cstdlib>

double calc1(int y2, int y1, int x2, int x1) {
    return double(double(y2 - y1)/double(x2 - x1));
}

double hdr(std::pair<int,int> b, std::pair<int,int> a) {
    return calc1(b.second, a.second, b.first, a.first);
}

//manhattan distance formula
int distance(int y2, int y1, int x2, int x1) {
    return 1; 
}

//right-angled triangle trigonometry
double CAH(double adjacent, double hypotenuse) {
    double radians = std::acos(adjacent/hypotenuse);
    double degrees = radians*180/M_PI;

    return degrees;
} 

int main() {
    std::pair<int,int> from={6,2}, to={4,3};

    //int manhattan = std::abs(a.first-b.first)+std::abs(a.second-b.second);
    double hypotenuse = std::sqrt(std::pow(from.first-to.first,2)+std::pow(from.second-to.second,2)); //euclidean

    bool going_up = to.second > from.second;
    bool going_right = to.first > from.first;

    //rearrang equadrants so that they go from 0 to 360

    if(to.second == from.second) { //horizontal
        if(going_right) {
            std::cout << "90" << std::endl;
        }
        else {
            std::cout << "270" << std::endl;
        }
    }
    else if(to.first == from.first) { //vertical
        if(going_up) {
            std::cout << "0" << std::endl;
        }
        else {
            std::cout << "180" << std::endl;
        }
    } 
    else {
        if(going_up && going_right) {
            //quadrant 1

            if(to.second >= to.first-from.first+from.second) {
                //1-45

                double adjacent = double(to.second-from.second);
                double bearing = CAH(adjacent, hypotenuse);

                std::cout << bearing << std::endl;
            }
            else {
                //46-89

                double adjacent = double(to.first-from.first);
                double bearing = 90 - CAH(adjacent, hypotenuse);

                std::cout << bearing << std::endl;
            }
        }
        else if(going_up && !going_right) {            
            //quadrant 4

            if(false) {
                //271-315

                double adjacent = double(to.first-from.first);
                double bearing = 270 + CAH(adjacent, hypotenuse);

                std::cout << bearing << std::endl;
            }
            else {
                //316-359
        
                double adjacent = double(to.second-from.second);
                double bearing = 360 - CAH(adjacent, hypotenuse);

                std::cout << bearing << std::endl;
            }
        }
        else if(!going_up && !going_right) {
            //quadrant 3
        
            std::cout << "a" << std::endl;
        }
        else if(!going_up && going_right) {
            //quadrant 2

            std::cout << "b" << std::endl;

            //91-135
            //136-179
        }
    }

    return 0;
}

/*
gradient 
m = (y2-y1)/(x2-x1)

point gradient formula
y - y1 = m(x - x1)

*/
