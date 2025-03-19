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
  // Misc
  TLD_GRV,
};

#define NUM     MO(LAYER_NUM)
#define NAV     MO(LAYER_NAV)
#define ADJUST  MO(LAYER_ADJUST)
#define COLEMAK DF(LAYER_COLEMAK)
#define QWERTY  DF(LAYER_QWERTY)
#define __HLD__ _______

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_QWERTY] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      TLD_GRV,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_ESC,    KC_LALT,    KC_Y,    KC_U,    KC_I,    KC_O, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------|--------+--------+--------+--------+--------+--------|
      KC_UNDS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_TAB,    KC_LGUI,    KC_H,    KC_J,    KC_K,    KC_L,    KC_P,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------|--------'  `--------|--------+--------+--------+--------+--------+--------|
      KC_BSLS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_DQUO,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                              NAV,     NUM,  KC_SPC,     KC_ENT, KC_LSFT, KC_LCTL
                                      //`--------------------------'  `--------------------------'
  ),

    [LAYER_COLEMAK] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      TLD_GRV,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,  KC_ESC,    KC_LALT,    KC_J,    KC_U,    KC_I,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------|--------+--------+--------+--------+--------+--------|
      KC_UNDS,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,  KC_TAB,    KC_LGUI,    KC_M,    KC_N,    KC_E,    KC_L,    KC_O,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------|--------'  `--------|--------+--------+--------+--------+--------+--------|
      KC_BSLS,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_DQUO,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                              NAV,     NUM,  KC_SPC,     KC_ENT, KC_LSFT, KC_LCTL
                                      //`--------------------------'  `--------------------------'
  ),

    [LAYER_NUM] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_GRV, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,  KC_ESC,    KC_LALT, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------|--------+--------+--------+--------+--------+--------|
      KC_MINS,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  KC_TAB,    KC_LGUI,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_PLUS,
  //|--------+--------+--------+--------+--------+--------|--------'  `--------|--------+--------+--------+--------+--------+--------|
      KC_PIPE, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, XXXXXXX,                      XXXXXXX, XXXXXXX,   KC_LT,   KC_GT, KC_QUES, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                           ADJUST, __HLD__,  KC_SPC,     KC_ENT, KC_LSFT, KC_LCTL
                                      //`--------------------------'  `--------------------------'
  ),


    [LAYER_NAV] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_ESC,    KC_LALT,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------|--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SC_HANJ,  KC_TAB,    KC_LGUI, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,  KC_F11,
  //|--------+--------+--------+--------+--------+--------|--------'  `--------|--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, SWAP_OS,  QWERTY, COLEMAK, SC_HAEN,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,  KC_F12,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          __HLD__,  ADJUST,  KC_SPC,     KC_ENT, KC_LSFT, KC_LCTL
                                      //`--------------------------'  `--------------------------'
  ),

    [LAYER_ADJUST] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------|--------+--------+--------+--------+--------+--------|
      RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|--------'  `--------|--------+--------+--------+--------+--------+--------|
      RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          __HLD__, __HLD__, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};

combo_t key_combos[] = {};
