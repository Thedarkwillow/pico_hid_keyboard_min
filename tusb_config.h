#pragma once
#define CFG_TUSB_MCU              OPT_MCU_RP2040
#define CFG_TUSB_OS               OPT_OS_PICO
#define BOARD_TUD_MAX_SPEED       OPT_MODE_DEFAULT_SPEED
#define CFG_TUSB_DEBUG            0

// Device mode config
#define CFG_TUD_ENABLED           1
#define CFG_TUSB_RHPORT0_MODE     (OPT_MODE_DEVICE)
#define CFG_TUD_ENDPOINT0_SIZE    64

// Enable only HID
#define CFG_TUD_HID               1
#define CFG_TUD_HID_EP_BUFSIZE    64

// Everything else off
#define CFG_TUD_CDC               0
#define CFG_TUD_MSC               0
#define CFG_TUD_MIDI              0
#define CFG_TUD_VENDOR            0
