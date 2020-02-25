#include <iostream>

bool valid(int);

int main() {
    int output=0;

    for(int i=387638; i<919123+1; i++) {
        if(valid(i)) {
            output++;
        }
    }

    std::cout << output << std::endl;

    return 0;
}

bool valid(int input) {
    int current = input;
    bool temp = false;
    bool doublef = false; 

    int count = 2; //used to ensure true doubles

    while(current > 0) {
        if(current%10 < current/10%10) { //future is less
            return false;
        }
        
        if(current%10 == current/10%10 && count != 1) { //repeated digit
            temp = true;
            count = 0;
        }

        if(current%10 == current/10%10 && count == 1) { //3x or more occurences
            temp = false;
            count = 0;
        }

        if(temp && count == 1) { //true double
            doublef = true;
        }

        current /= 10; //next digit

        count++;
    }

    if(doublef) {
        return true;
    }
    else {
        return false;
    }

}
