#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <cmath>
using namespace std;
struct point{
    int x,y;

    point(){
        x = 0;
        y = 0;
    }

    point(int a, int b){
        x = a;
        y = b;
    }


    double distance(point p){
        return sqrt(pow(x-p.x,2.0) + pow(y-p.y,2.0));
    }
};

#endif // POINT_H_INCLUDED
