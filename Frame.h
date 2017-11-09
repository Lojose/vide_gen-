#pragma once
#include "Rectangle.h"

class Frame {
public: 
	Rectangle rec;  
	bool outside_frame(double *x, double *y);
	void clamp(double *x, double *y);
	void clear_frame(); 
	void draw_frame(double t);
	unsigned char container[100][1000][3]; 
private:
};
