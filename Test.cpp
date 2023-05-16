#include "sources/Team.hpp"
#include "doctest.h"
#include <limits>

using namespace ariel;
using namespace std;

double maximalDouble = numeric_limits <double> :: max();
double minimalDouble = numeric_limits <double> :: min();
double epsilon = 0.0001;

TEST_CASE("Objects Initialization & Attributes Retrieving Correctness") {
    // Points initialization.
    Point origin(0, 0), p1(1.5, -3);
    CHECK((origin.getX() == 0 && origin.getY() == 0));
    CHECK((p1.getX() == 1.5 && p1.getY() == -3));
    CHECK_NOTHROW(p1.setX(0));
    CHECK((p1.getX() == 0));
    CHECK_NOTHROW(p1.setY(10));
    CHECK((p1.getY() == 10));

    CHECK_NOTHROW(Point(7.2, 2.7));
    CHECK_NOTHROW(Point(9999.9, -9999.9));
    CHECK_NOTHROW(Point(maximalDouble, minimalDouble));
    // Overflow detector.
    CHECK_THROWS_AS(Point(maximalDouble + epsilon, minimalDouble - epsilon), overflow_error);

    // Characters initialization.
    Character fighter("Hulk", origin, 100);
    CHECK((fighter.getName() == "Hulk"));
    CHECK((fighter.getLocation().getX() == 0));
    CHECK((fighter.getLocation().getY() == 0));
    CHECK((fighter.getHitpoint() == 100));

    // Ninja initialization.
    Ninja ninja("Shang", Point(1, 5));
    CHECK((ninja.getName() == "Shang"));
    CHECK((ninja.getLocation().getX() == 1));
    CHECK((ninja.getLocation().getY() == 5));
    CHECK_NOTHROW(ninja.setVelocity(18));
    CHECK((ninja.getVelocity() == 18));

    // YoungNinja initialization.
    YoungNinja youngNinja("Young", origin);
    CHECK((youngNinja.getVelocity() == 14));
    CHECK((youngNinja.getHitpoint() == 100));
    CHECK((youngNinja.getName() == "Young"));
    CHECK((youngNinja.getLocation().getX() == 0 && youngNinja.getLocation().getY() == 0));

    // TrainedNinja initialization.
    TrainedNinja trainedNinja("Trained", origin);
    CHECK((trainedNinja.getVelocity() == 12));
    CHECK((trainedNinja.getHitpoint() == 120));
    CHECK((trainedNinja.getName() == "Trained"));
    CHECK((trainedNinja.getLocation().getX() == 0 && youngNinja.getLocation().getY() == 0));

    // OldNinja initialization.
    OldNinja oldNinja("Oldie", origin);
    CHECK((oldNinja.getVelocity() == 8));
    CHECK((oldNinja.getHitpoint() == 150));
    CHECK((oldNinja.getName() == "Oldie"));
    CHECK((oldNinja.getLocation().getX() == 0 && youngNinja.getLocation().getY() == 0));

    // Cowboy initialization.
    Cowboy cowboy("Jack Hoxie", Point(999.9, -999.9));
    CHECK((cowboy.getBullets() == 6));
    CHECK((cowboy.getHitpoint() == 110));
    CHECK((cowboy.getName() == "Jack Hoxie"));
    CHECK((cowboy.getLocation().getX() == 999.9 && cowboy.getLocation().getY() == -999.9));

    // Ninjas team initialization.
    Team ninjas(&oldNinja);
    CHECK_THROWS_AS(ninjas.add(&oldNinja), logic_error);
    CHECK_NOTHROW((ninjas.add(&youngNinja)));
    CHECK_NOTHROW((ninjas.add(&trainedNinja)));
    CHECK((ninjas.getCaptain().getName() == oldNinja.getName() && ninjas.getCaptain().getHitpoint() == oldNinja.getHitpoint()));
    CHECK((ninjas.getFighters().size() == 3));

    // Cowboys team initialization.
    Cowboy cowboy1("Texas Jack", origin);
    Team cowboys(&cowboy);
    CHECK_THROWS_AS(cowboys.add(&cowboy), logic_error);
    CHECK_NOTHROW((cowboys.add(&cowboy1)));
    CHECK((cowboys.getCaptain().getName() == cowboy.getName() && cowboys.getCaptain().getHitpoint() == cowboy.getHitpoint()));
    CHECK((cowboys.getFighters().size() == 2));
}

