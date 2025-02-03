#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef struct {
  const uint16_t *pattern;
  const char *str;
} auto_completion_pattern_t;

#define AUTO_COMPLETION_PATTERN(_pattern, _str) \
  &(const auto_completion_pattern_t){ \
    .pattern = _pattern, \
    .str = _str, \
  }

extern const auto_completion_pattern_t** auto_completion_patterns;
void initialize_auto_completion(void);
bool process_auto_completion(uint16_t keycode, keyrecord_t *record,
    uint16_t completion_keycode);

#ifdef __cplusplus
}
#endif // __cplusplus
