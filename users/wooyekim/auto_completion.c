#include "auto_completion.h"
#include "quantum/send_string/send_string.h"
#include "quantum/send_string/send_string_keycodes.h"
#include "quantum_keycodes.h"
#include "print.h"

#include <string.h>

#ifndef AUTO_COMPLETION_LAST_KEYCODES_SIZE
  #define LAST_KEYCODES_SIZE 5
#else
  #define LAST_KEYCODES_SIZE AUTO_COMPLETION_LAST_KEYCODES_SIZE
#endif

#define KM_PATTERN "0x%04x(0x%02x)"

uint16_t last_keycodes[LAST_KEYCODES_SIZE];
uint8_t last_mods[LAST_KEYCODES_SIZE];
uint8_t next_keycode_index;  // Index to be stored in the next time

void initialize_auto_completion(void) {
  next_keycode_index = 0;
  memset(last_keycodes, 0, sizeof(last_keycodes));
  memset(last_mods, 0, sizeof(last_mods));
}

uint8_t next_last_keycodes_index(uint8_t idx) {
  return (idx + 1) % LAST_KEYCODES_SIZE;
}

void add_last_keycode(uint16_t keycode, uint8_t mods) {
  dprintf("lk[%d] = " KM_PATTERN "\n", next_keycode_index, keycode, mods);
  last_keycodes[next_keycode_index] = keycode;
  last_mods[next_keycode_index] = mods;
  next_keycode_index = next_last_keycodes_index(next_keycode_index);
}

bool last_keycodes_matches(const uint16_t pattern[]) {
  uint8_t p_i = 0;
  uint8_t pattern_size = 0;
  while (pattern[p_i] != KC_NO) {
    if (!IS_MODIFIER_KEYCODE(pattern[p_i])) {
      ++pattern_size;
    }
    ++p_i;
  }
  p_i = 0;
  uint8_t l_i = (LAST_KEYCODES_SIZE + next_keycode_index - pattern_size)
    % LAST_KEYCODES_SIZE;
  dprintf("Last keycodes start from %d\n", l_i);
  while (true) {
    uint16_t pk = pattern[p_i];
    uint8_t pm = 0;
    if (pk == KC_NO) {
      dprintf("Pattern matched\n");
      return true;
    }
    while (IS_MODIFIER_KEYCODE(pk)) {
      pm |= MOD_BIT(pk);
      pk = pattern[++p_i];
    }
    uint16_t lk = last_keycodes[l_i];
    uint8_t lm = last_mods[l_i];
    dprintf("Comparing p/l keycodes(mods) = " KM_PATTERN "/" KM_PATTERN "\n",
        pk, pm, lk, lm);
    if (pk != lk || pm != lm) {
      return false;
    }
    ++p_i;
    l_i = next_last_keycodes_index(l_i);
  }
}

void complete_auto_completion(void) {
  for (int i = 0; i < LAST_KEYCODES_SIZE ; ++i) {
    dprintf(KM_PATTERN "%s\n", last_keycodes[i], last_mods[i],
        i == next_keycode_index ? " <- next" : "");
  }
  const auto_completion_pattern_t *pattern = auto_completion_patterns[0];
  int i = 0;
  while (pattern != NULL) {
    dprintf("Comparing pattern #%d\n", i);
    if (last_keycodes_matches(pattern->pattern)) {
      SEND_STRING_DELAY(pattern->str, 10 /* ms */);
      break;
    }
    pattern = auto_completion_patterns[++i];
  }
  initialize_auto_completion();
}

bool process_auto_completion(uint16_t keycode, keyrecord_t *record,
    uint16_t completion_keycode) {
  if (!record->event.pressed) {
    // Do nothing on release
    return true;
  }
  if (keycode == completion_keycode) {
    complete_auto_completion();
    return false;
  }
  uint8_t mods = get_mods () |
      get_weak_mods() |
      get_oneshot_mods() |
      get_oneshot_locked_mods();
  uint16_t tap_keycode = keycode;
  if (IS_QK_MOD_TAP(keycode)) {
    if (record->tap.count == 0) {
      // Do nothing on mod-tap hold
      return true;
    }
    tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
  } else if (IS_QK_LAYER_TAP(keycode)) {
    if (record->tap.count == 0) {
      // Do nothing on layer-tap hold
      return true;
    }
    tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
  }
  if (!IS_BASIC_KEYCODE(tap_keycode) && !IS_QK_MODS(tap_keycode)) {
    // Not a basic keycode nor mod+basic keycode
    return true;
  }
  add_last_keycode(keycode, mods);
  return true;
}
