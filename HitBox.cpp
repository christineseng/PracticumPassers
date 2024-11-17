
#include "HitBox.h"
bool HitBox::isHit(HitBox h1, HitBox h2){
    // bool result = false;
    // int h1Top = h1.getPoint().y - h1.getWidth()/2;
    // int h1Bottom = h1.getPoint().y + h1.getWidth()/2;
    // int h1Left = h1.getPoint().x - h1.getLength()/2;
    // int h1Right = h1.getPoint().x + h1.getLength()/2;

    // int h2Top = h2.getPoint().y - h2.getWidth()/2;
    // int h2Bottom = h2.getPoint().y + h2.getWidth()/2;
    // int h2Left = h2.getPoint().x - h2.getLength()/2;
    // int h2Right = h2.getPoint().x + h2.getLength()/2;

    // if (h1Bottom >= h2Top && h2Right >= h1Left){result = true;}
    // else if (h1Top <= h2Bottom && h2Right >= h1Left){result = true;}
    // else if (h2Bottom >= h1Top && h1Right >= h2Left){result = true;}
    // else if (h1Bottom >= h2Top && h1Right >= h2Left){result = true;}

    // return result;

    bool result;
    int xDist = fabs(h1.getPoint().x - h2.getPoint().x);
    int yDist = fabs(h1.getPoint().y - h2.getPoint().y);
    int xBoundary = h1.getLength() / 2 + h2.getLength() / 2;
    int yBoundary = h1.getWidth() / 2 + h2.getWidth() / 2;
    result = (xDist < xBoundary) && (yDist < yBoundary);

    return result;
}
