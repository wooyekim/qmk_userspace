#include "os.h"
#include "os_detection.h"

bool os_swapped = false;

bool is_detected_os_mac(void) {
  switch (detected_host_os()) {
    case OS_MACOS:
    case OS_IOS:
      return true;
    default:
      return false;
  }
}

bool is_mac(void) {
  return is_detected_os_mac() ^ os_swapped;
}

bool process_os_variant_keys(uint16_t keycode, keyrecord_t *record, uint16_t os_swap_keycode) {
  if (!IS_USER_KEYCODE(keycode)) {
    return true;
  }
  if (keycode == os_swap_keycode && os_swap_keycode != KC_NO && record->event.pressed) {
    os_swapped = !os_swapped;
    return false;
  }
  const os_variant_key_t* config;
  int i = 0;
  while (true) {
    config = os_variant_keys[i++];
    if (config == NULL) {
      return true;
    }
    if (config->keycode == keycode) {
      break;
    }
  }
  keycode = is_mac() ? config->mac_keycode : config->default_keycode;
  if (record->event.pressed) {
    register_code16(keycode);
  } else {
    unregister_code16(keycode);
  }
  return false;
}

