#pragma once

#include <vector>
#include <algorithm>

/**
 * PolySpline
 *
 * Splines primitive based on third order polynoms
 * for smooth and differentiablie adjunction
 */
class PolySpline
{
    public:

        struct Point {
            double position;
            double value;
            double delta;
        };
        
        typedef std::vector<Point> Points;

        /**
         * Add a point with its x position, y value and 
         * its derivative slope
         */
        void addPoint(double pos, double val, double delta);

        void clear();

        /**
         * Return the spline interpolation 
         * for given x position
         */
        double get(double x) const;

        /**
         * Return the spline interpolation value
         * with x bound between 0 and 1
         */
        double getMod(double x) const;
        
        /**
         * Access to internal Points container
         */
        const Points& points() const;

    private:
        struct Polynom {
            double a;
            double b;
            double c;
            double d;
        };

        struct Spline {
            Polynom poly;
            double min;
            double max;
        };
        
        typedef std::vector<Spline> Splines;
        
        /**
         * Spline Points container
         */
        Points _points;

        /**
         * Splines container
         */
        Splines _splines;

        /**
         * Fast exponentation to compute 
         * given polynom value
         */
        static double polynomValue(
            double t, const Polynom& p);

        /**
         * Fit a polynom between 0 and 1 with
         * given value and slope
         */
        static Polynom polynomFit(
            double val1, double delta1, 
            double val2, double delta2);

        /**
         * Recompute splines interpolation model
         */
        void computeSplines();
};
