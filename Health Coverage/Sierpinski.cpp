/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "simpio.h"
#include "gmath.h"
#include "gobjects.h"


using namespace std;


void drawTriangle(GWindow& gWind, GPoint point1, GPoint point2, GPoint point3, int order);
GPoint nextPoints(GWindow& gWind, GPoint start, int edgeSize, double angle);
GPoint midpoint(const GPoint& point1, const GPoint& point2);



int main() {
    // [TODO: fill with your code]
    GWindow gWind;
    //inputs
    int order = getInteger("input order: ");
    int edgeSize = getInteger("input size of edge: ");
    // this is to generate our biggest triangle's points. 
    GPoint point1 (gWind.getWidth()/2 - edgeSize/2, gWind.getHeight()/2+(sqrt(3)/2)*edgeSize/2);
    GPoint point2 = nextPoints(gWind,point1, edgeSize, 0);
    GPoint point3 = nextPoints( gWind,point2, edgeSize, 120);
    gWind.drawPolarLine(point3, edgeSize, 240);
    // and this is our main recursive method.
    drawTriangle(gWind, point1, point2,point3, order);

    return 0;
}
// this method is responsible for returning end of the polar line.
GPoint nextPoints(GWindow& gWind, GPoint start, int edgeSize, double angle) {
    return gWind.drawPolarLine(start, edgeSize, angle);
}
// just as we use this formula  in maths, we can use this formula to calculate midpoint between two points.
GPoint midpoint(const GPoint& point1, const GPoint& point2) {
    return GPoint((point1.getX() + point2.getX()) / 2.0, (point1.getY() + point2.getY()) / 2.0);

}
// this method is our recursive method and it draws inner smaller triangles.
void drawTriangle(GWindow& gWind, GPoint point1, GPoint point2, GPoint point3, int order) {
    // if our order reaches 0 then return
    if (order == 0) {
        return;
    } 
    // this is responsible for drawing edges.
    gWind.drawLine(point1, point2);
    gWind.drawLine(point2, point3);
    gWind.drawLine(point3, point1);

    // generates our midpoints.
    GPoint midpoint31 = midpoint(point3, point1);
    GPoint midpoint12 = midpoint(point1, point2);
    GPoint midpoint23 = midpoint(point2, point3);
    
    // and lastly we use recursion to generate 3 smaller triangles.
    drawTriangle(gWind, point1, midpoint12, midpoint31, order - 1);
    drawTriangle(gWind, midpoint12, point2, midpoint23, order - 1);
    drawTriangle(gWind, midpoint31, midpoint23, point3, order - 1);

}