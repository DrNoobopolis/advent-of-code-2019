
#include <iostream>
#include <cstdlib>
#include <vector>

struct velocity {
    int x, y, z;

    velocity() {
        x = 0, y = 0, z = 0;
    }
};

struct position {
    int x, y, z;

    position() {}

    position(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct moon {
    velocity moon_velocity; 
    position moon_position;

    moon(int x, int y, int z) {
        moon_position = position(x, y, z);
    }

    int potential_energy() {
        return abs(moon_position.x) + abs(moon_position.y) + abs(moon_position.z);
    }

    int kinetic_energy() {
        return abs(moon_velocity.x) + abs(moon_velocity.y) + abs(moon_velocity.z);
    }
    
    int total_energy() {
        return potential_energy() * kinetic_energy();
    }
};

//need my own medicare card

void gravity(moon &moon1, moon &moon2) {

    if(moon1.moon_position.x != moon2.moon_position.x) {
        if(moon1.moon_position.x > moon2.moon_position.x) {
            moon1.moon_velocity.x--;
            moon2.moon_velocity.x++;
        }
        else {
            moon1.moon_velocity.x++;
            moon2.moon_velocity.x--;
        }
    }

    if(moon1.moon_position.y != moon2.moon_position.y) {
        if(moon1.moon_position.y > moon2.moon_position.y) {
            moon1.moon_velocity.y--;
            moon2.moon_velocity.y++;
        }
        else {
            moon1.moon_velocity.y++;
            moon2.moon_velocity.y--;
        }
    }

    if(moon1.moon_position.z != moon2.moon_position.z) {
        if(moon1.moon_position.z > moon2.moon_position.z) {
            moon1.moon_velocity.z--;
            moon2.moon_velocity.z++;
        }
        else {
            moon1.moon_velocity.z++;
            moon2.moon_velocity.z--;
        }
    }
}

void move(moon &moon1) {
    moon1.moon_position.x += moon1.moon_velocity.x;
    moon1.moon_position.y += moon1.moon_velocity.y;
    moon1.moon_position.z += moon1.moon_velocity.z;
}

void print(const moon e_moon) {
    std::cout << "pos=<x=" << e_moon.moon_position.x << ", y=" << e_moon.moon_position.y << ", z=" << e_moon.moon_position.z << ">, ";
    std::cout << "vel=<x=" << e_moon.moon_velocity.x << ", y=" << e_moon.moon_velocity.y << ", z=" << e_moon.moon_velocity.z << ">";
    std::cout << std::endl; 
}

std::string string_key(std::vector<moon*> moons) {
    std::stringstream ss;
        
    for(auto e_moon : moons) {
        ss << e_moon->moon_position.x << " ";
        ss << e_moon->moon_position.y << " ";
        ss << e_moon->moon_position.z << " ";
        ss << e_moon->moon_velocity.x << " ";
        ss << e_moon->moon_velocity.y << " ";
        ss << e_moon->moon_velocity.z << " ";
    }

    return ss.str();
}

/*
lcm [least common multiple]

lcm(a, b) = |a*b| / gcd(a, b)

gcd [greatest common divisor]
hcf [highest common factor]

gcd == hcf

euclidean algorithm, is an efficient method for computing the hcf
(of two numbers)


*/

int main () {
 
    moon Io(17, -7, -11);
    moon Europa(1, 4, -1); 
    moon Ganymede(6, -2, -6);
    moon Callisto(19, 11, 9);

    std::vector<moon*> moons;
    moons.push_back(&Io);
    moons.push_back(&Europa);
    moons.push_back(&Ganymede);
    moons.push_back(&Callisto);

    int time = 0;
    for(; time < 1000; time++) { //1000
        std::cout << "After " << time << " steps:" << std::endl;
        for(auto e_moon : moons) {
            print(*e_moon);
        }
        std::cout << std::endl;
        
        gravity(Io, Europa);
        gravity(Io, Ganymede);
        gravity(Io, Callisto);
        gravity(Europa, Ganymede);
        gravity(Europa, Callisto);
        gravity(Ganymede, Callisto);

        for(auto e_moon : moons) {
            move(*e_moon);
        }
    }

    std::cout << "After " << time << " steps:" << std::endl;
    for(auto e_moon : moons) {
        print(*e_moon);
    }
    std::cout << std::endl;

    int sum_total = 0;
    for(auto e_moon : moons) {
        sum_total += e_moon->total_energy();
    }

    std::cout << sum_total << std::endl;

    return 0;
}
