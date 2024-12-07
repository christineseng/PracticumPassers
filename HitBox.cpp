/*
* Authors: Christine Seng, Erick Martinez, Georgia Rushing, Graham Balas, Nolan Schirripa
* Assignment Title:  Group Project (HitBox.cpp)
* Assignment Description: defines HitBox class that makes an invisible box around a block and detects collisions
* Due Date: 12/09/2024
* Date Created: 10/25/2024
* Date Last Modified: 12/07/2024
*/

#include "HitBox.h"
bool HitBox::isHit(HitBox h1, HitBox h2){
    bool result;
    int xDist = fabs(h1.getPoint().x - h2.getPoint().x);
    int yDist = fabs(h1.getPoint().y - h2.getPoint().y);
    int xBoundary = h1.getLength() / 2 + h2.getLength() / 2;
    int yBoundary = h1.getWidth() / 2 + h2.getWidth() / 2;
    result = (xDist < xBoundary) && (yDist < yBoundary);

    return result;
}
