#pragma once
#include "Camera.h"
#include <jai_factory.h>
#include <vector>
using std::vector;

namespace scs
{
	class JAICamera : public Camera
	{
	public:
#pragma region Constructor
		JAICamera();
		~JAICamera();
#pragma endregion

#pragma region Public Functions
		bool open(int index) override;
		void close() override;
		bool image(Mat & im) override;
#pragma endregion

	private:
#pragma region Private Member
		CAM_HANDLE obj;
#pragma endregion

#pragma region Private Static Member
		static FACTORY_HANDLE factory;
		static uint32_t nCameras;
		static vector<int8_t[J_CAMERA_ID_SIZE]> IDs;
#pragma endregion


	};
}