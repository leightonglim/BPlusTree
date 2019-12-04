#include "line.h"


line::line(){
    p1.x = 0;
    p1.y = 0;
    p2.x = 1;
    p2.y = 1;
}
line::line(point a ,point b){
    p1 = a;
    p2 = b;
}

void line::draw(ostream& output){
    // print y = mx +b
    // need to find m and b

    bool hasSlope;
    double m,b;

    hasSlope = slope(m);
    if(hasSlope){
        b = y_inter();
        output << "y = " << m << " x + " << b;
    }
    else{
        output << "x = " << p1.x;
    }
}

void line::draw(SDL_Plotter& g){
    double m,b;
    int y;
    if(slope(m)){
        b = y_inter();
        for(double x = min(p1.x, p2.x); x <= max (p1.x,p2.x); x+= 0.0001){
            y = m*x +b;
            g.plotPixel(x,y,c.R,c.G,c.B);
        }
    }
    else{
        for(double y = min(p1.y,p2.y); y <= max(p1.y,p2.y); y+= 0.0001){
            g.plotPixel(p1.x,y,c.R,c.G,c.B);
        }
    }
}

bool line::slope(double& m){
    bool flag;
    flag = p1.x != p2.x;

    if(flag){
        m = static_cast<double>(p1.y-p2.y)/(p1.x-p2.x);
    }

    return flag;
}


double line::y_inter(){
    double m;
    slope(m);
    return p1.y - m * p1.x;
}


point line::getP1(){
    return p1;
}
point line::getP2(){
    return p2;
}
color line::getColor(){
    return c;
}

void line::setP1(point p){
    p1 = p;
}
void line::setP2(point p ){
    p2 = p;
}
void line::setColor(color a){
    c = a;
}




