#include "action.h"
#include "custom_oneshot_mods.h"
#include "os.h"
#include "keycode_config.h"
#include "print.h"

bool process_custom_oneshot_mods(uint16_t keycode, keyrecord_t *record) {
  bool is_osm_keycode = false;
  uint8_t mods;
  if (keycode == OS_LCTL_LCMD) {
    mods = !is_mac() ? MOD_LCTL : MOD_LGUI;
  } else if (keycode == OS_LWIN_LCTL) {
    mods = !is_mac() ? MOD_LGUI : MOD_LCTL;
  } else if (keycode == OS_RCTL_RCMD) {
    mods = !is_mac() ? MOD_RCTL : MOD_RGUI;
  } else if (keycode == OS_RWIN_RCTL) {
    mods = !is_mac() ? MOD_RGUI : MOD_RCTL;
  } else if (IS_QK_ONE_SHOT_MOD(keycode)) {
    is_osm_keycode = true;
  } else {
    return true;
  }
#ifdef ONESHOT_TAP_TOGGLE
  if (record->tap.count > ONESHOT_TAP_TOGGLE) {
    if (record->event.pressed) {
      clear_mods();
      clear_weak_mods();
      clear_oneshot_mods();
      clear_oneshot_locked_mods();
    }
    return false;
  }
#endif  // ONESHOT_TAP_TOGGLE
  if (is_osm_keycode) {
    return true;
  }
  action_t action = action_for_keycode(OSM(mods));
  process_action(record, action);
  return false;
}
