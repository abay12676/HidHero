#pragma once
#include <Windows.h>
#include <vector>
#include <string>

namespace hh
{
	//
	// A small wrapper around a bluetooth device handle.
	//
	class BluetoothDevice
	{
	private:
		HANDLE h;

	public:
		__forceinline BluetoothDevice(HANDLE h)
		{
			this->h = h;
		}

	public:
		//
		// Retrieves the address associated with this device.
		//
		uint64_t get_address();

		//
		// Closes this device.
		//
		__forceinline void close()
		{
			CloseHandle(h);
			h = NULL;
		}
	};

	class Bluetooth
	{
	public:
		//
		// Lists all available bluetooth devices.
		//
		static std::vector<BluetoothDevice> list();
	};
}