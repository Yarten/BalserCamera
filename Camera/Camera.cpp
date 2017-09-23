#include "Camera.h"
using namespace cv;
using namespace scs;

#define oo 9999999

scs::Camera::Parameter::Parameter()
{
	setXYZScale(1, 1, 1);
	setFocalScale(1, 1);
	setPrinciple(-oo, -oo);
}

void scs::Camera::Parameter::load(const string & dir, const string & cam)
{
	FileStorage fs(dir, FileStorage::READ);
	fs[cam] >> (*this);
}

void scs::Camera::Parameter::save(const string & dir, const string & cam, FileStorage::Mode mode)
{
	FileStorage fs(dir, mode);
	fs << cam << (*this);
}

void scs::Camera::Parameter::setIntrinsicMatrix(double fx, double fy, double cx, double cy)
{
	intrinsic = (Mat_<double>(3, 3) << fx, 0, cx, 0, fy, cy, 0, 0, 1);
}

void scs::Camera::Parameter::setDistortionVector(double k1, double k2, double p1, double p2, double k3)
{
	distortion = (Mat_<double>(5, 1) << k1, k2, p1, p2, k3);
}

void scs::Camera::Parameter::setResolution(int width, int height)
{
	resolution.width = width;
	resolution.height = height;
}

void scs::Camera::Parameter::setXYZScale(double _sx, double _sy, double _sz)
{
	sx = _sx;
	sy = _sy;
	sz = _sz;
}

void scs::Camera::Parameter::setFocalScale(double _sfx, double _sfy)
{
	sfx = _sfx;
	sfy = _sfy;
}

void scs::Camera::Parameter::setPrinciple(double _cx, double _cy)
{
	cx = _cx;
	cy = _cy;
}


Mat scs::Camera::Parameter::getR() const
{
	return (Mat_<double>(3, 1) << sx, sy, sz);
}

Mat scs::Camera::Parameter::getP() const
{
	Mat P = intrinsic.clone();
	if (P.data != nullptr)
	{
		P.at<double>(0, 0) *= sfx;
		P.at<double>(1, 1) *= sfy;
		if(cx != -oo) P.at<double>(0, 2) = cx;
		if(cy != -oo) P.at<double>(1, 2) = cy;
	}
	return P;
}

namespace scs
{
	void write(FileStorage & fs, const string & dir, const Camera::Parameter & x)
	{
		fs << "{"
			<< "fx" << x.intrinsic.at<double>(0, 0)
			<< "fy" << x.intrinsic.at<double>(1, 1)
			<< "cx" << x.intrinsic.at<double>(0, 2)
			<< "cy" << x.intrinsic.at<double>(1, 2)
			<< "k1" << x.distortion.at<double>(0, 0)
			<< "k2" << x.distortion.at<double>(1, 0)
			<< "p1" << x.distortion.at<double>(2, 0)
			<< "p2" << x.distortion.at<double>(3, 0)
			<< "k3" << x.distortion.at<double>(4, 0)
			<< "width" << x.resolution.width
			<< "height" << x.resolution.height
			<< "sfx" << x.sfx
			<< "sfy" << x.sfy
			<< "newcx" << x.cx
			<< "newcy" << x.cy
			<< "sx" << x.sx
			<< "sy" << x.sy
			<< "sz" << x.sz
			<< "}";
	}

	void read(const FileNode & node, Camera::Parameter & x, const Camera::Parameter & default_value)
	{
		if (node.empty())
			x = default_value;
		else
		{
			double fx, fy, cx, cy, k1, k2, p1, p2, k3, width, height;
			node["fx"] >> fx;
			node["fy"] >> fy;
			node["cx"] >> cx;
			node["cy"] >> cy;
			node["k1"] >> k1;
			node["k2"] >> k2;
			node["p1"] >> p1;
			node["p2"] >> p2;
			node["k3"] >> k3;
			node["width"] >> width;
			node["height"] >> height;
			node["sfx"] >> x.sfx;
			node["sfy"] >> x.sfy;
			node["newcx"] >> x.cx;
			node["newcy"] >> x.cy;
			node["sx"] >> x.sx;
			node["sy"] >> x.sy;
			node["sz"] >> x.sz;
			x.setIntrinsicMatrix(fx, fy, cx, cy);
			x.setDistortionVector(k1, k2, p1, p2, k3);
			x.setResolution(width, height);
		}
	}
}

