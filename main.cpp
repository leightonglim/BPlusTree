#include <iostream>
#include <random>
#include <ctime>
#include "BtreeNode.h"
#include "SDL_Plotter.h"
#include "rectangle.h"

using namespace std;


void moveToPosition(rectangle& ,point&, point&,SDL_Plotter&);
int main(int argc, char ** argv) {
//    Bptree temp(4);
//
//    srand(time(NULL));
//    for(int i = 20; i > 0; i--){
//         temp.insert(rand()%100);
//    }
//
//    temp.levelOrder(cout);
//
//    SDL_Plotter g(1000,1000,true);
//    bool stopped = false;
//    bool colored = false;
//    int x,y, xd, yd;
//    int R,G,B;
//    rectangle r1;
//    while (!g.getQuit())
//    {
//        if(!stopped){
//            x = rand()%g.getCol();
//            y = rand()%g.getRow();
//            R = rand()%256;
//            G = rand()%256;
//            B = rand()%256;
//            for(xd = 0; xd < 10 && x + xd < g.getCol(); xd++ ){
//                for(yd = 0; yd < 10 && y + yd < g.getRow(); yd++ ){
//                    if(colored){
//                        g.plotPixel( x + xd, y + yd, R, G, B);
//                    }
//                    else{
//                        g.plotPixel( x + xd, y + yd, 0, G, 0);
//                    }
//                }
//            }
//            r1.draw(g);
//
//            point x2 = r1.getP2();
//            x2.y++;
//
//            r1.setP2(x2);
//
//        }
//
//        if(g.kbhit()){
//            g.getKey();
//        }
//
//        if(g.getMouseClick(x,y)){
//            stopped = !stopped;
//        }
//
//        g.update();
//    }
    SDL_Plotter g(1000,1000, true);
    color newColor;
    rectangle r2(point(0,0),point(50,25),RED);

    char key;
    //int size = 200;
    int x = 500;
    int y = 500;

    //int count = 0;

    //line lineOne(point(100,25),point(101,300)), lineTwo(point(0,0),point(499,499));
    //lineOne.setColor(RED);

    //lineOne.draw(cout);
    //cout << endl;
    //lineTwo.draw(cout);
    //cout << endl;

    while(!g.getQuit()){
        if(g.kbhit()){
            key = g.getKey();
            g.clear();
        }
//        switch(key){
//            case RIGHT_ARROW:  r1.move(RIGHT);
//                break;
//            case LEFT_ARROW:   r1.move(LEFT);
//                break;
//            case UP_ARROW:     r1.move(UP);
//                if(y < 10){
//                    y = 10;
//                }
//                break;
//            case DOWN_ARROW:   r1.move(DOWN);
//                if(y > 500){
//                    y = 500;
//                }
//                break;
//        }

        point x1(400,400);
        point x2(450,425);

        moveToPosition(r2,x1,x2,g);
        //newColor.R = rand()%255;
        //newColor.G = rand()%255;
        //newColor.B = rand()%255;
        //lineOne.setColor(newColor);

        //if(count > 1000){
        //    lineOne.setP1(point(rand()%500,rand()%500));
        //    count = 0;
        //}
        //lineOne.setP2(point(rand()%500,rand()%500));
        //lineOne.draw(g);
        //count++;
        //r1.setColor(newColor);
        //r2.setColor(newColor);

        //r1.setP1(point(rand()%200,rand()%200));
        //r1.setP2(point(r1.getP1().x +rand()%300 , r1.getP1().y + rand()%300));

        //r1.draw(g);
        //r2.draw(g);

        //for(int row = y; row <= y+size; row ++){
        //    for(int col = x; col <=x+size; col ++){
        //        g.plotPixel(col, row, 200, 30, 30);
        //    }
        //}
        g.update();
        //g.Sleep(delay--);
        g.clear();

    }


    return 0;
}
void moveToPosition(rectangle& a, point& p1,point& p2,SDL_Plotter& g){
    unsigned int DELAY = 5;

    while(a.getP1().y != p1.y ){
        if(p1.y > a.getP1().y){
            a.move(DOWN);
        }else{
            a.move(UP);
        }
        a.draw(g);
        g.update();
        a.erase(g);
        g.Sleep(DELAY);
    }


    while(a.getP1().x != p1.x){
        if(p1.x > a.getP1().x){
            a.move(RIGHT);
        }else{
            a.move(LEFT);
        }
        a.draw(g);
        g.update();
        a.erase(g);
        g.Sleep(DELAY);
    }


    a.draw(g);





}