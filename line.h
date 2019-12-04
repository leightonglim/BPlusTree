#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include "point.h"
#include <ostream>
#include "SDL_Plotter.h"
#include "color.h"

using namespace std;
class line{
    private:
        point p1, p2;
        bool slope(double&);
        double y_inter();
        color c;

    public:
        line();
        line(point,point);
        point getP1();
        point getP2();
        color getColor();

        void setP1(point);
        void setP2(point);
        void setColor(color);

        void draw(ostream&);
        void draw(SDL_Plotter&);

};

#endif // LINE_H_INCLUDED
