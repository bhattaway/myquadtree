#include "bruteforcecollision.h"

void bruteforcecollision(MovRect * recta, const int num_rects){
	for(int i = 0; i < num_rects; ++i){
		if(recta[i].get_isAlive()){
			for(int j = i + 1; j < num_rects; ++j){
				if(recta[j].get_isAlive()
					&& ((recta[i].rect_.x >= recta[j].rect_.x
					&& recta[i].rect_.x <= recta[j].rect_.x + recta[j].rect_.w)
					|| (recta[j].rect_.x >= recta[i].rect_.x
					&& recta[j].rect_.x <= recta[i].rect_.x + recta[i].rect_.w))
					&&
					((recta[i].rect_.y >= recta[j].rect_.y
					&& recta[i].rect_.y <= recta[j].rect_.y + recta[j].rect_.h)
					|| (recta[j].rect_.y >= recta[i].rect_.y
					&& recta[j].rect_.y <= recta[i].rect_.y + recta[i].rect_.h)))
				{
					recta[i].set_isAlive(false);
					recta[j].set_isAlive(false);
				}
			}
		}
	}
}
