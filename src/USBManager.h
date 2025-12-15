#ifndef USB_MANAGER_H
#define USB_MANAGER_H

#include <vector>
#include <string>

struct USBDevice {
    char driveLetter;                // example drive name E, F, G etc.
    double totalSpaceGB; // total space in GB
    double freeSpaceGB;  // available free space in GB
};

class USBManager {
public:
    // here it shoult detect all USB devices connected to the system
    std::vector<USBDevice> detectUSBDevices();
    void listFiles(char driveLetter);

private:
    bool isUSBDrive(char driveLetter);
    USBDevice getDriveInfo(char driveLetter);
};

#endif
