/*****************************************************************************
 Yihsiang Liow
 Copyright
 *****************************************************************************/
#ifndef RECT_H
#define RECT_H

#include <iostream>
#include "Color.h"

class Rect
{
public:
	Rect(int x0 = 0, int y0 = 0, int w0 = 0, int h0 = 0, 
		int r0 = 255, int g0 = 255, int b0 = 255)
		: x(x0), y(y0), w(w0), h(h0)
	{
		c.r = r0;
		c.g = g0;
		c.b = b0;
	}
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
	int x, y, w, h;
	Color c;
};

inline std::ostream & operator<<(std::ostream & cout, const Rect & r)
{
	cout << "(" << r.x << "," << r.y << "," << r.w << "," << r.h << ")";
	return cout;
}
#endif
