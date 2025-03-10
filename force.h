/*
* Author: Nolan Schirripa, Christine Seng, Erick Martinez, Georgia Rushing, Graham Balas
* Assignment Title:  Group Project (force.h)
* Assignment Description: declares force class that adds and sets forces to ball
* Due Date: 12/09/2024
* Date Created: 10/25/2024
* Date Last Modified: 12/07/2024
*/

#ifndef FORCE_H
#define FORCE_H
#include <cmath>
#include <ostream>

class force{
private:
    double magnitude;
    double direction;  // radian

public:
    force();
    force(double m, double d);

    void setMagnitude(double m);
    void setDirection(double d);
    double getMagnitude()const;
    double getDirection()const;

    force operator+(const force& other) const;
    force operator=(const force& other);
    force add(const force& other) const;
    void apply(const force& other);

    void display(std::ostream& os)const{
        os << getMagnitude() << " " << getDirection() << std::endl;
    }
};

#endif //FORCE_H
