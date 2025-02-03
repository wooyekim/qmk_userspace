#include "send_string.h"
#include "quantum/send_string/send_string.h"
#include "quantum/send_string/send_string_keycodes.h"

bool process_send_string_map(uint16_t keycode, keyrecord_t *record) {
  uint8_t idx = 0;
  const send_string_t* entry;
  while (true) {
    entry = send_string_map[idx++];
    if (entry == NULL) {
      return true;
    }
    if (entry->keycode == keycode) {
      break;
    }
  }
  if (record->event.pressed) {
    SEND_STRING_DELAY(entry->str, 10 /* ms */);
  }
  return false;
}
