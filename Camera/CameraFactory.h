#pragma once
#include "Camera.h"

namespace scs
{
	class SCS_API CameraFactory
	{
	public:
		enum Type
		{
			ImageReader,
			OpenCVCamera,
			BalserCamera
		};
	public:
		static Camera * make(CameraFactory::Type type);
	};

}

