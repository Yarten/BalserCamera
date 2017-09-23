#include "CameraFactory.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <memory>
#include <ctime>
#include <thread>
#include <mutex>
#include <string>
#include <list>
using namespace std;
using namespace cv;
using namespace scs;


struct MatPair
{
	Mat * img[2];
};

list<MatPair> qs;
mutex mutexQS;
mutex mutexFinish;
mutex mutexIsFinish;
bool finish = false;
bool isFinish = false;


void writeMatPair(MatPair imgs, int i)
{
	static char buffer[255];
	for(int k = 0; k < 2; k++)
	{
		sprintf(buffer, "image/%k/%06d.png", k, i);
		imwrite(buffer, *imgs.img[k]);
	}
}

void writeImages()
{
	MatPair imgs;
	int index = 0;
	bool isSleep = false;

	while(1)
	{

		{
			unique_lock<mutex> lock(mutexQS);
			unique_lock<mutex> lock2(mutexFinish);

			if(finish && qs.empty()) break;
			else if(!finish && qs.empty()) isSleep = true;;
			else
			{
				imgs = qs.front();
				qs.pop_front();
			}
		}

		if(isSleep)
		{
			this_thread::sleep_for(chrono::microseconds(1000)); // 1ms
			isSleep = false;
			continue;
		}
		
		writeMatPair(imgs, index++);
		delete[] imgs.img;
		imgs.img[0] = imgs.img[1] = nullptr;
	}

	unique_lock<mutex> lock(mutexIsFinish);
	isFinish = true;
}


int main()
{
	unique_ptr<Camera> cam[2];

	for(int i = 0; i < 2; i++)
	{
		cam[i] = unique_ptr<Camera>(CameraFactory::make(CameraFactory::BalserCamera));
		if(!cam[i]->open(i))
		{
			cerr << "Camera " << i << " Failed." << endl;
			return i+1;
		}

		namedWindow(string("Image ")+char(i+'0'), 0);
	}

	MatPair img;
	char c = 0, buffer[256];
	int i = 0;

	system("mkdir image");
	system("mkdir image/0");
	system("mkdir image/1");

	mutex mutexCapture;
	int counter = 0;

	thread(writeImages).detach();
	thread th[2];

	while (c != 27)
	{
		double t1 = clock();

		counter = 2;


		for(int k = 0; k < 2; k++)
			th[k] = thread([&, k]() 
			{
				img.img[k] = new Mat;
				cam[k]->image(*img.img[k]);
				unique_lock<mutex> lock(mutexCapture);
				counter--;
			});

		for(int k = 0; k < 2; k++)
			th[k].detach();

		while(1)
		{
			this_thread::sleep_for(chrono::microseconds(1000)); // 1ms
			unique_lock<mutex> lock(mutexCapture);
			if (counter == 0) break;
		}

		{
			unique_lock<mutex> mutexQS;
			qs.push_back(img);
		}

		c = waitKey(2);

		double t2 = clock();

#ifdef WIN32
		cout << "Frame Cost = " << t2 - t1 << endl;
#else
		cout << "Frame Cost = " << (t2 - t1) / CLOCKS_PER_SEC << endl;
#endif	
	}

	{
		unique_lock<mutex> lock(mutexFinish);
		finish = true;
	}

	while(1)
	{
		this_thread::sleep_for(chrono::microseconds(1000)); // 1ms
		unique_lock<mutex> lock(mutexIsFinish);
		if (isFinish) break;
	}

	return 0;
}