TEST_CASE("Objects Functionality Correctness") {
    Cowboy cowboy("#1 Cowboy", Point(0, 0));
    OldNinja oldNinja("Oldie", Point(0.5, 0.5));

    SUBCASE("Shooting/Slashing Correctness") {
        CHECK_NOTHROW(cowboy.shoot(&oldNinja));
        // Cowboy is NOT farther than 1 meter. Thus, slashing must be done.
        CHECK_NOTHROW(oldNinja.slash(&cowboy));

        // One slash deals 40 damage for the cowboy (110 - 40 = 70).
        // Cowboy shot the ninja once - so he loses one bullet.
        CHECK((cowboy.getBullets() == 5 && cowboy.getHitpoint() == 70));
        // Cowboy shot the ninja once - leading to damage him with 10 hitpoints (150 - 10 = 140).
        CHECK((oldNinja.getHitpoint() == 140));

        // Moving the cowboy farther than 1 meter.
        cowboy.getLocation().setX(-10);
        cowboy.getLocation().setY(-10);
        // Now, the cowboy cannot get slashed by the ninja.
        CHECK_THROWS_AS(oldNinja.slash(&cowboy), logic_error);
    }

    SUBCASE("Checking Cowboy's Reloading & Ninja's Movements") {
        // Cowboy is back to his spawn location.
        cowboy.getLocation().setX(0);
        cowboy.getLocation().setY(0);

        // Shooting the 5 bullets left.
        while (cowboy.hasboolets()) {
            CHECK_NOTHROW(cowboy.shoot(&oldNinja));
        }

        // Making sure that the cowboy has run out of bullets and cannot shoot anymore.
        CHECK((cowboy.getBullets() == 0));
        CHECK_THROWS_AS(cowboy.shoot(&oldNinja), logic_error);
        // The ninja has got shot with another 5 bullets - making him getting damaged by 50 hitpoints.
        CHECK((oldNinja.getHitpoint() == 90));

        // Cowboy reloads his pistol.
        CHECK_NOTHROW(cowboy.reload());
        // Making sure that the pistol is reloaded & attempting to shoot the ninja once after reloading.
        CHECK((cowboy.getBullets() == 6));
        CHECK_NOTHROW(cowboy.shoot(&oldNinja));
        // If so, the ninja's hitpoint must be 80 now.
        CHECK((oldNinja.getHitpoint() == 80));

        // The ninja moves more than 1 meter away from the cowboy.
        CHECK_NOTHROW((oldNinja.move(&cowboy)));
        // The ninja won't be able to slash the cowboy because he is of type "old" and moves "velocity = 8" meters towards the cowboy.
        // Which makes the ninja to pass the cowboy and move farther than 1 meter.
        CHECK_THROWS_AS(oldNinja.slash(&cowboy), logic_error);

        // Moving the ninja to be 7.5 meters away from the cowboy.
        CHECK_NOTHROW(oldNinja.getLocation().setX(7.5));
        CHECK_NOTHROW(oldNinja.getLocation().setY(7.5));
        // Moving the ninja towards the cowboy such that it can be able to slash him.
        CHECK_NOTHROW(oldNinja.move(&cowboy));
        CHECK_NOTHROW(oldNinja.slash(&cowboy));
        // The ninja slashes the cowboy for the second time - damaging him with another 40 hitpoints.
        // 70 - 40 = 30
        CHECK((cowboy.getHitpoint() == 30));
    }
}

TEST_CASE("Light Battle Correctness - Cowboys VS Ninjas & Other Functionalities Correctness") {
    Point ninjasSpawnLocation(-50, -50), cowboysSpawnLocation(0.8, 0.8);

    YoungNinja youngNinja("Youngie", ninjasSpawnLocation);
    TrainedNinja trainedNinja("Trainee", ninjasSpawnLocation);
    OldNinja oldNinja("Oldie", ninjasSpawnLocation);

    Cowboy firstCowboy("Thomas", cowboysSpawnLocation),
            secondCowboy("Williams", cowboysSpawnLocation),
            thirdCowboy("Alex", cowboysSpawnLocation);

    // Assigning captains for both teams.
    Team cowboys(&firstCowboy);
    Team ninjas(&oldNinja);

    SUBCASE("3 VS 3 Battle Setup") {
        // Making sure that the cowboys are ready.
        CHECK_THROWS(cowboys.add(&firstCowboy));
        CHECK_NOTHROW(cowboys.add(&secondCowboy));
        CHECK_NOTHROW(cowboys.add(&thirdCowboy));
        CHECK((cowboys.getFighters().size() == 3 && cowboys.stillAlive() == 3));

        // Making sure that the ninjas are ready.
        CHECK_THROWS(ninjas.add(&oldNinja));
        CHECK_NOTHROW(ninjas.add(&youngNinja));
        CHECK_NOTHROW(ninjas.add(&trainedNinja));
        CHECK((ninjas.getFighters().size() == 3 && ninjas.stillAlive() == 3));
    }

    SUBCASE("Starting 3 VS 3 Battle Using Attack()") {
        // Starting the battle.
        while (cowboys.stillAlive() > 0 && ninjas.stillAlive() > 0) {
            // Captains start the spark.
            CHECK_NOTHROW(firstCowboy.shoot(&oldNinja));
            CHECK_NOTHROW(oldNinja.slash(&firstCowboy));

            CHECK_NOTHROW(cowboys.attack(&ninjas));
            CHECK_NOTHROW(ninjas.attack(&cowboys));
        }
    }

    SUBCASE("Post-Battle Checks") {
        // Checking which team has won and that at least one of their fighters got his hitpoint damaged.
        if (ninjas.stillAlive() > 0) {
            CHECK((cowboys.stillAlive() == 0));
            CHECK((ninjas.getFighters()[0].getHitpoint() != 150 ||
                   ninjas.getFighters()[1].getHitpoint() != 100 ||
                   ninjas.getFighters()[2].getHitpoint() != 120));
        } else if (cowboys.stillAlive() > 0) {
            CHECK((ninjas.stillAlive() == 0));
            CHECK((cowboys.getFighters()[0].getHitpoint() != 110 ||
                   cowboys.getFighters()[1].getHitpoint() != 110 ||
                   cowboys.getFighters()[2].getHitpoint() != 110));
        }
    }
}