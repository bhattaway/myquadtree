#include "quadtreecollision.h"
#include "bruteforcecollision.h"

int QuadTree::threshold_ = 8;
int QuadTree::max_depth_ = 6;

QTNode::QTNode(QTNode * parent, int minx, int maxx, int miny, int maxy)
	: parent_(parent), minx_(minx), maxx_(maxx), miny_(miny), maxy_(maxy)
{
	for(int i = 0; i < 4; ++i){
		children_[i] = NULL;
	}
}

//returns true if the node has children
bool QTNode::has_children() const{
	//child 0 does not exist, therefore no children exist
	return (children_[0] != NULL);
}

//creates new children for the current node
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
	children_[0] = new QTNode(this, minx_, minx_ + (maxx_ - minx_) / 2, miny_, miny_ + (maxy_ - miny_) / 2);
	children_[1] = new QTNode(this, minx_ + (maxx_ - minx_) / 2 + 1, maxx_, miny_, miny_ + (maxy_ - miny_) / 2);
	children_[2] = new QTNode(this, minx_, minx_ + (maxx_ - minx_) / 2, miny_ + (maxy_ - miny_) / 2 + 1, maxy_);
	children_[3] = new QTNode(this, minx_ + (maxx_ - minx_) / 2 + 1, maxx_, miny_ + (maxy_ - miny_) / 2 + 1, maxy_);
}

//returns true if this node has a parent
bool QTNode::has_parent() const{
	return (parent_ != NULL);
}

//quadtree constructor
QuadTree::QuadTree(QTNode * proot)
	: proot_(proot)
{
}

//deletes a tree recursively
void recursive_del(QTNode * node){
	if(node != NULL){
		for(int i = 0; i < 4; ++i){
			recursive_del(node->children_[i]);
		}
		delete node;
	}
}

//inserts a moving rectangle into a tree
void insert_into_tree(QTNode * node, MovRect * mr, QuadTree qt){
	//if node does not exist, make one
	if(node == NULL){
		node = new QTNode;
	}

	
	if(node->has_children()){
		bool was_inserted = false;

		//pick a child to insert the rectangle into
		for(int i = 0; i < 4; ++i){
			if((mr->rect_.x >= node->children_[i]->minx_
				&& mr->rect_.x + mr->rect_.w <= node->children_[i]->maxx_)
				&&
				(mr->rect_.y >= node->children_[i]->miny_
				&& mr->rect_.y + mr->rect_.h <= node->children_[i]->maxy_)){

				//child i is chosen
				was_inserted = true;
				//do a recursive insert
				insert_into_tree(node->children_[i], mr, qt);
				break;
			}
		}

		//if it could not be inserted into any child, put it into this node instead
		//(i.e. if the rectangle was on a border)
		if(!was_inserted){
			node->data_.push_back(mr);
		}
	}

	//this node has no children
	else{
		//put the rectangle into this node's data vector
		node->data_.push_back(mr);

		//if the threshold was broken AND the tree is less than max_depth
		if(node->data_.size() >= QuadTree::threshold_
			&& qt.height(qt.proot_) < QuadTree::max_depth_){

			//make children
			node->make_children();

			//move data from parent to newly created children
			int current_data_size = node->data_.size();
			for(int i = 0; i < current_data_size; ++i){
				insert_into_tree(node, node->data_[i], qt);
			}
			//remove all the data from this node that went to the children
			node->data_.erase(node->data_.begin(), node->data_.begin() + current_data_size);
		}
	}
}

//returns height of the tree
int QuadTree::height(QTNode * node){
	if(node == NULL){
		return -1;
	}
	else{
		return 1 + height(node->children_[0]);
	}
}

//recursively add lines to a line vector (for drawing the boundaries of each quadrant)
void find_lines(QTNode * node, std::vector< Line > & lines){
	if(node != NULL){
		for(int i = 0; i < 4; ++i){
			find_lines(node->children_[i], lines);
		}
		Line l0(node->minx_, node->miny_, node->maxx_, node->miny_);
		Line l1(node->minx_, node->miny_, node->minx_, node->maxy_);
		Line l2(node->minx_, node->maxy_, node->maxx_, node->maxy_);
		Line l3(node->maxx_, node->miny_, node->maxx_, node->maxy_);
		lines.push_back(l0);
		lines.push_back(l1);
		lines.push_back(l2);
		lines.push_back(l3);
	}
}

//prints the tree, for debugging
void preorderprint(QTNode * proot){
	//std::cout << proot;
	if(proot != NULL){
		std::cout << proot << ' ';
		std::cout << "[";
		for(int i = 0; i < proot->data_.size(); ++i){
			std::cout << "<" << proot->data_[i]->rect_.x
						<< ", " << proot->data_[i]->rect_.y
						<< "> ";
		}
		std::cout << "]";

		for(int i = 0; i < 4; ++i){
			preorderprint(proot->children_[i]);
		}

	}
	//if node does not exist, print a star
	else{
		std::cout << '*' << ' ';
	}
}

//pass in a proot and process the collisions for the tree
void do_collisions(QTNode * node){
	//TODO: Check collisions between parents and all children
	if(node != NULL){
		for(int i = 0; i < 4; ++i){
			do_collisions(node->children_[i]);
		}
		bruteforcecollision(node->data_);
	}
}

//do parent to child collisions (kinda doesn't work, dunno why
void do_p_to_c_collisions(QTNode * node, QTNode * subnode){
	if(node == NULL){
	}
	else{
		if(subnode == NULL){
		}
		else{
			if(subnode->has_children()){
				for(int i = 0; i < 4; ++i){
					do_p_to_c_collisions(node, subnode->children_[i]);
				}
			}
			bruteforcecollision(node->data_, subnode->data_);
		}
	}
}

//traverse the tree for the parent to child collisions (doesn't work)
void p_to_c_traverse(QTNode * node){
	if(node != NULL){
		if(node->has_children()){
			for(int i = 0; i < 4; ++i){
				p_to_c_traverse(node);
			}
			for(int i = 0; i < 4; ++i){
				do_p_to_c_collisions(node, node->children_[i]);
			}
		}
	}
}

//another attempt at making parent to children collisions work; doesn't work
void do_parent_to_child_collisions(QTNode * node, QTNode * child){
	if(node != NULL && node->has_children()){
		if(node != NULL){
			for(int i = 0; i < 4; ++i){
				do_parent_to_child_collisions(node->children_[i]);
			}
			if(child->has_children()){
				for(int i = 0; i < 4; ++i){
					do_parent_to_child_collisions(node, child->children_[i]);
				}
			}
			bruteforcecollision(node->data_, child->data_);
		}
	}
}



