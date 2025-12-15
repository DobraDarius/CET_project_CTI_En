#include <iostream>
#include <string>
#include "USBManager.h"

void printHelp() {
    std::cout << "\nAvailable commands:\n";
    std::cout << "  list            -> List connected USB drives\n";
    std::cout << "  select <letter> -> Select a drive (e.g., select E)\n";
    std::cout << "  exit            -> Exit the program\n";
}

void printDriveHelp() {
    std::cout << "\nDrive Commands:\n";
    std::cout << "  ls              -> List files on this drive\n";
    std::cout << "  info            -> Show usage info (Free/Total)\n";
    std::cout << "  ..              -> Go back to main menu\n";
}

int main() {
    USBManager usbManager;
    std::string command;
    char selectedDrive = 0; 

    std::cout << "=== USB Storage Management Tool ===\n";
    std::cout << "Type 'help' for a list of commands.\n\n";

    while (true) {
        // here we display a prompt which resembles the terminal
        if (selectedDrive == 0) {
            std::cout << "USB-Tool > ";
        } else {
            std::cout << "USB-Tool (" << selectedDrive << ":) > ";
        }

        // 2. Read command
        std::cin >> command;

        // 3. Process command
        if (command == "exit") {
            std::cout << "Exiting application...\n";
            break; 
        } 
        else if (command == "help") {
            if (selectedDrive == 0) printHelp();
            else printDriveHelp();
        }
        else if (selectedDrive == 0) {
            // --- MAIN MENU COMMANDS ---
            if (command == "list") {
                auto devices = usbManager.detectUSBDevices();
                if (devices.empty()) {
                    std::cout << "No USB devices detected.\n";
                } else {
                    std::cout << "Connected Drives:\n";
                    for (auto& dev : devices) {
                        std::cout << " - Drive " << dev.driveLetter << ": (" 
                                  << dev.freeSpaceGB << " GB free / " 
                                  << dev.totalSpaceGB << " GB total)\n";
                    }
                }
            } 
            else if (command == "select") {
                char letter;
                std::cin >> letter; // Read the drive letter
                letter = toupper(letter); // Convert to uppercase
                
                // Simple validation could be added here
                selectedDrive = letter;
                std::cout << "Selected drive " << selectedDrive << "\n";
            }
            else {
                std::cout << "Unknown command. Try 'list' or 'select <letter>'.\n";
            }
        } 
        else {
            // --- DRIVE SPECIFIC COMMANDS ---
            if (command == "..") {
                selectedDrive = 0; // Return to main menu
                std::cout << "Returned to main menu.\n";
            }
            else if (command == "ls") {
                // Calls the function from Week 3
                usbManager.listFiles(selectedDrive);
            }
            else if (command == "info") {
                std::cout << "[Info feature in progress for drive " << selectedDrive << "]\n";
            }
            else {
                std::cout << "Unknown drive command. Try 'ls' or '..'.\n";
            }
        }
    }

    return 0;
}