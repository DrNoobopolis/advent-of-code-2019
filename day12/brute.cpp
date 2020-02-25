
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <set>
#include <sstream>

struct velocity {
    int x, y, z;

    bool operator==(velocity velocity1) {
        if(this->x == velocity1.x && this->y == velocity1.y &&  this->z == velocity1.z) { 
            return true;
        }
        return false;
    }

    velocity() {
        x = 0, y = 0, z = 0;
    }
};

struct position {
    int x, y, z;

    bool operator==(position position1) {
        if(this->x == position1.x && this->y == position1.y &&  this->z == position1.z) { 
            return true;
        }
        return false;
    }

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

    bool operator==(moon moon1) {
        if(this->moon_velocity == moon1.moon_velocity && this->moon_position == moon1.moon_position) {
            return true;
        }
        return false;
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

moon Io(17, -7, -11);
moon Europa(1, 4, -1); 
moon Ganymede(6, -2, -6);
moon Callisto(19, 11, 9);

int main () {

    std::vector<moon*> moons;
    moons.push_back(&Io);
    moons.push_back(&Europa);
    moons.push_back(&Ganymede);
    moons.push_back(&Callisto);

    std::set<std::string> history;

    bool match = false;

    while(match == false) {

        if(history.find(string_key(moons)) != history.end()) {
            std::cout << "ans " << history.size() << std::endl;

            match = true;
        }

                          //4686774924                            
        if(history.size() % 1000000 == 0) {
            std::cout << history.size() << std::endl;
        }

        history.insert(string_key(moons));
            
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

    //std::cout << history.size() << std::endl;

    return 0;
}
