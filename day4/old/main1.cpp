#include <iostream>

bool valid(int);

int main() {

    int count=0;

    for(int i=387638; i<919123+1; i++) {
        if(valid(i)) {
            count++;
        }
    }

    //std::cout << std::endl;
    std::cout << count << std::endl;

    return 0;
}

bool valid(int input) {

    int current = input;
    bool doublef = false;
    bool pass = false; //more permanent

    int count = 2;

    while(current > 0) {
        if(current%10 < current/10%10) {
            //std::cout << input << " false" << std::endl;
            return false;
        }
        
        if(current%10 == current/10%10 && count != 1) {
            doublef = true;
            count = 0;
        }

        if(current%10 == current/10%10 && count == 1) { //failing this should not end it
            doublef = false;
            count = 0;
        }

        //the rule is that the doublef flag has detected a tripple or higher
        //so it because false

        //but... without "pass" doubles appearing prior to tripples or higher are erased
        
        //pass takes doublef=true when it is confirmed that a double has been detected

        //doublef is more of a temp variable pass is our new "doublef"

        if(doublef && count == 1) {
            pass = true;
        }

        current /= 10;

        count++;
    }

    if(pass) {
        //std::cout << input << " true" << std::endl;
        return true;
    }
    else {
        //std::cout << input << " false" << std::endl;
        return false;
    }

}
