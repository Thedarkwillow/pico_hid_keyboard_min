#include "tusb.h"
#include <string.h>

#define USB_VID 0xCafe
#define USB_PID 0x4000
#define USB_BCD 0x0200

enum { ITF_NUM_HID, ITF_COUNT };
#define EPNUM_HID   0x81

// HID report: standard keyboard
uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD()
};

// Device descriptor
tusb_desc_device_t const desc_device = {
  .bLength            = sizeof(tusb_desc_device_t),
  .bDescriptorType    = TUSB_DESC_DEVICE,
  .bcdUSB             = USB_BCD,
  .bDeviceClass       = 0x00,
  .bDeviceSubClass    = 0x00,
  .bDeviceProtocol    = 0x00,
  .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

  .idVendor           = USB_VID,
  .idProduct          = USB_PID,
  .bcdDevice          = 0x0100,

  .iManufacturer      = 0x01,
  .iProduct           = 0x02,
  .iSerialNumber      = 0x03,

  .bNumConfigurations = 0x01
};

uint8_t const * tud_descriptor_device_cb(void) {
  return (uint8_t const *) &desc_device;
}

// Configuration descriptor (1 config, 1 HID interface)
#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)
uint8_t const desc_configuration[] = {
  TUD_CONFIG_DESCRIPTOR(1, ITF_COUNT, 0, CONFIG_TOTAL_LEN, 0x00, 100),
  TUD_HID_DESCRIPTOR(ITF_NUM_HID, 0, HID_ITF_PROTOCOL_KEYBOARD,
                     sizeof(desc_hid_report), EPNUM_HID, 8, 10)
};

uint8_t const * tud_descriptor_configuration_cb(uint8_t index) {
  (void) index;
  return desc_configuration;
}

// Strings
char const* string_desc_arr[] = {
  (const char[]){ 0x09, 0x04 }, // 0: English (0x0409)
  "TinyKey Co",                 // 1: Manufacturer
  "Pico HID Keyboard",          // 2: Product
  "123456",                     // 3: Serial
};

static uint16_t _desc_str[32];

uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
  (void) langid;

  if (index == 0) {
    _desc_str[1] = 0x0409;
    _desc_str[0] = (TUSB_DESC_STRING << 8) | (2*1 + 2);
    return _desc_str;
  }

  if (index >= sizeof(string_desc_arr)/sizeof(string_desc_arr[0])) return NULL;

  const char* str = string_desc_arr[index];
  uint8_t chr_count = (uint8_t) strlen(str);
  if (chr_count > 31) chr_count = 31;
  for (uint8_t i = 0; i < chr_count; i++) {
    _desc_str[1 + i] = str[i];
  }
  _desc_str[0] = (TUSB_DESC_STRING << 8) | (2*chr_count + 2);
  return _desc_str;
}

// Optional HID callbacks (empty implementations)
uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id,
                               hid_report_type_t report_type,
                               uint8_t* buffer, uint16_t reqlen) {
  (void)itf; (void)report_id; (void)report_type; (void)buffer; (void)reqlen;
  return 0;
}

void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id,
                           hid_report_type_t report_type,
                           uint8_t const* buffer, uint16_t bufsize) {
  (void)itf; (void)report_id; (void)report_type; (void)buffer; (void)bufsize;
}
