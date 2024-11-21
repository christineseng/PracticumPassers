#ifndef hitbox_h
#define hitbox_h

#include "SDL_Plotter.h"
#include <cmath>
class HitBox{
    private:
        point location;
        int length;
        int width;
    public:
        HitBox(){
            location.x = 0;
            location.y = 0;
            length = 0;
            width = 0;
        }
        HitBox(point loc, int l = 0, int w = 0){
            location = loc;
            length = l;
            width = w;
        }
        void setPoint(point loc){
            location = loc;
        }
        void setLength(int l){
            length = l;
        }
        void setWidth(int w){
            width = w;
        }
        point getPoint()const{
            return location;
        }
        int getLength()const{
            return length;
        }
        int getWidth()const{
            return width;
        }


        static bool isHit(HitBox h1, HitBox h2);

};
#endif
