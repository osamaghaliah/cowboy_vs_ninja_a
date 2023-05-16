#include "Character.hpp"

namespace ariel {
    Character::Character() {

    }

    Character::Character(string name, Point location, int hitpoint) {

    }

    Point Character::getLocation() {

        return this->location;
    }

    void Character::setLocation(Point other) {

    }

    string Character::getName() {

        return " ";
    }

    void Character::setName(string name) {

    }

    int Character::getHitpoint() {

        return 0;
    }

    void Character::setHitpoint(int hitpoint) {

    }

    bool Character::isAlive() {

        return true;
    }

    double Character::distance(Character *character) {

        return 0;
    }

    void Character::hit(int damage) {

    }

    string Character::print() {

        return " ";
    }
}