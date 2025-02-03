#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#define OS_LSFT      OSM(MOD_LSFT)
#define OS_LCTL      OSM(MOD_LCTL)
#define OS_LALT      OSM(MOD_LALT)
#define OS_LGUI      OSM(MOD_LGUI)
#define OS_LCTL_LCMD MT(MOD_LCTL, KC_LCTL)  // LCTL on Windows, LCMD on Mac
#define OS_LWIN_LCTL MT(MOD_LGUI, KC_LGUI)  // LWIN on Windows, LCTL on Mac
#define OS_RSFT      OSM(MOD_RSFT)
#define OS_RCTL      OSM(MOD_RCTL)
#define OS_RALT      OSM(MOD_RALT)
#define OS_RGUI      OSM(MOD_RGUI)
#define OS_RCTL_RCMD MT(MOD_RCTL, KC_RCTL)  // RCTL on Windows, RCMD on Mac
#define OS_RWIN_RCTL MT(MOD_RGUI, KC_RGUI)  // RWIN on Windows, RCTL on Mac

bool process_custom_oneshot_mods(uint16_t keycode, keyrecord_t *record);

#ifdef __cplusplus
}
#endif // __cplusplus
