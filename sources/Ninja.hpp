/**
 * This class represents a ninja whom speciality is to slash his enemy and damaging him with 40 HP.
 * Also, he can move a distance which is equal to a certain velocity/speed towards his enemy.
 * The velocity is based on the type of a ninja, there are 3 types of ninjas:
 *  1. YoungNinja.
 *  2. TrainedNinja.
 *  3. OldNinja.
 * Each type of ninja holds his own speciality in terms of velocity and starting HP.
 * NOTE :- A ninja is able to slash his enemy ONLY if the enemy is less than 1 meter close.
 *
 * @author Osama M. Ghaliah
 */

#ifndef NINJA_HPP
#define NINJA_HPP

#include "Cowboy.hpp"

using namespace std;

namespace ariel {
    class Ninja : public Character {
        protected:
            int velocity;

        public:
            // Constructors.
            Ninja();
            Ninja(string name, Point location);

            // Essential methods for the battle.
            void move(Character *enemy);
            void slash(Character *enemy);

            // Getters & setters.
            int getVelocity();
            void setVelocity(int velocity);
    };
};

#endif
