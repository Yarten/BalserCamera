#include "CameraFactory.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <memory>
#include <ctime>
#include <thread>
using namespace std;
using namespace cv;
using namespace scs;

int main()
{
	unique_ptr<Camera> camLeft(CameraFactory::make(CameraFactory::BalserCamera));
	unique_ptr<Camera> camRight(CameraFactory::make(CameraFactory::BalserCamera));
	
	if (!camLeft->open(0))
	{
		cerr << "Left Camera Failed." << endl;
		return 1;
	}

	if (!camRight->open(1))
	{
		cerr << "Right Camera Failed." << endl;
		return 2;
	}

	Mat imgLeft, imgRight;
	char c = 0, buffer[256];
	int i = 0;

	namedWindow("Left Image", 0);
	namedWindow("Right Image", 0);
	system("mkdir image");
	system("mkdir image/left");
	system("mkdir image/right");

	while (c != 27)
	{
		double t1 = clock();

		
		camLeft->image(imgLeft);
		camRight->image(imgRight);

		sprintf(buffer, "image/left/%06d.png", i);
	//	imwrite(buffer, imgLeft);
		sprintf(buffer, "image/right/%06d.png", i);
	//	imwrite(buffer, imgRight);
		i++;

		imshow("Left Image", imgLeft);
	//	imshow("Right Image", imgRight);

		c = waitKey(2);

		double t2 = clock();

#ifdef WIN32
		cout << "Frame Cost = " << t2 - t1 << endl;
#else
		cout << "Frame Cost = " << (t2 - t1) / CLOCKS_PER_SEC << endl;
#endif	
	}

	return 0;
}
