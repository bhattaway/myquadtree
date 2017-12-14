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
					//recta[i].set_isAlive(false);
					//recta[j].set_isAlive(false);
				}
			}
		}
	}
}

void bruteforcecollision(std::vector< MovRect * > & data){
	for(int i = 0; i < data.size(); ++i){
		if(data[i]->get_isAlive()){
			for(int j = i + 1; j < data.size(); ++j){
				if(data[j]->get_isAlive()
					&& ((data[i]->rect_.x >= data[j]->rect_.x
					&& data[i]->rect_.x <= data[j]->rect_.x + data[j]->rect_.w)
					|| (data[j]->rect_.x >= data[i]->rect_.x
					&& data[j]->rect_.x <= data[i]->rect_.x + data[i]->rect_.w))
					&&
					((data[i]->rect_.y >= data[j]->rect_.y
					&& data[i]->rect_.y <= data[j]->rect_.y + data[j]->rect_.h)
					|| (data[j]->rect_.y >= data[i]->rect_.y
					&& data[j]->rect_.y <= data[i]->rect_.y + data[i]->rect_.h)))
				{
					//data[i]->set_isAlive(false);
					//data[j]->set_isAlive(false);
				}
			}
		}
	}
}

void bruteforcecollision(std::vector< MovRect * > & mydata, std::vector< MovRect * > & parentdata){
}
