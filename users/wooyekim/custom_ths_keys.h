#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  const uint16_t keycode;
  const uint16_t tap;
  const uint16_t shift_tap;
  const uint16_t hold;
  const uint16_t shift_hold;

  bool layer_switched: 1;
  uint16_t registered;
} custom_ths_key_t;

#define CUSTOM_THS_KEY(_keycode, _tap, _shift_tap, _hold, _shift_hold) \
  (&(custom_ths_key_t){\
   .keycode = _keycode, \
   .tap = _tap, \
   .shift_tap = _shift_tap, \
   .hold = _hold, \
   .shift_hold = _shift_hold, \
   .layer_switched = false, \
   .registered = KC_NO, \
   })

#define CUSTOM_SHIFT_KEY(_keycode, _tap, _shift_tap) \
  CUSTOM_THS_KEY(_keycode, _tap, _shift_tap, KC_NO, KC_NO)

extern custom_ths_key_t** custom_ths_keys;
bool pre_process_custom_ths_keys(uint16_t keycode, keyrecord_t *record);
bool process_custom_ths_keys(uint16_t keycode, keyrecord_t *record);

#ifdef __cplusplus
}
#endif
