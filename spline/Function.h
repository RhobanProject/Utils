#pragma once

#include <vector>
#include <map>
#include <string>

#ifndef FUNCTION_DEFAULT_POINTS
#define FUNCTION_DEFAULT_POINTS 16
#endif

class Function
{
    public:
        Function();

        /**
         * Add a point (x, y) to the function
         */
        void addPoint(double x, double y);

        /**
         * Gets the xMax of the function
         */
        double getXMax();

        /**
         * Get the value for the given x
         */
        double get(double x);

        /**
         * Gets the value for the given x, modulo the size of the function
         */
        double getMod(double x);

        /**
         * Checks if the function can contain one more element
         */
        void checkSize();

        /**
         * Clear the spline
         */
        void clear();

        /**
         * Load a JSON file
         */
        static std::map<std::string, Function> fromFile(std::string filename);

    protected:
        /**
         * Function points
         */
        std::vector<double> points;

        /**
         * The nth item of this array is the slope between the nth point and the
         * n+1th point
         */
        std::vector<double> ds;

        /**
         * Number of points
         */
        int nbPoints;
};
