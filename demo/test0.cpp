#include "test0.h"

class MovRect{
public:
	MovRect()
		: dx_(0), dy_(0), isAlive_(true)
	{
	}
	MovRect(Rect rect, int dx = 0, int dy = 0)
		: rect_(rect), dx_(dx), dy_(dy), isAlive_(true)
	{
	}

	void set_isAlive(bool b){
		isAlive_ = b;
	}
	bool get_isAlive(){
		return isAlive_;
	}
	void set_dy(int newdy){
		dy_ = newdy;
	}
	int get_dy(){
		return dy_;
	}
	void set_dx(int newdx){
		dx_ = newdx;
	}
	int get_dx(){
		return dx_;
	}
	void set_rect(const Rect & newrect){
		rect_ = newrect;
	}
	Rect get_rect(){
		return rect_;
	}
	void move(){
		//only move if rect is alive
		if(isAlive_){
			rect_.x += dx_;
			rect_.y += dy_;

			if(rect_.x < 0){
				rect_.x = 0;
				dx_ = -dx_;
			}
			if(rect_.x > W_RES - rect_.w){
				rect_.x = W_RES - rect_.w;
				dx_ = -dx_;
			}
			if(rect_.y < 0){
				rect_.y = 0;
				dy_ = -dy_;
			}
			if(rect_.y > H_RES - rect_.h){
				rect_.y = H_RES - rect_.h;
				dy_ = -dy_;
			}

			/*
			++rect_.c.r;
			++rect_.c.g;
			++rect_.c.b;
			*/
		}
	}
//private:
	Rect rect_;
	int dx_;
	int dy_;
	bool isAlive_;
};

int meme(){
	int num_rects;
	std::cin >> num_rects;

	MovRect * recta = new MovRect[num_rects];
	for(int i = 0; i < num_rects; ++i){
		recta[i].rect_.x = rand() % (W_RES - 21);
		recta[i].rect_.y = rand() % (H_RES - 21);
		recta[i].rect_.w = 2;
		//recta[i].h = rand() % (H_RES - 1 - recta[i].y);
		recta[i].rect_.h = recta[i].rect_.w;
		recta[i].rect_.c.r = rand() % 56 + 200;
		recta[i].rect_.c.g = rand() % 56 + 200;
		recta[i].rect_.c.b = rand() % 56 + 200;
		recta[i].dx_ = rand() % 8 - 4;
		recta[i].dy_ = rand() % 8 - 4;
	}
	Surface surface(W_RES, H_RES);
	Event event;

	const int RATE = 1000 / 60;

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
		//COLLISION DETECTION -- BRUTE FORCE
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

		int count = 0;
		for(int i = 0; i < num_rects; ++i){
			if(recta[i].get_isAlive()) ++count;
		}
		std::cout << "NUM ALIVE: " << count << '\n';


        int end = getTicks();

        int dt = RATE - end + start;
        if (dt > 0) delay(dt);
		//else std::cout << "BAD FRAMERATE : " << dt << '\n';

	}

	delete [] recta;
	return 0;
}
