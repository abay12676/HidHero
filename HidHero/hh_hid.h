#pragma once
#include <Windows.h>
#include <vector>
#include <string>

namespace hh
{
	//
	// A small wrapper around a hid handle.
	//
	class HidDevice
	{
	private:
		HANDLE h;
		
	public:
		__forceinline HidDevice(HANDLE h)
		{
			this->h = h;
		}

	public:
		//
		// Retrieves the product name associated with this device.
		//
		std::wstring get_product();
		//
		// Retrieves the manufacturer associated with this device.
		//
		std::wstring get_manufacturer();
		//
		// Retrieves the serial associated with this device.
		//
		std::wstring get_serial();

		//
		// Closes this device.
		//
		__forceinline void close() 
		{
			CloseHandle(h);
			h = NULL;
		}
	};

	class Hid
	{
	public:
		//
		// Lists all available HID devices.
		//
		static std::vector<HidDevice> list();
	};
}