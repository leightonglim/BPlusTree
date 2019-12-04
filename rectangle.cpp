
#include "rectangle.h"

rectangle::rectangle() {
    p1.x = 0;
    p1.y = 0;

    p2.x = 50;
    p2.y = 25;

    c = BLACK;
}

rectangle::rectangle(point a, point b, color clr) {
    p1 = a;
    p2 = b;
    c = clr;
}

point rectangle::getP1() {
    return p1;
}

point rectangle::getP2() {
    return p2;
}

color rectangle::getColor() {
    return c;
}

void rectangle::setP1(point p) {
    p1 = p;
}

void rectangle::setP2(point p) {
    p2 = p;
}

void rectangle::setColor(color a) {
    c = a;
}



void rectangle::draw(SDL_Plotter& g) {
    for (double x = p1.x; x <= p2.x; x++) {
        for (double y = p1.y; y <= p2.y; y++) {
            g.plotPixel(x,y,c.R,c.G,c.B);
        }
    }
}


void rectangle::erase(SDL_Plotter& g){
    for (double x = p1.x; x <= p2.x; x++) {
        for (double y = p1.y; y <= p2.y; y++) {
            g.plotPixel(x,y,255,255,255);
        }
    }
}

void rectangle::move(DIRECTION x) {
    switch(x){
        case RIGHT : p1.x++;
                     p2.x++;
            break;
        case LEFT : p1.x--;
                    p2.x--;
            break;
        case UP :
            if(p1.y > 10){
                p1.y--;
                p2.y--;
            }

            break;
        case DOWN:
            if(p1.y < 1000){
                p1.y++;
                p2.y++;
            }
            break;
        default: break;
    }
}