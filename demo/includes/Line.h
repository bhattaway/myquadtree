/*****************************************************************************
 Yihsiang Liow
 Copyright
 *****************************************************************************/
#ifndef LINE_H
#define LINE_H

#include <iostream>
#include "Color.h"

class Line
{
public:
	Line(int x0_ = 0, int y0_ = 0, int x1_ = 0, int y1_ = 0, 
		int r0 = 255, int g0 = 255, int b0 = 255)
		: x0(x0_), y0(y0_), x1(x1_), y1(y1_)
	{
		c.r = r0;
		c.g = g0;
		c.b = b0;
	}
	/*
    Rect( const SDL_Rect & rect)
		: x(rect.x), y(rect.y), w(rect.w), h(rect.h)
	{
		c.r = 255;
		c.g = 255;
		c.b = 255;
	}
	SDL_Rect getSDL_Rect()
	{
		SDL_Rect rec = {x, y, w, h};
		return rec;
	}
	*/
	int x0, y0, x1, y1;
	Color c;
};

/*
inline std::ostream & operator<<(std::ostream & cout, const Rect & r)
{
	cout << "(" << r.x << "," << r.y << "," << r.w << "," << r.h << ")";
	return cout;
}
*/
#endif
