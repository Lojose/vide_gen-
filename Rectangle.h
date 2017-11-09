#pragma once
#include "windows.h"

class Rectangle {
public:
	void draw_rect(); 
private:
	double x; 
	double y; 
	double w;
	double h; 
	byte r; 
	byte g; 
	byte b; 
};
