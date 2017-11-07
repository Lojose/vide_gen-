#include <iostream>
#include <sstream>
#include <windows.h>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cstring>

using namespace std; 
#define W 720
#define H 480

class Rectangle {
public: 
	Rectangle(int x, int y); 
	~Rectangle(); 
	void draw_frame(double t); 
	void draw_rect(int x, int y, int w, int h, byte r, byte g, byte b); 
	void clamp(int *x, int *y); 
	void clearframe(); 
	bool outside_frame(int *x, int *y);
	int buildcommand(int argc, char * argv[]); 
	int m1(int argc, char * argv[], const char*cmd);
private:
	int x; 
	int y; 
	unsigned char frame[H][W][3];  
};

Rectangle::Rectangle(int x, int y) {
	this->x = x; 
	this->y = y; 
}

void Rectangle::clearframe() {
	memset(frame, 0, sizeof(frame));
}

bool Rectangle::outside_frame(int *x, int *y) {
	return *x < 0 || *x >= W || *y < 0 || *y >= H;
}
void Rectangle::clamp(int *x, int *y) {
	if (*x < 0) *x = 0; else if (*x >= W) *x = W - 1;
	if (*y < 0) *y = 0; else if (*y >= H) *y = H - 1;
}

void Rectangle::draw_rect(int x, int y, int w, int h, byte r,byte g, byte b) {
	if (outside_frame(&x, &y)) return; 
	int x0 = x; 
	int x1 = x + w;
	int y0 = y;
	int y1 = y + h;
	clamp(&x0, &y0);
	clamp(&x1, &y1);
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame[y][x][0] = r;
			frame[y][x][1] = g;
			frame[y][x][2] = b;
		}
	}
}

void Rectangle::draw_frame(double t ) {
	clearframe();
	const double pps = 80; // pixels per second
	draw_rect(0 + t * pps, 0 + t * pps, 20, 20, 0x00, 0xff, 0x00);
}

int Rectangle::buildcommand(int argc, char * argv[]) {
	const char * cmd =
		"ffmpeg\\bin\\ffmpeg.exe"
		" "
		"-y                  "
		" "
		"-hide_banner        "
		" "
		"-f rawvideo         " // input to be raw video data
		"-pixel_format rgb24 "
		" "
		"-video_size 720x480 "
		" "
		"-r 60               " // frames per second
		" "
		"-i -                " // read data from the standard input stream
		"-pix_fmt yuv420p    " // to render with Quicktime
		" "
		"-vcodec mpeg4       "
		" "
		"-an                 " // no audio
		" "
		"-q:v 5              " // quality level; 1 <= q <= 32
		"output.mp4          ";
	return 0; 
}

int Rectangle::m1(int argc, char * argv[], const char*cmd) {
	const double frames_per_second = 30;
	const int duration_in_seconds = 3;
	// Run the ffmpeg command and get pipe to write into its standard input stream.
	FILE * pipe = _popen(cmd, "w");
	if (pipe == 0) {
		cout << "error: " << strerror(errno) << endl;
		return 1;
	}
	// Write video frames into the pipe.
	int num_frames = duration_in_seconds * frames_per_second;
	for (int i = 0; i < num_frames; ++i) {
		double time_in_seconds = i / frames_per_second;
		draw_frame(time_in_seconds);
		fwrite(frame, 3, W * H, pipe);
	}
	fflush(pipe);
	_pclose(pipe);
	cout << "num_frames: " << num_frames << endl;
	return 0;
}

int main() {
	Rectangle re;
	re.
	cout << "All test passed" << endl;

}
