#include <iostream>

#include "hh_bluetooth.h"
#include "hh_hid.h"

#define LOG(X) std::wcout << X << std::endl

//
// Lists all HID devices.
//
static void list_hid()
{
    LOG(L"Listing HID devices");
    for (auto& device : hh::Hid::list())
    {
        LOG(L" -> Device");
        LOG(L"  -> Product= " << device.get_product());
        LOG(L"  -> Manufacturer= " << device.get_manufacturer());
        LOG(L"  -> Serial= " << device.get_serial());
        device.close();
    }

    LOG(L"Listing bluetooth devices");
    for (auto& device : hh::Bluetooth::list())
    {
        LOG(L" -> Device");
        LOG(L"  -> Address= " << std::hex << device.get_address());
        device.close();
    }
}

int main()
{
    list_hid();
    std::cin.get();
    return 0;
}
