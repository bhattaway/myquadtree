#include "quadtreecollision.h"
#include "bruteforcecollision.h"

int QuadTree::threshold_ = 4;
int QuadTree::max_depth_ = 6;

QTNode::QTNode(QTNode * parent, int minx, int maxx, int miny, int maxy)
	: parent_(parent), minx_(minx), maxx_(maxx), miny_(miny), maxy_(maxy)
	{
		for(int i = 0; i < 4; ++i){
			children_[i] = NULL;
		}
	}

bool QTNode::has_children() const{
	//child 0 does not exist, therefore no children exist
	return (children_[0] != NULL);
}
void QTNode::make_children(){
	/****
	DIVIDING CHILDREN INTO 4 AREAS
		 |
	  0  |  1
		 |  
	-----------
		 |
	  2  |  3
		 |  
	 ****/
	children_[0] = new QTNode(this, minx_, minx_ + (maxx_ - minx_) / 2, miny_, (maxy_ - miny_) / 2);
	children_[1] = new QTNode(this, minx_ + (maxx_ - minx_) / 2 + 1, maxx_, miny_, miny_ + (maxy_ - miny_) / 2);
	children_[2] = new QTNode(this, minx_, minx_ + (maxx_ - minx_) / 2, miny_ + (maxy_ - miny_) / 2 + 1, maxy_);
	children_[3] = new QTNode(this, minx_ + (maxx_ - minx_) / 2 + 1, maxx_, miny_ + (maxy_ - miny_) / 2 + 1, maxy_);
}

bool QTNode::has_parent() const{
	return (parent_ != NULL);
}


/*
void QTNode::insert(MovRect * mr){
	//std::cout << " in insert... ";
	if(has_children()){
		std::cout << " child! ";
		int q;
		std::cin >> q;
		bool was_inserted = false;

		for(int i = 0; i < 4; ++i){
			if((mr->rect_.x >= children_[i]->minx_
				&& mr->rect_.x + mr->rect_.w <= children_[i]->maxx_)
				&&
				(mr->rect_.y >= children_[i]->miny_
				&& mr->rect_.y + mr->rect_.h <= children_[i]->maxy_)){

				was_inserted = true;
				children_[i]->insert(mr);
				break;
			}
		}

		if(!was_inserted){
			data_.push_back(mr);
		}
	}
	else{
		std::cout << " NO child! ";
		data_.push_back(mr);
		if(data_.size() >= threshold_){
			DIVIDING CHILDREN INTO 4 AREAS
				 |
			  0  |  1
			     |  
			-----------
				 |
			  2  |  3
			     |  

			children_[0] = new QTNode(minx_, maxx_ / 2, miny_, maxy_ / 2);
			children_[1] = new QTNode(maxx_ / 2 + 1, maxx_, miny_, maxy_ / 2);
			children_[2] = new QTNode(minx_, maxx_ / 2, maxy_ / 2 + 1, maxy_);
			children_[3] = new QTNode(maxx_ / 2 + 1, maxx_, maxy_ / 2 + 1, maxy_);
			int current_data_size = data_.size();
			for(int i = 0; i < current_data_size; ++i){
				insert(data_[0]);
				//data_.erase(data_.begin());
			}
			//data_.erase(data_.begin(), data_.begin() + current_data_size);
		}
	}
}
*/


QuadTree::QuadTree(QTNode * proot)
	: proot_(proot)
{
}

/*
QuadTree::~QuadTree(){
	recursive_del(proot_);
}
void QuadTree::recursive_del(QTNode * node){
	if(node == NULL){
	}
	else{
		for(int i = 0; i < 4; ++i){
			recursive_del(node->children_[i]);
		}
		delete node;
	}
}
*/

void insert_into_tree(QTNode * node, MovRect * mr, QuadTree qt){
	if(node == NULL){
		//std::cout << "I AM IN NULL HELP" << std::endl;
		node = new QTNode;
	}
	//std::cout << "CHILD 0 IS " << node->children_[0] << std::endl;
	if(node->has_children()){
		//pick a child
		bool was_inserted = false;

		for(int i = 0; i < 4; ++i){
			if((mr->rect_.x >= node->children_[i]->minx_
				&& mr->rect_.x + mr->rect_.w <= node->children_[i]->maxx_)
				&&
				(mr->rect_.y >= node->children_[i]->miny_
				&& mr->rect_.y + mr->rect_.h <= node->children_[i]->maxy_)){

				was_inserted = true;
				insert_into_tree(node->children_[i], mr, qt);
				break;
			}
		}

		if(!was_inserted){
			node->data_.push_back(mr);
		}
	}
	else{
		node->data_.push_back(mr);
		if(node->data_.size() >= QuadTree::threshold_
			&& qt.height(qt.proot_) < QuadTree::max_depth_){
			node->make_children();
			int current_data_size = node->data_.size();
			for(int i = 0; i < current_data_size; ++i){
				insert_into_tree(node, node->data_[i], qt);
			}
			node->data_.erase(node->data_.begin(), node->data_.begin() + current_data_size);
		}
	}
}

int QuadTree::height(QTNode * node){
	if(node == NULL){
		return -1;
	}
	else{
		return 1 + height(node->children_[0]);
	}
}

void preorderprint(QTNode * proot){
	//std::cout << proot;
	if(proot != NULL){
		for(int i = 0; i < 4; ++i){
			preorderprint(proot->children_[i]);
		}
		std::cout << proot << ' ';
		std::cout << "[";
		for(int i = 0; i < proot->data_.size(); ++i){
			std::cout << "<" << proot->data_[i]->rect_.x
						<< ", " << proot->data_[i]->rect_.y
						<< "> ";
		}
		std::cout << "]";

	}
	else{
		std::cout << '*' << ' ';
	}
}

void do_collisions(QTNode * node){
	if(node != NULL){
		for(int i = 0; i < 4; ++i){
			do_collisions(node->children_[i]);
		}
		bruteforcecollision(node->data_);
	}
}



