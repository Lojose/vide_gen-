#include "Rectangle.h"
#include "Frame.h"

extern Frame f; 

void Rectangle::draw_rect() {
	if (f.outside_frame(&x, &y)) return;
	double x0 = x;
	double x1 = x + w;
	double y0 = y;
	double y1 = y + h;
	f.clamp(&x0, &y0);
	f.clamp(&x1, &y1);
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			f.container[y][x][0] = r;
			f.container[y][x][1] = g;
			f.container[y][x][2] = b;
		}
	}
}
