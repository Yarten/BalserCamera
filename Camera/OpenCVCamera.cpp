#include "OpenCVCamera.h"

bool scs::OpenCVCamera::open(int index)
{
	cam.open(index);
	cam.set(CV_CAP_PROP_FRAME_WIDTH, 720);
	cam.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	return cam.isOpened();
}

void scs::OpenCVCamera::close()
{
	cam.release();
}

bool scs::OpenCVCamera::image(Mat & im)
{
	if (!cam.isOpened()) return false;
	cam >> im;
	return im.data != nullptr;
}
