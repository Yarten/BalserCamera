#include "JAICamera.h"
using namespace scs;

static int jai_camera_counter = 0;

FACTORY_HANDLE JAICamera::factory;
uint32_t JAICamera::nCameras = 0;
vector<int8_t[J_CAMERA_ID_SIZE]> JAICamera::IDs;

scs::JAICamera::JAICamera()
{
	if (++jai_camera_counter == 1)
	{
		J_STATUS_TYPE retval;
		retval = J_Factory_Open("", &factory);
		if (retval == J_ST_SUCCESS)
		{
			bool8_t hasChanged;
			retval = J_Factory_UpdateCameraList(factory, &hasChanged);
			if (retval == J_ST_SUCCESS && hasChanged)
			{
				retval = J_Factory_GetNumOfCameras(factory, &nCameras);
				if (retval == J_ST_SUCCESS && nCameras > 0)
				{		
					for (uint32_t i = 0; i < nCameras; i++)
					{
						int8_t id[J_CAMERA_ID_SIZE];
						uint32_t size = sizeof(id);
						retval = J_Factory_GetCameraIDByIndex(factory, i, id, &size);
						if (retval == J_ST_SUCCESS)
						{
							IDs.push_back(id);
						}
					}
				}
			}
		}
	}
}

scs::JAICamera::~JAICamera()
{
	close();

	if (--jai_camera_counter == 0)
	{
		J_Factory_Close(factory);
	}
}

bool scs::JAICamera::open(int index)
{
	if (index < 0 || index >= nCameras) return false;

	J_STATUS_TYPE retval;
	retval = J_Camera_Open(factory, IDs[index], &obj);

	if (retval == J_ST_SUCCESS)
	{
		// Set some values
		return true;
	}
	else return false;
}

void scs::JAICamera::close()
{
	J_Camera_Close(obj);
}

bool scs::JAICamera::image(Mat & im)
{
	return false;
}
