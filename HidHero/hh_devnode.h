#include <Windows.h>
#include <cfgmgr32.h>

#include <cstdint>
#include <vector>

namespace hh
{
	//
	// Opens a handle to all devices with the provided guid.
	//
	std::vector<HANDLE> list_devices(GUID* guid);
}