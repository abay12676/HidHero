#include "hh_devnode.h"

namespace hh
{

	std::vector<HANDLE> list_devices(GUID* guid)
	{
		CONFIGRET status = CR_SUCCESS;
		PWSTR deviceInterfaceList = NULL;
		ULONG deviceInterfaceListLength = 0;
		PWSTR currentInterface;
		HANDLE deviceHandle = INVALID_HANDLE_VALUE;
		WCHAR stringBuf[128];
		std::vector<HANDLE> devices;

		status = CM_Get_Device_Interface_List_Size(&deviceInterfaceListLength, guid, NULL, CM_GET_DEVICE_INTERFACE_LIST_PRESENT);
		if (status != CR_SUCCESS)
		{
			goto ret;
		}

		if (deviceInterfaceListLength <= 1)
		{
			goto ret;
		}

		deviceInterfaceList = (PWSTR)malloc(deviceInterfaceListLength * sizeof(WCHAR));
		if (deviceInterfaceList == NULL)
		{
			goto ret;
		}

		ZeroMemory(deviceInterfaceList, deviceInterfaceListLength * sizeof(WCHAR));

		status = CM_Get_Device_Interface_List(guid, NULL, deviceInterfaceList, deviceInterfaceListLength, CM_GET_DEVICE_INTERFACE_LIST_PRESENT);
		if (status != CR_SUCCESS)
		{
			goto ret;
		}

		for (currentInterface = deviceInterfaceList; *currentInterface; currentInterface += wcslen(currentInterface) + 1)
		{
			deviceHandle = CreateFile(currentInterface, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
			if (deviceHandle == INVALID_HANDLE_VALUE)
			{
				continue;
			}

			devices.push_back(deviceHandle);
		}

	ret:
		if (deviceInterfaceList)
		{
			free(deviceInterfaceList);
		}

		return devices;
	}
}