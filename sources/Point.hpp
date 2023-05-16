/**
 * This class represents a location of X & Y coordinates for the fighters.
 *
 * @author Osama M. Ghaliah
 */

#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace ariel {
    class Point {
        private:
            double x, y;

        public:
            // Constructors.
            Point();
            Point(double x, double y);

            // Essential methods for the fighters.
            double distance(Point other);
            void print();
            Point moveTowards(Point source, Point destination, double distance);

            // Getters & setters.
            double getX();
            void setX(double x);
            double getY();
            void setY(double y);
    };
};

#endif
