#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef struct {
  const uint16_t keycode;
  const char *str;
} send_string_t;

#define SEND_STRING_ENTRY(_keycode, _str) \
  &((send_string_t){ \
    .keycode = _keycode, \
    .str = _str, \
  })

extern const send_string_t **send_string_map;

bool process_send_string_map(uint16_t keycode, keyrecord_t *record);

#ifdef __cplusplus
}
#endif // __cplusplus
