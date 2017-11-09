#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cstring>
#include "Frame.h"
#define J 720
#define P 480
using namespace std; 
Frame frame;
int main(int argc, char * argv[]) {
	const double frames_per_second = 30;
	const int duration_in_seconds = 3;
	const char * cmd =
		"ffmpeg\\bin\\ffmpeg.exe "
		"-y                  "
		"-hide_banner        "
		"-f rawvideo         " 
		"-pixel_format rgb24 "
		"-video_size 720x480 "
		"-r 60               " 
		"-i -                " 
		"-pix_fmt yuv420p    " 
		"-vcodec mpeg4       "
		"-an                 "
		"-q:v 5              "
		"output.mp4          ";
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
		frame.draw_frame(time_in_seconds);
		fwrite(frame.container, 3, J * P, pipe);
	}
	fflush(pipe);
	_pclose(pipe);

	cout << "num_frames: " << num_frames << endl;
	cout << "Done." << endl;
	return 0;
}
