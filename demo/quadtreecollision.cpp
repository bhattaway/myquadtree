#include "quadtreecollision.h"

int QTNode::threshold_ = 20;

void quadtreecollision(MovRect * recta, const int num_rects){
}

QTNode::QTNode(int minx, int maxx, int miny, int maxy)
	: minx_(minx), maxx_(maxx), miny_(miny), maxy_(maxy)
	{
		for(int i = 0; i < 4; ++i){
			children_[i] = NULL;
		}
	}

bool QTNode::has_children() const{
	//child 0 does not exist, therefore no children exist
	if(children_[0] == NULL){
		return false;
	}
	else{
		return true;
	}
}

void QTNode::insert(QTNode * proot, MovRect * mr){
	if(has_children()){
		bool was_inserted = false;

		for(int i = 0; i < 4 && !was_inserted; ++i){
			if((mr->rect_.x >= children_[i]->minx_
				&& mr->rect_.x + mr->rect_.w <= children_[i]->maxx_)
				&&
				(mr->rect_.y >= children_[i]->miny_
				&& mr->rect_.y + mr->rect_.h <= children_[i]->maxy_)){
				was_inserted = true;
				insert(children_[i], mr);
			}
		}

		if(!was_inserted){
			data_.push_back(mr);
		}
	}
	else{
		data_.push_back(mr);
		if(data_.size() >= threshold_){
			/********
			DIVIDING CHILDREN INTO 4 AREAS
				 |
			  0  |  1
			     |  
			-----------
				 |
			  2  |  3
			     |  

			********/
			children_[0] = new QTNode(minx_, maxx_ / 2, miny_, maxy_ / 2);
			children_[1] = new QTNode(maxx_ / 2 + 1, maxx_, miny_, maxy_ / 2);
			children_[2] = new QTNode(minx_, maxx_ / 2, maxy_ / 2 + 1, maxy_);
			children_[3] = new QTNode(maxx_ / 2 + 1, maxx_, maxy_ / 2 + 1, maxy_);
			int current_data_size = data_.size();
			for(int i = 0; i < current_data_size; ++i){
				insert(proot, data_[i]);
			}
			data_.erase(data_.begin(), data_.begin() + current_data_size);
		}
	}
}
