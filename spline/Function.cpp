#include <cstdlib>
#include <cstdio>
#include "Function.h"

#define POINT_X(n) points[2*(n)]
#define POINT_Y(n) points[2*(n)+1]

Function::Function() : nbPoints(0)
{
    size = FUNCTION_DEFAULT_POINTS;
    points = (double *)malloc(2*size*sizeof(double));
    ds = (double *)malloc(size*sizeof(double));
}

Function::~Function()
{
    free(points);
    free(ds);
}
        
void Function::checkSize()
{
    if (nbPoints+1 >= size) {
        size *= 2;
        points = (double *)realloc(points, 2*size*sizeof(double));
        ds = (double *)realloc(ds, size*sizeof(double));
    }
}

void Function::clear()
{
    nbPoints = 0;
}

double Function::getXMax()
{
    if (nbPoints == 0) {
        return 0.0;
    }

    return POINT_X(nbPoints-1);
}

void Function::addPoint(double x, double y)
{
    checkSize();

    POINT_X(nbPoints) = x;
    POINT_Y(nbPoints) = y;

    if (nbPoints > 0) {
        ds[nbPoints-1] = POINT_Y(nbPoints) - POINT_Y(nbPoints-1);
        ds[nbPoints-1] /= POINT_X(nbPoints) - POINT_X(nbPoints-1);
    }

    nbPoints++;
}

double Function::get(double x)
{
    int i;
    
    for (i=0; i<nbPoints; i++) {
        if (POINT_X(i) >= x) {
            break;
        }
    }

    if (i == 0 || i == nbPoints) {
        return 0.0;
    }

    return POINT_Y(i-1)+ds[i-1]*(x-POINT_X(i-1));
}

double Function::getMod(double x)
{
    double maxX = getXMax();

    if (x < 0.0 || x > maxX) {
        x -= maxX*(int)(x/maxX);
    }
    
    return get(x);
}


#undef POINT_X
#undef POINT_Y
