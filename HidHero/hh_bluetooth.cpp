#include "hh_bluetooth.h"
#include "hh_devnode.h"

#include <stdio.h>
#include <stdlib.h>
#include <SetupAPI.h>
#include <ws2bth.h>
#include <cfgmgr32.h>
#include <bthioctl.h>

namespace hh
{
	uint64_t BluetoothDevice::get_address()
	{
		BTH_LOCAL_RADIO_INFO info;
		DWORD returned;
		if (!DeviceIoControl(h, IOCTL_BTH_GET_LOCAL_INFO, NULL, 0, (LPVOID)&info, sizeof(info), &returned, (LPOVERLAPPED)NULL))
		{
			return 0;
		}

		if (returned < sizeof(info))
		{
			return 0;
		}

		return info.localInfo.address;
	}

	std::vector<BluetoothDevice> Bluetooth::list()
	{
		GUID guid = GUID_BTHPORT_DEVICE_INTERFACE;

		std::vector<BluetoothDevice> devices;
		for (auto& handle : list_devices(&guid))
		{
			devices.push_back(BluetoothDevice(handle));
		}

		return devices;
	}
}