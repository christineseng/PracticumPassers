
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
