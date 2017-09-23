#pragma once
#include "Camera.h"
#include <opencv2/opencv.hpp>

using cv::VideoCapture;

namespace scs
{
	class OpenCVCamera : public Camera
	{
	public:
		bool open(int index) override;
		void close() override;
		bool image(Mat & im) override;

	private:
		VideoCapture cam;
	};
}