cmake_minimum_required(VERSION 3.10)

project(usb_tool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ================= CONSOLE APP =================
add_executable(usb_console
        src/main.cpp
        src/USBManager.cpp
)

target_include_directories(usb_console PRIVATE src)

# ================= GUI APP =====================
add_executable(usb_gui
        src/main_gui.cpp
        src/USBManager.cpp
)

target_include_directories(usb_gui PRIVATE src)
