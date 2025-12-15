#include <windows.h>
#include <cstdio>
#include "USBManager.h"

USBManager usb;
HWND listBox;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {

    case WM_COMMAND:
        // Button ID = 1
        if (LOWORD(wParam) == 1) {

            // Clear list
            SendMessage(listBox, LB_RESETCONTENT, 0, 0);

            // Get USB drives
            auto drives = usb.detectUSBDevices();

            if (drives.empty()) {
                SendMessage(listBox, LB_ADDSTRING, 0,
                            (LPARAM)"No USB devices found");
            }

            for (auto& d : drives) {
                char text[64];
                sprintf(text, "%c: %.0f GB free / %.0f GB total",
                        d.driveLetter,
                        d.freeSpaceGB,
                        d.totalSpaceGB);

                SendMessage(listBox, LB_ADDSTRING, 0, (LPARAM)text);
            }
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {

    // Register window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "USB_GUI";

    RegisterClass(&wc);

    // Create main window
    HWND hwnd = CreateWindow(
        "USB_GUI",
        "USB Storage Tool",
        WS_OVERLAPPEDWINDOW,
        200, 200, 420, 320,
        NULL, NULL, hInst, NULL
    );

    // Button
    CreateWindow(
        "BUTTON",
        "List USB",
        WS_VISIBLE | WS_CHILD,
        20, 20, 100, 30,
        hwnd,
        (HMENU)1,
        hInst,
        NULL
    );

    // ListBox
    listBox = CreateWindow(
        "LISTBOX",
        "",
        WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY,
        20, 60, 360, 200,
        hwnd,
        NULL,
        hInst,
        NULL
    );

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
