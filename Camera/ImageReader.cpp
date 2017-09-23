#include "ImageReader.h"
#include <iostream>
using namespace cv;
using namespace std;

bool scs::ImageReader::open(int index)
{
	cout
		<< "Open Camera " << index << ": " << endl
		<< "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl
		<< "Input |   dir   |   suffix   |   width   |   start   |   end   |" << endl
		<< ">>>: ";
	cin >> dir >> suffix >> width >> start >> end;
	
	reset();
	return true;
}

bool scs::ImageReader::open(string _dir, string _suffix, int _width, int _start, int _end)
{
	dir = _dir;
	suffix = _suffix;
	width = _width;
	start = _start;
	end = _end;
	reset();
	return true;
}

bool scs::ImageReader::image(Mat & frame)
{
	char name[256];
	if (iterator > end)
	{
		reset();
		frame = Mat();
	}
#ifndef WIN32
	#define sprintf_s sprintf
#endif
	sprintf_s(name, "%s/%0*d.%s", dir.c_str(), width, iterator++, suffix.c_str());
	frame = imread(name);

	return frame.data != nullptr;
}
