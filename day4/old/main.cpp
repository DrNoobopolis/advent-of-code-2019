#include <iostream>

bool valid(int);

int main() {

    /*
    valid(122345);
    valid(111123);
    valid(135679);
    valid(111111);
    valid(223450);
    valid(135789);
    */
    
    // /*
    int count=0;

    for(int i=387638; i<919123+1; i++) {
        if(valid(i)) {
            count++;
        }
    }

    std::cout << std::endl;
    std::cout << count << std::endl;
    // */

    return 0;
}

bool valid(int input) {

    int current = input;
    bool doublef = false;

    while(current > 0) {
        if(current%10 < current/10%10) {
            std::cout << input << " false" << std::endl;
            return false;
        }
        
        if(current%10 == current/10%10) {
            doublef = true;
        }

        current /= 10;
    }

    if(doublef) {
        std::cout << input << " true" << std::endl;
        return true;
    }
    else {
        std::cout << input << " false" << std::endl;
        return false;
    }

}
