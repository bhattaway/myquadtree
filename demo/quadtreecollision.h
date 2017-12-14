#ifndef QUADTREECOLLISION_H
#define QUADTREECOLLISION_H

#include "test0.h"
#include "MovRect.h"

class QTNode{
public:
	QTNode(QTNode * parent = NULL, int minx = 0, int maxx = W_RES - 1, int miny = 0, int maxy = H_RES - 1);
	bool has_children() const;
	bool has_parent() const;
	void insert(MovRect * rect);
	void make_children();

	int minx_, maxx_;
	int miny_, maxy_;
	QTNode * children_[4];
	QTNode * parent_;
	std::vector < MovRect * > data_;
private:
};

class QuadTree{
public:
	QuadTree(QTNode * proot = NULL);
	/*
	~QuadTree();
	void recursive_del(QTNode * node);
	*/
	int height(QTNode * node);

	QTNode * proot_;
	static int max_depth_;
	static int threshold_;
private:
};

void preorderprint(QTNode * proot);
void quadtreecollision(MovRect * recta, const int num_rects);
void insert_into_tree(QTNode * node, MovRect * mr, QuadTree qt);
void do_collisions(QTNode * node);

#endif
