#include "Frame.h"
//#include "Rectangle.h"
#define J 720
#define P 480

//extern Rectangle rec; 
void Frame::clear_frame() {

}

void Frame::draw_frame(double t) {
	clear_frame(); 
	const double pps = 80; // pixels per second
	rec.draw_rect(0 + t * pps, 0 + t * pps, 20, 10, 0x00, 0xff, 0x00);
}
bool Frame::outside_frame(double *x, double *y) {
	return *x < 0 || *x >= J || *y < 0 || *y >= P;
}

void Frame::clamp(double * x, double * y) {
	if (*x < 0) *x = 0; else if (*x >= J) *x = J - 1;
	if (*y < 0) *y = 0; else if (*y >= P) *y = P - 1;
}
