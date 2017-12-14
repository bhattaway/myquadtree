#include "test0.h"
#include "MovRect.h"
#include "Line.h"
#include "bruteforcecollision.h"
#include "quadtreecollision.h"

int meme(){
	int num_rects;
	std::cin >> num_rects;

	MovRect * recta = new MovRect[num_rects];
	for(int i = 0; i < num_rects; ++i){
		recta[i].rect_.x = rand() % (W_RES - 10);
		recta[i].rect_.y = rand() % (H_RES - 10);
		recta[i].rect_.w = 4;
		//recta[i].h = rand() % (H_RES - 1 - recta[i].y);
		recta[i].rect_.h = recta[i].rect_.w;
		recta[i].rect_.c.r = rand() % 56 + 00;
		recta[i].rect_.c.g = rand() % 56 + 00;
		recta[i].rect_.c.b = rand() % 56 + 00;
		recta[i].dx_ = rand() % 8 - 4;
		recta[i].dy_ = rand() % 8 - 4;
	}
	Surface surface(W_RES + 1, H_RES + 1);
	Event event;

	const int RATE = 1000 / 60;

	bool use_quadtree = true;

	int last_press = 0;

	while(1){
		if (event.poll() && event.type() == QUIT) break;

        int start = getTicks();

		//MOVE RECTS
		for(int i = 0; i < num_rects; ++i){
			recta[i].move();
		}

		KeyPressed keypressed = get_keypressed();
		if(keypressed[SPACE]){
			if(getTicks() - last_press > 500){
				use_quadtree = !use_quadtree;
				last_press = getTicks();
			}
		}
		//DO COLLISION
		std::vector< Line > lines;
		if(use_quadtree){
			QuadTree qt(new QTNode);
			for(int i = 0; i < num_rects; ++i){
				if(recta[i].get_isAlive()){
					insert_into_tree(qt.proot_, &recta[i], qt);
				}
			}
			do_collisions(qt.proot_);
			//p_to_c_traverse(qt.proot_);
			do_p_to_c_collisions(qt.proot_, qt.proot_->children_[0]);
			find_lines(qt.proot_, lines);
			//do_parent_to_child_collisions(qt.proot_, qt.proot_->children_[0]);
		}
		else{
			bruteforcecollision(recta, num_rects);
		}

		surface.lock();
        surface.fill(BLACK);
		for(int i = 0; i < num_rects; ++i){
			if(recta[i].get_isAlive()){
				surface.put_rect(recta[i].rect_);
			}
		}

		for(int i = 0; i < lines.size(); ++i){
			surface.put_line(lines[i].x0, lines[i].y0,
					lines[i].x1, lines[i].y1,
					lines[i].c.r, lines[i].c.g, lines[i].c.b);
		}
        surface.unlock();
        surface.flip();



		/*
		int count = 0;
		for(int i = 0; i < num_rects; ++i){
			if(recta[i].get_isAlive()) ++count;
		}
		std::cout << "NUM ALIVE: " << count << '\n';
		*/


        int end = getTicks();
		//std::cout << end - start << "\n";

        int dt = RATE - end + start;
        if (dt > 0) delay(dt);
		//else std::cout << "BAD FRAMERATE : " << dt << '\n';

	}

	delete [] recta;
	return 0;
}
