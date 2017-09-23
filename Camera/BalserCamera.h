#pragma once
#include "Camera.h"
#include "utils.h"
#include <pylon/PylonIncludes.h>
using Pylon::CInstantCamera;
using Pylon::EGrabStrategy;
using Pylon::DeviceInfoList;
using Pylon::CInstantCameraArray;
using Pylon::CGrabResultPtr;
using Pylon::CPylonImage;
using Pylon::CImageFormatConverter;

namespace scs
{
	class SCS_API BalserCamera : public Camera
	{
	public:
#pragma region Constructor
		BalserCamera();
		~BalserCamera();
#pragma endregion

		
#pragma region Public Function
		bool open(int index) override;
		void close() override;
		bool image(Mat & im) override;
#pragma endregion	

	private:

#pragma region Public Property
		PrivateMember(int, MaxNumBuffer, MaxNumBuffer > 0);
		PrivateMember(EGrabStrategy, GrabStrategy, true);
#pragma endregion

		
#pragma region Private Member
		Pylon::CInstantCamera obj;
		CGrabResultPtr imgPtr;
		CPylonImage targetImage;
		CImageFormatConverter converter;
#pragma endregion

	private:
		static DeviceInfoList devices;
	};
}