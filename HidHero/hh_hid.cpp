#include "hh_hid.h"
#include "hh_devnode.h"

#include <stdio.h>
#include <stdlib.h>
#include <cfgmgr32.h>
#include <hidsdi.h>

namespace hh
{
	std::wstring HidDevice::get_product()
	{
		BOOLEAN success;
		WCHAR stringBuf[128];

		success = HidD_GetProductString(h, stringBuf, sizeof(stringBuf));
		return success ? std::wstring(stringBuf) : L"N/A";
	}

	std::wstring HidDevice::get_manufacturer()
	{
		BOOLEAN success;
		WCHAR stringBuf[128];

		success = HidD_GetManufacturerString(h, stringBuf, sizeof(stringBuf));
		return success ? std::wstring(stringBuf) : L"N/A";
	}

	std::wstring HidDevice::get_serial()
	{
		BOOLEAN success;
		WCHAR stringBuf[128];

		success = HidD_GetSerialNumberString(h, stringBuf, sizeof(stringBuf));
		return success ? std::wstring(stringBuf) : L"N/A";
	}

	std::vector<HidDevice> Hid::list()
	{
		GUID guid;
		HidD_GetHidGuid(&guid);

		std::vector<HidDevice> devices;
		for (auto& handle : list_devices(&guid))
		{
			devices.push_back(HidDevice(handle));
		}

		return devices;
	}
}