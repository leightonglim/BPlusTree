#include <iostream>
#include <random>
#include <ctime>
#include "BtreeNode.h"
#include "SDL_Plotter.h"
#include "rectangle.h"

using namespace std;



int main(int argc, char ** argv) {




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

    Bptree temp(4,g);
    srand(time(NULL));


//

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

        int i = 0;
        if( i < 5) i++;
        temp.insert(i);

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

//        point x1(400,400);
//        point x2(450,425);

//        moveToPosition(r2,x1,x2,g);
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
