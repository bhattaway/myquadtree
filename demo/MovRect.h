#ifndef MOVRECT_H
#define MOVRECT_H

#include "test0.h"

class MovRect{
public:
	MovRect()
		: dx_(0), dy_(0), isAlive_(true)
    {
    }
    MovRect(Rect rect, int dx = 0, int dy = 0)
        : rect_(rect), dx_(dx), dy_(dy), isAlive_(true)
    {
    }
 
    void set_isAlive(bool b){
        isAlive_ = b;
    }
    bool get_isAlive(){
        return isAlive_;
    }
    void set_dy(int newdy){
        dy_ = newdy;
    }
    int get_dy(){
        return dy_;
    }
    void set_dx(int newdx){
        dx_ = newdx;
    }
    int get_dx(){
        return dx_;
    }
    void set_rect(const Rect & newrect){
        rect_ = newrect;
    }

	Rect get_rect(){
        return rect_;
    }
    void move(){
        //only move if rect is alive
        if(isAlive_){
            rect_.x += dx_;
            rect_.y += dy_;

            if(rect_.x < 0){
                rect_.x = 0;
                dx_ = -dx_;
            }
            if(rect_.x > W_RES - rect_.w){
                rect_.x = W_RES - rect_.w;
                dx_ = -dx_;
            }
            if(rect_.y < 0){
                rect_.y = 0;
                dy_ = -dy_;
            }
            if(rect_.y > H_RES - rect_.h){
                rect_.y = H_RES - rect_.h;
                dy_ = -dy_;
            }

            /*
            ++rect_.c.r;
            ++rect_.c.g;
            ++rect_.c.b;
            */
        }
    }

//private:
	Rect rect_;
	int dx_;
	int dy_;
	bool isAlive_;
};

#endif
