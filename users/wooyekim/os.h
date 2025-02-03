#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef struct {
  const uint16_t keycode;
  const uint16_t default_keycode;
  const uint16_t mac_keycode;
} os_variant_key_t;

#define OS_VARIANT_KEY(_keycode, _default_keycode, _mac_keycode) \
  &((os_variant_key_t){ \
    .keycode = _keycode, \
    .default_keycode = _default_keycode, \
    .mac_keycode = _mac_keycode, \
  })

extern const os_variant_key_t **os_variant_keys;

bool is_mac(void);
bool process_os_variant_keys(uint16_t keycode, keyrecord_t *record, uint16_t os_swap_keycode);

#ifdef __cplusplus
}
#endif // __cplusplus
