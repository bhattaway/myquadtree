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
					//*
					int dummy = recta[i].dx_;
					recta[i].dx_ = -recta[j].dy_;
					recta[j].dy_ = -dummy;

					dummy = recta[i].dy_;
					recta[i].dy_ = -recta[j].dx_;
					recta[j].dx_ = -dummy;

					recta[i].rect_.c.r = rand() % 200 + 55;
					recta[i].rect_.c.g = rand() % 200 + 55;
					recta[i].rect_.c.b = rand() % 200 + 55;
					
					recta[j].rect_.c.r = rand() % 200 + 55;
					recta[j].rect_.c.g = rand() % 200 + 55;
					recta[j].rect_.c.b = rand() % 200 + 55;
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
					//*
					int dummy = data[i]->dx_;
					data[i]->dx_ = -data[j]->dy_;
					data[j]->dy_ = -dummy;

					dummy = data[i]->dy_;
					data[i]->dy_ = -data[j]->dx_;
					data[j]->dx_ = -dummy;

					/*
					data[i]->dx_ = -data[i]->dx_;
					data[i]->dy_ = -data[i]->dy_;

					data[j]->dx_ = -data[j]->dx_;
					data[j]->dy_ = -data[j]->dy_;
					*/
					//*/
					///*
					data[i]->rect_.c.r = rand() % 200 + 55;
					data[i]->rect_.c.g = rand() % 200 + 55;
					data[i]->rect_.c.b = rand() % 200 + 55;
					
					data[j]->rect_.c.r = rand() % 200 + 55;
					data[j]->rect_.c.g = rand() % 200 + 55;
					data[j]->rect_.c.b = rand() % 200 + 55;
					//*/
				}
			}
		}
	}
}

void bruteforcecollision(std::vector< MovRect * > & data0, std::vector< MovRect * > & data1){
	for(int i = 0; i < data0.size(); ++i){
		if(data0[i]->get_isAlive()){
			for(int j = 0; j < data1.size(); ++j){
				if(data1[j]->get_isAlive()
					&& ((data0[i]->rect_.x >= data1[j]->rect_.x
					&& data0[i]->rect_.x <= data1[j]->rect_.x + data1[j]->rect_.w)
					|| (data1[j]->rect_.x >= data0[i]->rect_.x
					&& data1[j]->rect_.x <= data0[i]->rect_.x + data0[i]->rect_.w))
					&&
					((data0[i]->rect_.y >= data1[j]->rect_.y
					&& data0[i]->rect_.y <= data1[j]->rect_.y + data1[j]->rect_.h)
					|| (data1[j]->rect_.y >= data0[i]->rect_.y
					&& data1[j]->rect_.y <= data0[i]->rect_.y + data0[i]->rect_.h)))
				{
					//data[i]->set_isAlive(false);
					//data1[j]->set_isAlive(false);
					///*
					data0[i]->dx_ = -data0[i]->dx_;
					data0[i]->dy_ = -data0[i]->dy_;

					data1[j]->dx_ = -data1[j]->dx_;
					data1[j]->dy_ = -data1[j]->dy_;
					//*/
					data0[i]->rect_.c.r = 255;
					data0[i]->rect_.c.g = 255;
					data0[i]->rect_.c.b = 255;
					
					data1[j]->rect_.c.r = 255;
					data1[j]->rect_.c.g = 255;
					data1[j]->rect_.c.b = 255;
				}
			}
		}
	}
}
