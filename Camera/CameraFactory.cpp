#include "CameraFactory.h"
#include "ImageReader.h"
#include "OpenCVCamera.h"
#include "BalserCamera.h"

namespace scs
{
	Camera * CameraFactory::make(CameraFactory::Type type)
	{
		switch (type)
		{
		case scs::CameraFactory::ImageReader:
			return new scs::ImageReader;
		case scs::CameraFactory::OpenCVCamera:
			return new scs::OpenCVCamera;
		case scs::CameraFactory::BalserCamera:
			return new scs::BalserCamera;
		default:
			return nullptr;
		}
	}
}
