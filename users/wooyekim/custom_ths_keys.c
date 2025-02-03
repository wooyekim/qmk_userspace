#include "custom_ths_keys.h"
#include "layer_lock.h"

custom_ths_key_t* find_config(uint16_t keycode) {
  uint8_t i = 0;
  while (true) {
    custom_ths_key_t* config = custom_ths_keys[i++];
    if (config == NULL || config->keycode == keycode) {
      return config;
    }
  }
  // Should never reach here
  return NULL;
}

uint16_t coalesce(uint16_t a, uint16_t b) {
  return a == 0 ? b : a;
}

bool process_custom_ths_keys(uint16_t keycode, keyrecord_t *record) {
  if (IS_QK_MOD_TAP(keycode) && record->tap.count == 0) {
    return true;
  }
  // Overrides layer 0 only
  bool is_hold = false;
  if (IS_QK_LAYER_TAP(keycode) && record->tap.count == 0) {
    if (QK_LAYER_TAP_GET_LAYER(keycode) > 0) {
      return true;
    }
    is_hold = true;
  }
  custom_ths_key_t* config = find_config(keycode);
  if (config == NULL) {
    return true;
  }
  uint8_t mods = get_mods();
  bool shifted = (mods |
      get_weak_mods() |
      get_oneshot_mods() |
      get_oneshot_locked_mods()) &
    MOD_MASK_SHIFT;
  dprintf("mods: 0x%02x / shifted: %d\n", mods, shifted);
  if (record->event.pressed) {
    if (shifted) {
      unregister_mods(MOD_MASK_SHIFT);
      del_weak_mods(MOD_MASK_SHIFT);
      del_oneshot_mods(MOD_MASK_SHIFT);
      if (is_hold && config->shift_hold != KC_NO) {
        config->registered = config->shift_hold;
      } else {
        config->registered = config->shift_tap;
      }
    } else {
      if (is_hold && config->hold != KC_NO) {
        config->registered = config->hold;
      } else {
        config->registered = config->tap;
      }
    }
    register_code16(config->registered);
    set_mods(mods);
    clear_weak_mods();
    clear_oneshot_mods();
  } else {
    unregister_code16(config->registered);
    config->registered = KC_NO;
  }
  return false;
}
