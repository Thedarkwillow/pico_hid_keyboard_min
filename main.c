#include "pico/stdlib.h"
#include "bsp/board_api.h"
#include "tusb.h"

static uint32_t last_ms = 0;

int main(void) {
  board_init();
  tusb_init();

  while (true) {
    tud_task(); // tinyusb device task

    uint32_t now = board_millis();
    if (tud_mounted() && (now - last_ms) > 1500) {
      last_ms = now;
      // press and release 'a' (HID keycode 0x04)
      uint8_t kc[6] = {0};
      kc[0] = 0x04;
      tud_hid_keyboard_report(0, 0, kc);
      sleep_ms(20);
      tud_hid_keyboard_report(0, 0, NULL);
    }
  }
  return 0;
}

// Required, minimal stubs
void tud_mount_cb(void) {}
void tud_umount_cb(void) {}
void tud_suspend_cb(bool remote_wakeup_en) { (void)remote_wakeup_en; }
void tud_resume_cb(void) {}
uint16_t tud_hid_get_poll_interval_cb(uint8_t instance) { (void)instance; return 10; }
