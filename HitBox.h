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
        //CONSTRUCTORS
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

        //SETTER METHODS
        //************************************************************
        // description: sets hitbox point to point parameter
        // return: void
        // pre: loc is a valid point on the screen
        // post: hitbox point changed to point parameter
        //************************************************************
        void setPoint(point loc){
            location = loc;
        }
        //************************************************************
        // description: sets hitbox length to int l
        // return: void
        // pre: l is non-negative int
        // post: hitbox length changed to parameter
        //************************************************************
        void setLength(int l){
            length = l;
        }
        //************************************************************
        // description: sets hitbox width to int w
        // return: void
        // pre: w is non-negative int
        // post: hitbox width changed to parameter
        //************************************************************
        void setWidth(int w){
            width = w;
        }

        //GETTER METHODS
        //************************************************************
        // description: returns hitbox point
        // return: point
        // pre: location initialized
        // post: hitbox remains unchanged
        //************************************************************
        point getPoint()const{
            return location;
        }
        //************************************************************
        // description: returns hitbox length
        // return: int
        // pre: length initialized
        // post: hitbox remains unchanged
        //************************************************************
        int getLength()const{
            return length;
        }
        //************************************************************
        // description: returns hitbox width
        // return: int
        // pre: width initialized
        // post: hitbox remains unchanged
        //************************************************************
        int getWidth()const{
            return width;
        }

        //METHODS
        //************************************************************
        // description: returns bool if two hitbox parameters are hit
        // return: bool 
        // pre: both hitboxes initialized
        // post: hitboxex remains unchanged
        //************************************************************
        static bool isHit(HitBox h1, HitBox h2);

};

#endif
