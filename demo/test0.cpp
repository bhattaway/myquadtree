#include "test0.h"

class MovRect{
public:
	MovRect(Rect rect, int dx = 0, int dy = 0)
		: rect_(rect), dx_(dx), dy_(dy)
	{
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
//private:
	Rect rect_;
	int dx_;
	int dy_;
};

int meme(){
	int num_rects;
	std::cin >> num_rects;

	Rect * recta = new Rect[num_rects];
	for(int i = 0; i < num_rects; ++i){
		recta[i].x = rand() % (W_RES - 1);
		recta[i].y = rand() % (H_RES - 1);
		recta[i].w = rand() % (W_RES - 1 - recta[i].x);
		//recta[i].h = rand() % (H_RES - 1 - recta[i].y);
		recta[i].h = recta[i].w;
		recta[i].c.r = rand() % 256;
		recta[i].c.g = rand() % 256;
		recta[i].c.b = rand() % 256;
	}
	Surface surface(W_RES, H_RES);
	Event event;

	const int RATE = 1000 / 60;

	while(1){
		if (event.poll() && event.type() == QUIT) break;

        int start = getTicks();

		for(int i = 0; i < num_rects; ++i){
			++recta[i].c.r;
			++recta[i].c.g;
			++recta[i].c.b;


		}

		surface.lock();
        surface.fill(BLACK);
		for(int i = 0; i < num_rects; ++i){
			surface.put_rect(recta[i]);
		}
        surface.unlock();
        surface.flip();

        int end = getTicks();

        int dt = RATE - end + start;
        if (dt > 0) delay(dt);
		//else std::cout << "BAD FRAMERATE : " << dt << '\n';

	}

	delete [] recta;
	return 0;
}
