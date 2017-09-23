#include "BalserCamera.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstring>
#include <ctime>
using namespace cv;
using namespace scs;
using namespace std;
using namespace Pylon;

static int balser_camera_counter = 0;
DeviceInfoList BalserCamera::devices;

scs::BalserCamera::BalserCamera()
	: MaxNumBuffer(10), GrabStrategy(EGrabStrategy::GrabStrategy_OneByOne)
{
	if (++balser_camera_counter == 1)
	{
		PylonInitialize();

		CTlFactory & tlFactory = CTlFactory::GetInstance();
		tlFactory.EnumerateDevices(BalserCamera::devices);
	}

	converter.OutputPixelFormat = PixelType_BGR8packed;
}

scs::BalserCamera::~BalserCamera()
{
	close();

	if (--balser_camera_counter == 0)
	{
		PylonTerminate();
	}
}

bool scs::BalserCamera::open(int index)
{
	CTlFactory & tlFactory = CTlFactory::GetInstance();
	size_t ndevices = BalserCamera::devices.size();

	if (ndevices == 0)
	{
		cout << "No Camera Present." << endl;
		return false;
	}
	else if (index < 0 || index >= ndevices)
	{
		cout << "Wrong Camera Index." << endl;
		return false;
	}
	else obj.Attach(tlFactory.CreateDevice(BalserCamera::devices[index]));

	try { obj.Open(); }
	catch (RuntimeException e)
	{
		cout << e.what() << endl;
	}

	return obj.IsOpen();
}

void scs::BalserCamera::close()
{
	obj.Close();
}

bool scs::BalserCamera::image(Mat & im)
{
	if (!obj.IsOpen()) return false;

	obj.MaxNumBuffer = MaxNumBuffer;
	obj.StartGrabbing(1, GrabStrategy);
	
	while (obj.IsGrabbing())
	{
		obj.RetrieveResult(5000, imgPtr, TimeoutHandling_Return);

		if (imgPtr->GrabSucceeded())
		{					
			converter.Convert(targetImage, imgPtr);
			uchar * ptr = (uchar*)targetImage.GetBuffer();

			int height = targetImage.GetHeight();
			int width = targetImage.GetWidth();

			im.create(height, width, CV_8UC3);
			memcpy(im.data, ptr, width * height * 3);
		//	return true;
		//	cvtColor(im, im, CV_RGB2BGR);
		}
		else return false;
	}

	return im.data == nullptr;
}
