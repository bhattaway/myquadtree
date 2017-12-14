#include "test0.h"
#include "MovRect.h"
#include "bruteforcecollision.h"
#include "quadtreecollision.h"

int meme(){
	int num_rects;
	std::cin >> num_rects;

	MovRect * recta = new MovRect[num_rects];
	for(int i = 0; i < num_rects; ++i){
		recta[i].rect_.x = rand() % (W_RES - 10);
		recta[i].rect_.y = rand() % (H_RES - 10);
		recta[i].rect_.w = 2;
		//recta[i].h = rand() % (H_RES - 1 - recta[i].y);
		recta[i].rect_.h = recta[i].rect_.w;
		recta[i].rect_.c.r = rand() % 56 + 200;
		recta[i].rect_.c.g = rand() % 56 + 200;
		recta[i].rect_.c.b = rand() % 56 + 200;
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

		surface.lock();
        surface.fill(BLACK);
		for(int i = 0; i < num_rects; ++i){
			if(recta[i].get_isAlive()){
				surface.put_rect(recta[i].rect_);
			}
		}
        surface.unlock();
        surface.flip();

		KeyPressed keypressed = get_keypressed();
		if(keypressed[SPACE]){
			//keydelay = getTicks();
			if(getTicks() - last_press > 500){
				use_quadtree = !use_quadtree;
				last_press = getTicks();
			}
		}

		if(use_quadtree){
			QuadTree qt(new QTNode);
			for(int i = 0; i < num_rects; ++i){
				if(recta[i].get_isAlive()){
					insert_into_tree(qt.proot_, &recta[i], qt);
				}
			}
			do_collisions(qt.proot_);
		}
		else{
			bruteforcecollision(recta, num_rects);
		}
		//COLLISION DETECTION -- BRUTE FORCE
		/*
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
		*/

		//COLLISION DETECTION -- QUADTREE
		//std::cout << "building tree ...\n";
		//QTNode * qtn = new QTNode;
		//std::cout << "colliding ...\n";
		//std::cout << "about to print\n";
		//preorderprint(qt.proot_);

		//quadtreecollision(recta, num_rects);
		/*
		std::cout << "done with collisions!\n";
		std::cout << "height : " << qt.height(qt.proot_) << std::endl;
		int arstd;
		std::cin >> arstd;
		*/


		

		/*
		int count = 0;
		for(int i = 0; i < num_rects; ++i){
			if(recta[i].get_isAlive()) ++count;
		}
		std::cout << "NUM ALIVE: " << count << '\n';
		*/


        int end = getTicks();
		std::cout << end - start << "\n";

        int dt = RATE - end + start;
        if (dt > 0) delay(dt);
		//else std::cout << "BAD FRAMERATE : " << dt << '\n';

	}

	delete [] recta;
	return 0;
}
