#include <iostream>
#include "hh_hid.h"

#define LOG(X) std::wcout << X << std::endl

//
// Lists all HID devices.
//
static void list_hid()
{
    LOG(L"Listing HID devices");
    for (auto device : hh::Hid::list())
    {
        LOG(L" -> Device");
        LOG(L"  -> Product= " << device.get_product());
        LOG(L"  -> Manufacturer= " << device.get_manufacturer());
        LOG(L"  -> Serial= " << device.get_serial());
    }
}

int main()
{
    list_hid();
    return 0;
}
