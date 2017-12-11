#ifndef QUADTREECOLLISION_H
#define QUADTREECOLLISION_H

#include "test0.h"
#include "MovRect.h"

class QTNode{
public:
	QTNode(int minx = 0, int maxx = W_RES, int miny = 0, int maxy = H_RES);
	bool has_children() const;
	void insert(MovRect * rect);

	int minx_, maxx_;
	int miny_, maxy_;
	QTNode * children_[4];
	std::vector < MovRect * > data_;
private:
};

class QuadTree{
public:
	QuadTree(QTNode * proot = NULL);
	void qtinsert(MovRect * mr);

	QTNode * proot_;
	static int max_depth_;
	static int threshold_;
private:
};

void quadtreecollision(MovRect * recta, const int num_rects);

#endif
