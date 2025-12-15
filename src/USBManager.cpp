#include "USBManager.h"
#include <windows.h>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

bool USBManager::isUSBDrive(char driveLetter) {
    std::string path = "";
    path += driveLetter;
    path += ":\\";
    UINT type = GetDriveTypeA(path.c_str());
    return type == DRIVE_REMOVABLE;
}

USBDevice USBManager::getDriveInfo(char driveLetter) {
    USBDevice dev{};
    dev.driveLetter = driveLetter;

    std::string root = "";
    root += driveLetter;
    root += ":\\";

    ULARGE_INTEGER freeBytesAvailable, totalBytes, freeBytes;

    if (GetDiskFreeSpaceExA(root.c_str(), &freeBytesAvailable, &totalBytes, &freeBytes)) {
        dev.totalSpaceGB = totalBytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
        dev.freeSpaceGB  = freeBytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
    } else {
        dev.totalSpaceGB = 0;
        dev.freeSpaceGB  = 0;
    }

    return dev;
}

std::vector<USBDevice> USBManager::detectUSBDevices() {
    std::vector<USBDevice> usbList;

    DWORD drives = GetLogicalDrives(); // Bitmask of available drives

    for (char c = 'A'; c <= 'Z'; c++) {
        if (drives & (1 << (c - 'A'))) {
            if (isUSBDrive(c)) {
                usbList.push_back(getDriveInfo(c));
            }
        }
    }

    return usbList;
}

void USBManager::listFiles(char driveLetter) {
    std::string path = std::string(1, driveLetter) + ":\\";
    
    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            std::cout << "Files on " << path << ":\n";
            for (const auto& entry : fs::directory_iterator(path)) {
                std::cout << " - " << entry.path().filename().string();
                if (fs::is_directory(entry.status())) {
                    std::cout << " [DIR]";
                }
                std::cout << "\n";
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error accessing drive: " << e.what() << "\n";
    }
}