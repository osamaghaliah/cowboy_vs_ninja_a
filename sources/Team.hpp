/**
 * This class represents a team of fighters - either cowboys or ninjas.
 * A team has the ability to assign a captain for themselves and to attack the opponent team.
 * NOTE :- A team can have a maximum of 10 fighters.
 *
 * @author Osama M. Ghaliah
 */

#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include <vector>
#include "Point.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"

using namespace std;

namespace ariel {
    class Team {
        private:
            Character captain;
            vector <Character> fighters;

        public:
            // Constructor.
            Team(Character *captain);

            // Essential methods for the battle.
            void add(Character *fighter);
            void attack(Team *opponent);
            int stillAlive();
            void print();

            // Getters & setters.
            Character getCaptain();
            void setCaptain(Character captain);
            vector <Character> getFighters();
            void setFighters(vector <Character> fighters);
    };
};

#endif