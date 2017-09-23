#pragma once
#include "Camera.h"
#include <opencv2/opencv.hpp>
#include <string>
using cv::Mat;
using std::string;

namespace scs
{
	class SCS_API ImageReader : public Camera
	{	
	public:
		bool open(int index) override;
		bool open(string dir, string suffix, int width, int start, int end);
		void close() override {}
		bool image(Mat & im) override;

		void reset() { iterator = start; }
	private:
		string dir, suffix;
		int width, start, end, iterator;
	};
}