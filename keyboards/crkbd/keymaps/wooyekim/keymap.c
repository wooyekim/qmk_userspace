/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap_korean.h"
#include "users/wooyekim/os.h"
#include "users/wooyekim/custom_ths_keys.h"

enum crkbd_layers {
  LAYER_COLEMAK,
  LAYER_QWERTY,
  LAYER_NUM,
  LAYER_NAV,
  LAYER_ADJUST,
};

enum custom_keycodes {
  // Change OS
  SWAP_OS = SAFE_RANGE,
  // Shortcuts
  SC_HAEN,
  SC_HANJ,
};

#define NUM      MO(LAYER_NUM)
#define NAV      MO(LAYER_NAV)
#define ADJUST   MO(LAYER_ADJUST)
#define SPC_LSFT LSFT_T(KC_SPC)
#define ENT_RSFT RSFT_T(KC_ENT)
#define GRV_CTL  LCTL_T(KC_GRV)
#define TAB_CTL  LCTL_T(KC_TAB)
#define UDS_CTL  LCTL_T(KC_UNDS)
#define QTY_LALT LALT_T(KC_0)
#define CMK_LALT LALT_T(KC_1)
#define __HLD__ _______

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_QWERTY] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,QTY_LALT,   CMK_LALT,    KC_Y,    KC_U,    KC_I,    KC_O, KC_SCLN,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------|--------+--------+--------+--------+--------+--------|
      TAB_CTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_LGUI,    SC_HAEN,    KC_H,    KC_J,    KC_K,    KC_L,    KC_P, UDS_CTL,
  //|--------+--------+--------+--------+--------+--------|--------'  `--------|--------+--------+--------+--------+--------+--------|
      KC_LBRC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RBRC,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                              NUM,SPC_LSFT, KC_DQUO,    KC_BSPC,ENT_RSFT,     NAV
                                      //`--------------------------'  `--------------------------'
  ),

    [LAYER_COLEMAK] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,QTY_LALT,   CMK_LALT,    KC_J,    KC_U,    KC_I,    KC_Y, KC_SCLN,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------|--------+--------+--------+--------+--------+--------|
      TAB_CTL,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G, KC_LGUI,    SC_HAEN,    KC_M,    KC_N,    KC_E,    KC_L,    KC_O, UDS_CTL,
  //|--------+--------+--------+--------+--------+--------|--------'  `--------|--------+--------+--------+--------+--------+--------|
      KC_LBRC,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_RBRC,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                              NUM,SPC_LSFT, KC_DQUO,    KC_BSPC,ENT_RSFT,     NAV
                                      //`--------------------------'  `--------------------------'
  ),

    [LAYER_NUM] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,QTY_LALT,   CMK_LALT, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------|--------+--------+--------+--------+--------+--------|
      GRV_CTL,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_LGUI,    SC_HAEN,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|--------'  `--------|--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                              NUM,SPC_LSFT, KC_DQUO,    KC_BSPC,ENT_RSFT,     NAV
                                      //`--------------------------'  `--------------------------'
  ),

    [LAYER_NAV] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  QTY_LALT,   CMK_LALT,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------|--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI,    SC_HAEN, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, KC_F11,
  //|--------+--------+--------+--------+--------+--------|--------'  `--------|--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, SWAP_OS, XXXXXXX, XXXXXXX, SC_HANJ,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, KC_F12,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                              NUM,SPC_LSFT, KC_DQUO,    KC_BSPC,ENT_RSFT,     NAV
                                      //`--------------------------'  `--------------------------'
  ),

    [LAYER_ADJUST] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,QTY_LALT,   CMK_LALT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------|--------+--------+--------+--------+--------+--------|
      KC_LCTL, RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, KC_LGUI,    SC_HAEN, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|--------'  `--------|--------+--------+--------+--------+--------+--------|
      XXXXXXX, RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              NUM,SPC_LSFT, KC_DQUO,    KC_BSPC,ENT_RSFT,     NAV
                                      //`--------------------------'  `--------------------------'
  )
};

combo_t key_combos[] = {};

#define PROCESS_FN(fn, ...) \
  if (!fn(__VA_ARGS__)) { \
    return false; \
  }

void toggle_qwerty_colemak(void) {
  uprintf("default_layer_state: 0x%04x(%d)\n",
          default_layer_state, get_highest_layer(default_layer_state));
  if (get_highest_layer(default_layer_state) == LAYER_COLEMAK) {
    default_layer_set(1 << LAYER_QWERTY);
  } else {
    default_layer_set(1 << LAYER_COLEMAK);
  }
}

bool process_haen(uint16_t keycode, keyrecord_t *record) {
  if (keycode == SC_HAEN && (get_mods() & MOD_MASK_SHIFT) == 0 &&
      record->event.pressed) {
    toggle_qwerty_colemak();
  }
  // Always pass through
  return true;
}

bool process_default_layer2(uint16_t keycode, keyrecord_t *record) {
  if (IS_QK_MOD_TAP(keycode) && record->tap.count == 0) {
    return true;
  }
  if (keycode == QTY_LALT) {
    default_layer_set(1 << LAYER_QWERTY);
    return false;
  }
  if (keycode == CMK_LALT) {
    default_layer_set(1 << LAYER_COLEMAK);
    return false;
  }
  return true;
}

const os_variant_key_t** os_variant_keys = (const os_variant_key_t*[]){
  OS_VARIANT_KEY(SC_HAEN, KR_HAEN, LGUI(KC_SPC)),
  OS_VARIANT_KEY(SC_HANJ, KR_HANJ, LOPT(KC_ENT)),
  NULL
};

custom_ths_key_t** custom_ths_keys = (custom_ths_key_t*[]){
  CUSTOM_SHIFT_KEY(KC_BSPC,  KC_BSPC, KC_DEL),
  CUSTOM_SHIFT_KEY(KC_DQUO,  KC_DQUO, KC_QUOT),
  CUSTOM_SHIFT_KEY(UDS_CTL,  KC_UNDS, KC_MINS),
  NULL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uprintf("kc: 0x%04x / pressed: %d / tap.count: %d\n",
      keycode, record->event.pressed, record->tap.count);
  PROCESS_FN(process_haen, keycode, record);
  PROCESS_FN(process_os_variant_keys, keycode, record, SWAP_OS);
  PROCESS_FN(process_custom_ths_keys, keycode, record);
  PROCESS_FN(process_default_layer2, keycode, record);
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, LAYER_NUM, LAYER_NAV, LAYER_ADJUST);
    return state;
}
