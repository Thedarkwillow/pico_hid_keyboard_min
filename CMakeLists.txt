cmake_minimum_required(VERSION 3.13)
set(PICO_SDK_FETCH_FROM_GIT ON)
include(${CMAKE_SOURCE_DIR}/pico_sdk_import.cmake)

project(pico_hid_keyboard_min C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(pico_hid_keyboard_min
  main.c
  usb_descriptors.c
)

# keep USB CDC off to avoid descriptor clashes; silent UART too
pico_enable_stdio_usb(pico_hid_keyboard_min 0)
pico_enable_stdio_uart(pico_hid_keyboard_min 0)

target_include_directories(pico_hid_keyboard_min PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# HID-only TinyUSB config
target_compile_definitions(pico_hid_keyboard_min PUBLIC
  CFG_TUSB_MCU=OPT_MCU_RP2040
  CFG_TUSB_RHPORT0_MODE=OPT_MODE_DEVICE
  CFG_TUD_HID=1
)

target_link_libraries(pico_hid_keyboard_min
  pico_stdlib
  tinyusb_device
  tinyusb_board
)

pico_add_extra_outputs(pico_hid_keyboard_min)
