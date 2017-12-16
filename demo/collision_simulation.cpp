/*
AUTHOR: Brandon Hattaway

USAGE INSTRUCTIONS:
the command line will prompt you for an integer; this is the number of rectangles that will spawn initially

during runtime, you may press space. this will change the collision detection method;
	by default, uses quadtree
	when space is pressed, uses brute force

	will toggle with each spacebar press
*/
#include "collision_simulation.h"
#include "MovRect.h"
#include "Line.h"
#include "bruteforcecollision.h"
#include "quadtreecollision.h"

int collision_simulation(){
	//input the number of rectangles you would like to create
	int num_rects;
	std::cin >> num_rects;

	//create array on the heap with the specified number of rectangles.
	MovRect * recta = new MovRect[num_rects];
	for(int i = 0; i < num_rects; ++i){
		recta[i].rect_.x = rand() % (W_RES - 10);
		recta[i].rect_.y = rand() % (H_RES - 10);
		recta[i].rect_.w = 3;
		//recta[i].h = rand() % (H_RES - 1 - recta[i].y);
		recta[i].rect_.h = recta[i].rect_.w;
		recta[i].rect_.c.r = rand() % 56 + 200;
		recta[i].rect_.c.g = rand() % 56 + 200;
		recta[i].rect_.c.b = rand() % 56 + 200;
		recta[i].dx_ = rand() % 8 - 4;
		recta[i].dy_ = rand() % 8 - 4;
	}

	//create surface
	Surface surface(W_RES + 1, H_RES + 1);
	Event event;

	//set minimum frame rate
	const int RATE = 1000 / 60;

	//use quadtree instead of brute force -- 
	//can be changed during runtime by pressing SPACE
	bool use_quadtree = true;

	//used to ensure that SPACE presses have a cooldown of 500ms
	int last_press = 0;

	while(1){
		if (event.poll() && event.type() == QUIT) break;

		//used for framerate calculation
        int start = getTicks();

		//MOVE RECTS
		for(int i = 0; i < num_rects; ++i){
			recta[i].move();
		}

		//check if SPACE was pressed
		KeyPressed keypressed = get_keypressed();
		if(keypressed[SPACE]){
			//if the last SPACE press was over 500ms ago...
			if(getTicks() - last_press > 500){
				//flip collision method
				use_quadtree = !use_quadtree;

				//set last press to now
				last_press = getTicks();
			}
		}

		//create vector of lines, these draw the quadtree borders
		std::vector< Line > lines;

		//DO COLLISION
		if(use_quadtree){
			//create a tree
			QuadTree qt(new QTNode);

			//insert all the rectangles into the tree
			for(int i = 0; i < num_rects; ++i){
				if(recta[i].get_isAlive()){
					insert_into_tree(qt.proot_, &recta[i], qt);
				}
			}

			//do collisions within each node
			do_collisions(qt.proot_);

			//p_to_c_traverse(qt.proot_);
			//do parent to child collisions
			do_p_to_c_collisions(qt.proot_, qt.proot_->children_[0]);

			//place the quadtree quadrant lines into the line vector
			find_lines(qt.proot_, lines);
			recursive_del(qt.proot_);
		}
		else{
			//do bruteforce collision
			bruteforcecollision(recta, num_rects);
		}

		//DRAW EVERYTHING
		surface.lock();
        surface.fill(BLACK);

		//draw all rectangles
		for(int i = 0; i < num_rects; ++i){
			if(recta[i].get_isAlive()){
				surface.put_rect(recta[i].rect_);
			}
		}

		//draw the quadtree boundary lines
		for(int i = 0; i < lines.size(); ++i){
			surface.put_line(lines[i].x0, lines[i].y0,
					lines[i].x1, lines[i].y1,
					lines[i].c.r, lines[i].c.g, lines[i].c.b);
		}

        surface.unlock();
        surface.flip();


		//calculate number of rectangles that are alive for debugging
		/*
		int count = 0;
		for(int i = 0; i < num_rects; ++i){
			if(recta[i].get_isAlive()) ++count;
		}
		std::cout << "NUM ALIVE: " << count << '\n';
		*/


		//determine framerate and delay if things are happening too fast
        int end = getTicks();
		//std::cout << end - start << "\n";

        int dt = RATE - end + start;
        if (dt > 0) delay(dt);
		//else std::cout << "BAD FRAMERATE : " << dt << '\n';

	}

	delete [] recta;
	return 0;
}
