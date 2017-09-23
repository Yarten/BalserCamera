#pragma once
#include <opencv2/opencv.hpp>
#include <string>

using std::string;
using cv::Mat;
using cv::Size;
using cv::FileStorage;
using cv::FileNode;

#ifdef WIN32

# ifdef SCS_EXPORTS
#  define SCS_API __declspec(dllexport)
# else
#  define SCS_API __declspec(dllimport)
# endif

#else
# define SCS_API
#endif

namespace scs
{
	class SCS_API Camera
	{
	public:
		class SCS_API Parameter
		{
		public:
			Parameter();

			/**
			 * @Title: load / save
			 * @Description: Set/save camera parameter by .yaml file.
			 * @param: dir, path of the file.
			 * @param: cam, name of the Parameter object in the setting file.
			*/
			virtual void load(const string & dir, const string & cam);
			virtual void save(const string & dir, const string & cam, FileStorage::Mode mode = FileStorage::WRITE);

			void setIntrinsicMatrix(double fx, double fy, double cx, double cy);
			void setDistortionVector(double k1, double k2, double p1, double p2, double k3 = 0.0);
			void setResolution(int width, int height);
			void setXYZScale(double sx, double sy, double sz);
			void setFocalScale(double sfx, double sfy);
			void setPrinciple(double cx, double cy);

			Mat getIntrinsicMatrix() const { return intrinsic; }
			Mat getDistortion() const { return distortion; }
			Size getResolution() const { return resolution; }
			Mat getR() const;
			Mat getP() const;

		protected:
			// These write and read functions must be defined for the serialization in FileStorage to work
			friend void write(FileStorage & fs, const string & dir, const Parameter & x);
			friend void read(const FileNode & node, Parameter & x, const Parameter & default_value);

			double sfx, sfy, cx, cy, sx, sy, sz;
			Mat intrinsic, distortion;
			Size resolution;
		} param;

	public:
		virtual bool open(int index) = 0;
		virtual void close() = 0;
		virtual bool image(Mat & im) = 0;

		virtual ~Camera() {}	
	};

	

} /// Namespace scs

