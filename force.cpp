/*
* Author: Nolan Schirripa, Christine Seng, Erick Martinez, Georgia Rushing, Graham Balas
* Assignment Title:  Group Project (force.cpp)
* Assignment Description: defines force class that adds and sets force to ball
* Due Date: 12/09/2024
* Date Created: 10/25/2024
* Date Last Modified: 12/07/2024
*/
#include "force.h"

force::force(){
    magnitude = 0;
    direction = 0;
}

force::force(double m, double d){
    magnitude = m;
    direction = d;
}

force force::operator+(const force& other) const{
    return add(other);
}

void force::apply(const force& other){
    *this = add(other);
}


force force::add(const force& other) const{
    force v;
    double ax, ay;
    double bx, by;
    double theta, mag;

    ax = magnitude * cos(direction);
    bx = other.magnitude * cos(other.direction);

    ay = magnitude * sin(direction);
    by = other.magnitude * sin(other.direction);

    theta = atan((ay+by)/(ax+bx));
    if((ay+by) < 0 && theta > 0) theta += M_PI;
    if((ay+by) > 0 && theta < 0) theta += M_PI;

    mag   = sqrt(pow(ax + bx, 2) + pow(ay + by, 2));

    v.magnitude = mag;
    v.setDirection(theta);
    return v;
}

void force::setMagnitude(double m){
    magnitude = m;
}
void force::setDirection(double d){
    while(d > 2*M_PI ) d -= 2*M_PI;
    while(d < 0) d += 2*M_PI;
    direction = d;
}

double force::getMagnitude()const{
    return magnitude;
}

double force::getDirection()const{
    return direction;
}

force force::operator=(const force& other){
    setMagnitude(other.magnitude);
    setDirection(other.direction);
    return *this;
}
