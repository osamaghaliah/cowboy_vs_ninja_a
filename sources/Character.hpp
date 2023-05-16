/**
 * This class represents a character which reflects one of the following fighters:
 *  1. Cowboy.
 *  2. Ninja.
 * Each character specializes to damage his opponent and a special HP that they get spawned with.
 * Besides, a character specializes to hold a location (X,Y) of the battle's field and a name.
 *
 * @author Osama M. Ghaliah
 */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Point.hpp"

using namespace std;

namespace ariel {
    class Character {
        protected:
            Point location;
            int hitpoint;
            string name;

        public:
            // Constructors
            Character();
            Character(string name, Point location, int hitpoint);

            // Essential methods for the battle.
            bool isAlive();
            double distance(Character *character);
            void hit(int damage);
            string print();

            // Getters & setters.
            string getName();
            void setName(string name);
            Point getLocation();
            void setLocation(Point other);
            int getHitpoint();
            void setHitpoint(int hitpoint);
    };
};

#endif
