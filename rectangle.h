/*
    Author: Matthew Sun, Nilei Pan, Tianyi Zhang, Runze Li, Maiqi Hou
    Assignment Title: Mario Brazazu
    Assignment Description: creating a playable Mario like game
    Due Date: 12/3/2018
    Date Created: 11/20/2018
    Date Last Modified: 12/3/2018

*/
/*
    Data Abstraction:
                Some variables and functions are set to be used
    Input:
                The user makes the input
    Process:
                The program responds to the input by the user and
                moves the Mario
    Output:
                The Mario and the game board are drawn to the screen
    Assumptions:
                Assumes that user only controls one Mario object
                Assumes that there are only two turtles needed
*/
#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

#include "point.h"
#include "color.h"
#include "SDL_Plotter.h"

class rectangle {
    private:
        point p1, p2;
        color c;

    public:
        /*
         * description: default constructor
         * return: no return
         * precondition: no
         * postcondition: sets the variables to default
         *
        */
        rectangle();
        /*
         * description: default constructor
         * return: no return
         * precondition: two points and a color exists
         * postcondition: sets the variables to the input
         *
        */
        rectangle(point a, point b, color = BLACK);

        /*
         * description: getting the value of p1
         * return: point
         * precondition: no
         * postcondition: the value of p1 is extracted and returned
         *
        */
        point getP1();
        /*
         * description: getting the value of p2
         * return: point
         * precondition: no
         * postcondition: the value of p2 is extracted and returned
         *
        */
        point getP2();
        /*
         * description: getting the color
         * return: color
         * precondition: no
         * postcondition: the color is extracted and returned
         *
        */
        color getColor();

        /*
         * description: setting the value of p1
         * return: no return
         * precondition: a point exists
         * postcondition: the value of p1 is set
         *
        */
        void setP1(point p);
        /*
         * description: setting the value of p2
         * return: no return
         * precondition: a point exists
         * postcondition: the value of p2 is set
         *
        */
        void setP2(point p);
         /*
         * description: setting the color
         * return: no return
         * precondition: a color exists
         * postcondition: the color is set
         *
        */
        void setColor(color a);

        /*
         * description: drawing the rectangle
         * return: no return
         * precondition: SDL plotter
         * postcondition: the rectangle is drawn on screen
         *
        */
        void draw(SDL_Plotter& g);
};

#endif // RECTANGLE_H_INCLUDED
