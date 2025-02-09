/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keymap_korean.h"
#include "users/wooyekim/os.h"
#include "users/wooyekim/custom_ths_keys.h"

enum planck_layers {
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

#define SPC_SFT LSFT_T(KC_SPC)
#define SPC_NUM LT(LAYER_NUM, KC_SPC)
#define ENT_SFT RSFT_T(KC_ENT)
#define ENT_NUM LT(LAYER_NUM, KC_ENT)
#define UDS_CTL LCTL_T(KC_UNDS)
#define TAB_CTL LCTL_T(KC_TAB)
#define TAB_NAV LT(LAYER_NAV, KC_TAB)
#define BSP_CTL RCTL_T(KC_BSPC)
#define LBR_SFT LSFT_T(KC_LBRC)
#define RBR_SFT RSFT_T(KC_RBRC)
#define NAV     MO(LAYER_NAV)
#define NUM     MO(LAYER_NUM)
#define COLEMAK DF(LAYER_COLEMAK)
#define QWERTY  DF(LAYER_QWERTY)
#define __HLD__ _______

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   ;  | "/'  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |_/Ctrl|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   P  |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | [/Sft|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | ]/Sft|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  (   |   ~  | Meta | Alt  |TabNav|SpcNum|EntSft|BspCtl|Hangul| Hanja|   \  |  )   |
 * `-----------------------------------------------------------------------------------'
 */
[LAYER_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_SCLN, KC_DQUO,
    UDS_CTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_P,    KC_EQL,
    LBR_SFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RBR_SFT,
    KC_LPRN, TLD_GRV, KC_LGUI, KC_LALT, TAB_NAV, SPC_NUM, ENT_SFT, BSP_CTL, SC_HAEN, SC_HANJ, KC_BSLS, KC_RPRN
),

/* Tarmak-DH 4
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   F  |   P  |   B  |   J  |   U  |   I  |   Y  |   ;  | "/'  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |_/Ctrl|   A  |   R  |   S  |   T  |   G  |   M  |   N  |   E  |   L  |   O  |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | [/Sft|   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |   /  | ]/Sft|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  (   |   ~  | Meta | Alt  |TabNav|SpcNum|EntSft|BspCtl|Hangul| Hanja|   \  |  )   |
 * `-----------------------------------------------------------------------------------'
 */
[LAYER_COLEMAK] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_U,    KC_I,    KC_Y,    KC_SCLN, KC_DQUO,
    UDS_CTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_L,    KC_O,    KC_EQL,
    LBR_SFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, RBR_SFT,
    KC_LPRN, TLD_GRV, KC_LGUI, KC_LALT, TAB_NAV, SPC_NUM, ENT_SFT, BSP_CTL, SC_HAEN, SC_HANJ, KC_BSLS, KC_RPRN
),

/* Number 
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  -   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  +   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  {   |      |      |      |      |      |      |      |   <  |   >  |   ?  |  }   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  (   |   `  | Meta | Alt  |Adjust| Hold |      | Bksp |      |      |   |  |  )   |
 * `-----------------------------------------------------------------------------------'
 */
[LAYER_NUM] = LAYOUT_planck_grid(
    XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_QUOT,
    KC_MINS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PLUS,
    KC_LCBR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LT,   KC_GT,   KC_QUES, KC_RCBR,
    KC_LPRN, KC_GRV,  KC_LGUI, KC_LALT, _______, __HLD__, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, KC_RPRN
),

/* Navigation
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * `-----------------------------------------------------------------------------------'
 * |      | Meta | Alt  | Ctrl | Shift|      | Left | Down |  Up  | Right|      |      |
 * `-----------------------------------------------------------------------------------'
 * |      |      | OS   | Qwty | Clmk |      | Home | PgDn | PgUp | End  |      |      |
 * `-----------------------------------------------------------------------------------'
 * |      |      |      |      | Hold |Adjust| Enter| Bksp |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[LAYER_NAV] = LAYOUT_planck_grid(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, SWAP_OS, QWERTY,  COLEMAK, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, __HLD__, _______, KC_ENT,  KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | Hold | Hold |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[LAYER_ADJUST] = LAYOUT_planck_grid(
    XXXXXXX, RESET,   DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, __HLD__, __HLD__, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)

};

combo_t key_combos[] = {};

#define PROCESS_FN(fn, ...) \
  if (!fn(__VA_ARGS__)) { \
    return false; \
  }

bool process_haen(uint16_t keycode, keyrecord_t *record) {
  if (keycode == SC_HAEN && (get_mods() & MOD_MASK_SHIFT) == 0 &&
      record->event.pressed) {
    uprintf("default_layer_state: 0x%04x(%d)\n",
        default_layer_state, get_highest_layer(default_layer_state));
    if (get_highest_layer(default_layer_state) == LAYER_COLEMAK) {
      default_layer_set(1 << LAYER_QWERTY);
    } else {
      default_layer_set(1 << LAYER_COLEMAK);
    }
  }
  return true;
}

const os_variant_key_t** os_variant_keys = (const os_variant_key_t*[]){
  OS_VARIANT_KEY(SC_HAEN, KR_HAEN, LGUI(KC_SPC)),
  OS_VARIANT_KEY(SC_HANJ, KR_HANJ, LOPT(KC_ENT)),
  NULL
};

custom_ths_key_t** custom_ths_keys = (custom_ths_key_t*[]){
  CUSTOM_SHIFT_KEY(KC_BSPC, KC_BSPC, KC_DEL),
  CUSTOM_SHIFT_KEY(KC_DQUO, KC_DQUO, KC_QUOT),
  CUSTOM_SHIFT_KEY(UDS_CTL, KC_UNDS, KC_MINS),
  CUSTOM_SHIFT_KEY(TLD_GRV, KC_TILD, KC_GRV),
  NULL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uprintf("kc: 0x%04x / pressed: %d / tap.count: %d\n",
      keycode, record->event.pressed, record->tap.count);
  PROCESS_FN(process_haen, keycode, record);
  PROCESS_FN(process_os_variant_keys, keycode, record, SWAP_OS);
  PROCESS_FN(process_custom_ths_keys, keycode, record);
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, LAYER_NUM, LAYER_NAV, LAYER_ADJUST);
}

