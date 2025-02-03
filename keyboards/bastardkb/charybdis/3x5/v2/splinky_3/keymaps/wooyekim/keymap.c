/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#include "users/wooyekim/auto_completion.h"
#include "users/wooyekim/custom_oneshot_mods.h"
#include "users/wooyekim/custom_ths_keys.h"
#include "users/wooyekim/layer_lock.h"
#include "users/wooyekim/os.h"
#include "users/wooyekim/send_string.h"
#include "print.h"
#include "quantum/keymap_extras/keymap_korean.h"
#include "quantum/send_string/send_string.h"
#include "quantum/send_string/send_string_keycodes.h"

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
  #include "timer.h"
#endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_COLEMAK = 0,
    LAYER_QWERTY,
    LAYER_NUMBER,
    LAYER_EXTEND,
    LAYER_FUNCTION,
    LAYER_SYMBOL,
    LAYER_POINTER,
};

enum custom_keycodes {
  // Change OS
  SWAP_OS = SAFE_RANGE,
  // Shortcuts
  SC_UNDO,
  SC_REDO,
  SC_FIND,
  SC_CUT,
  SC_COPY,
  SC_PSTE,
  SC_SALL,
  SC_PREV,
  SC_NEXT,
  SC_UDIR,
  SC_HAEN,
  SC_HANJ,
  // Layer lock
  LA_LOCK,
  // Programming shortcuts
  C_ARROW,  // -> op
  // Auto completion key
  AT_COMP,
};

// Automatically enable sniping-mode on the pointer layer.
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define __HLD__ _______

#define UDS_PTR LT(LAYER_POINTER, KC_MINS)
#define Z_PTR   LT(LAYER_POINTER, KC_Z)
#define ESC_SYM LT(LAYER_SYMBOL, KC_ESC)
#define SPC_SFT LSFT_T(KC_SPC)
#define NUMBER  MO(LAYER_NUMBER)
#define TAB_NUM LT(LAYER_NUMBER, KC_TAB)
#define EXTEND  MO(LAYER_EXTEND)
#define BSP_EXT LT(LAYER_EXTEND, KC_BSPC)
#define ENT_SFT RSFT_T(KC_ENT)
#define COLEMAK DF(LAYER_COLEMAK)
#define QWERTY  DF(LAYER_QWERTY)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define DPI_RMOD KC_NO
#    define S_D_MOD KC_NO
#    define S_D_RMOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

/** Convenience row shorthands. */
#define __________HOME_ROW_MODS_L_________ OS_LWIN_LCTL, OS_LALT, OS_LSFT, OS_LCTL_LCMD
#define __________HOME_ROW_MODS_R_________ OS_LCTL_LCMD, OS_RSFT, OS_LALT, OS_LWIN_LCTL
#define _______________THUMB_CLUSTER_______________ \
       ESC_SYM, SPC_SFT, TAB_NUM, BSP_EXT, ENT_SFT

// clang-format off
#define LAYOUT_LAYER_QWERTY \
       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_DQUO, \
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_P, \
       Z_PTR,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  UDS_PTR, \
                         _______________THUMB_CLUSTER_______________

#define LAYOUT_LAYER_TARMAK_DH_1_A \
       KC_Q,    KC_W,    KC_J,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_DQUO, \
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_N,    KC_E,    KC_L,    KC_P, \
       Z_PTR,   KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  UDS_PTR, \
                         _______________THUMB_CLUSTER_______________

#define LAYOUT_LAYER_TARMAK_DH_1_B \
       KC_Q,    KC_W,    KC_J,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_DQUO, \
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_M,    KC_N,    KC_E,    KC_L,    KC_P, \
       Z_PTR,   KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_H,    KC_COMM, KC_DOT,  UDS_PTR, \
                         _______________THUMB_CLUSTER_______________

#define LAYOUT_LAYER_TARMAK_DH_2_A \
       KC_Q,    KC_W,    KC_J,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_DQUO, \
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_M,    KC_N,    KC_E,    KC_L,    KC_P, \
       Z_PTR,   KC_X,    KC_C,    KC_B,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  UDS_PTR, \
                         _______________THUMB_CLUSTER_______________

#define LAYOUT_LAYER_TARMAK_DH_2_B \
       KC_Q,    KC_W,    KC_F,    KC_R,    KC_B,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_DQUO, \
       KC_A,    KC_S,    KC_D,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_L,    KC_P, \
       Z_PTR,   KC_X,    KC_C,    KC_J,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  UDS_PTR, \
                         _______________THUMB_CLUSTER_______________

#define LAYOUT_LAYER_TARMAK_DH_3 \
       KC_Q,    KC_W,    KC_F,    KC_J,    KC_B,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_DQUO, \
       KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_L,    KC_P, \
       Z_PTR,   KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  UDS_PTR, \
                         _______________THUMB_CLUSTER_______________

#define LAYOUT_LAYER_TARMAK_DH_4 \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_U,    KC_I,    KC_Y,    KC_DQUO, \
       KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_L,    KC_O, \
       Z_PTR,   KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  UDS_PTR, \
                         _______________THUMB_CLUSTER_______________

#define LAYOUT_LAYER_COLEMAK_DH \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_DQUO, \
       KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O, \
       Z_PTR,   KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  UDS_PTR, \
                         _______________THUMB_CLUSTER_______________

#define LAYOUT_LAYER_COLEMAK LAYOUT_LAYER_TARMAK_DH_2_B

#define LAYOUT_LAYER_SYMBOL \
    KC_TILD, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_PIPE, KC_BSLS, KC_GRV, \
    KC_SCLN, KC_COLN, KC_LT,   KC_GT,   XXXXXXX, KC_ASTR, KC_LPRN, KC_LCBR, KC_LBRC, KC_MINS, \
    XXXXXXX, XXXXXXX, C_ARROW, KC_EQL,  XXXXXXX, KC_PLUS, KC_RPRN, KC_RCBR, KC_RBRC, KC_SLSH, \
                      __HLD__, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define LAYOUT_LAYER_NUMBER \
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, \
    __________HOME_ROW_MODS_L_________, XXXXXXX, KC_ASTR, KC_1,    KC_2,    KC_3,    KC_MINS, \
    LA_LOCK, XXXXXXX, KC_DOT,  KC_EQL,  XXXXXXX, KC_PLUS, KC_4,    KC_5,    KC_6,    KC_SLSH, \
                      XXXXXXX, XXXXXXX, __HLD__, EXTEND,  KC_0

#define LAYOUT_LAYER_EXTEND \
    KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX, XXXXXXX, SC_PREV, SC_UDIR, SC_NEXT, XXXXXXX, \
    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, SC_FIND, SC_SALL, __________HOME_ROW_MODS_R_________, \
    SC_UNDO, SC_CUT,  SC_COPY, SC_PSTE, SC_REDO, AT_COMP, SC_HAEN, SC_HANJ, XXXXXXX, XXXXXXX, \
                      XXXXXXX, XXXXXXX, NUMBER,  __HLD__, XXXXXXX

#define LAYOUT_LAYER_FUNCTION \
    XXXXXXX, SWAP_OS, XXXXXXX, DB_TOGG, QK_RBT,  XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F12, \
    __________HOME_ROW_MODS_L_________, XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F11, \
    XXXXXXX, XXXXXXX, QWERTY,  COLEMAK, XXXXXXX, XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F10, \
                      QK_BOOT, XXXXXXX, __HLD__, __HLD__, XXXXXXX

#define LAYOUT_LAYER_POINTER \
    DPI_RMOD, DPI_MOD, S_D_RMOD, S_D_MOD, SC_PREV, SC_PREV, SC_SALL, SC_CUT,  SC_COPY, SC_PSTE, \
    __________HOME_ROW_MODS_L_________,   SC_NEXT, SC_NEXT, __________HOME_ROW_MODS_R_________, \
    __HLD__, DRGSCRL,  SNIPING,  KC_BSPC, LA_LOCK, LA_LOCK, KC_BSPC, SNIPING, DRGSCRL, __HLD__, \
                       KC_BTN2,  KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN1

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_COLEMAK]  = LAYOUT_wrapper(LAYOUT_LAYER_COLEMAK),
  [LAYER_QWERTY]   = LAYOUT_wrapper(LAYOUT_LAYER_QWERTY),
  [LAYER_EXTEND]   = LAYOUT_wrapper(LAYOUT_LAYER_EXTEND),
  [LAYER_SYMBOL]   = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOL),
  [LAYER_NUMBER]   = LAYOUT_wrapper(LAYOUT_LAYER_NUMBER),
  [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
  [LAYER_POINTER]  = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
};

// clang-format on
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uprintf("kc: 0x%04x / pressed: %d / tap.count: %d\n",
      keycode, record->event.pressed, record->tap.count);
  PROCESS_FN(process_haen, keycode, record);
  PROCESS_FN(process_auto_completion, keycode, record, AT_COMP);
  PROCESS_FN(process_layer_lock, keycode, record, LA_LOCK)
  PROCESS_FN(process_os_variant_keys, keycode, record, SWAP_OS)
  PROCESS_FN(process_custom_oneshot_mods, keycode, record)
  PROCESS_FN(process_send_string_map, keycode, record);
  PROCESS_FN(process_custom_ths_keys, keycode, record);
  return true;
}

custom_ths_key_t** custom_ths_keys = (custom_ths_key_t*[]){
  CUSTOM_SHIFT_KEY(KC_BSPC, KC_BSPC, KC_DEL),
  CUSTOM_SHIFT_KEY(BSP_EXT, KC_BSPC, KC_DEL),
  CUSTOM_SHIFT_KEY(KC_DQUO, KC_DQUO, KC_QUOT),
  CUSTOM_SHIFT_KEY(KC_COMM, KC_COMM, KC_EXLM),
  CUSTOM_SHIFT_KEY(KC_DOT,  KC_DOT,  KC_QUES),
  CUSTOM_SHIFT_KEY(UDS_PTR, KC_UNDS, KC_EQL),
  NULL
};

const send_string_t** send_string_map = (const send_string_t*[]){
  SEND_STRING_ENTRY(C_ARROW, "->"),
  NULL
};

#define DOCSTRING_COMPLETION_WORD(_char) \
  /* _char */ _char _char \
  SS_TAP(X_ENT) \
  SS_TAP(X_ENT) \
  _char _char _char \
  SS_TAP(X_UP)

const uint16_t include_header[] = {KC_HASH, KC_I, KC_NO};
const uint16_t dquo_docstring_header[] = {KC_DQUO, KC_NO};
const uint16_t quot_docstring_header[] = {KC_LSFT, KC_DQUO, KC_NO};
const uint16_t code_block_header[] = {KC_GRV, KC_NO};
const uint16_t jfyi_header[] = {KC_LSFT, KC_J, KC_LSFT, KC_F, KC_LSFT, KC_Y, KC_LSFT, KC_I, KC_NO};
const auto_completion_pattern_t** auto_completion_patterns = (const auto_completion_pattern_t*[]){
  AUTO_COMPLETION_PATTERN(include_header, /* #i */ "nclude "),
  AUTO_COMPLETION_PATTERN(dquo_docstring_header, DOCSTRING_COMPLETION_WORD("\"")),
  AUTO_COMPLETION_PATTERN(quot_docstring_header, DOCSTRING_COMPLETION_WORD("'")),
  AUTO_COMPLETION_PATTERN(code_block_header, DOCSTRING_COMPLETION_WORD("`")),
  AUTO_COMPLETION_PATTERN(jfyi_header, SS_TAP(X_BSPC) SS_TAP(X_BSPC) SS_TAP(X_BSPC) /* J */ "ust for your information"),
  NULL
};

const os_variant_key_t** os_variant_keys = (const os_variant_key_t*[]){
  OS_VARIANT_KEY(SC_UNDO, LCTL(KC_Z), LGUI(KC_Z)),
  OS_VARIANT_KEY(SC_REDO, LCTL(KC_B), LGUI(KC_B)),
  OS_VARIANT_KEY(SC_FIND, LCTL(KC_F), LGUI(KC_F)),
  OS_VARIANT_KEY(SC_CUT,  LCTL(KC_X), LGUI(KC_X)),
  OS_VARIANT_KEY(SC_COPY, LCTL(KC_C), LGUI(KC_C)),
  OS_VARIANT_KEY(SC_PSTE, LCTL(KC_V), LGUI(KC_V)),
  OS_VARIANT_KEY(SC_SALL, LCTL(KC_A), LGUI(KC_A)),
  OS_VARIANT_KEY(SC_PREV, LALT(KC_LEFT), LGUI(KC_LBRC)),
  OS_VARIANT_KEY(SC_NEXT, LALT(KC_RGHT), LGUI(KC_RBRC)),
  OS_VARIANT_KEY(SC_UDIR, LALT(KC_UP), LGUI(KC_UP)),
  OS_VARIANT_KEY(SC_HAEN, KR_HAEN, LGUI(KC_SPC)),
  OS_VARIANT_KEY(SC_HANJ, KR_HANJ, LOPT(KC_ENT)),
  NULL
};

#define ROW1_HELPER(L1, L2, L3, L4, L5, R6, R7, R8, R9, R10, \
             ...) \
             L1, L2, L3, L4, L5, R6, R7, R8, R9, R10
#define ROW2_HELPER(L1,  L2,  L3,  L4,  L5,  R6,  R7,  R8,  R9,  R10, \
             L11, L12, L13, L14, L15, R16, R17, R18, R19, R20, \
             ...) \
             L11, L12, L13, L14, L15, R16, R17, R18, R19, R20
#define ROW3_HELPER(L1,  L2,  L3,  L4,  L5,  R6,  R7,  R8,  R9,  R10, \
             L11, L12, L13, L14, L15, R16, R17, R18, R19, R20, \
             L21, L22, L23, L24, L25, R26, R27, R28, R29, R30, \
             ...) \
             L21, L22, L23, L24, L25, R26, R27, R28, R29, R30
#define ROW1(...) ROW1_HELPER(__VA_ARGS__)
#define ROW2(...) ROW2_HELPER(__VA_ARGS__)
#define ROW3(...) ROW3_HELPER(__VA_ARGS__)
#define COL1_HELPER(L1, ...) L1
#define COL2_HELPER(L1, L2, ...) L2
#define COL3_HELPER(L1, L2, L3, ...) L3
#define COL4_HELPER(L1, L2, L3, L4, ...) L4
#define COL5_HELPER(L1, L2, L3, L4, L5, ...) L5
#define COL6_HELPER(L1, L2, L3, L4, L5, R6, ...) R6
#define COL7_HELPER(L1, L2, L3, L4, L5, R6, R7, ...) R7
#define COL8_HELPER(L1, L2, L3, L4, L5, R6, R7, R8, ...) R8
#define COL9_HELPER(L1, L2, L3, L4, L5, R6, R7, R8, R9, ...) R9
#define COL0_HELPER(L1, L2, L3, L4, L5, R6, R7, R8, R9, R10) R10
#define COL1(...) COL1_HELPER(__VA_ARGS__)
#define COL2(...) COL2_HELPER(__VA_ARGS__)
#define COL3(...) COL3_HELPER(__VA_ARGS__)
#define COL4(...) COL4_HELPER(__VA_ARGS__)
#define COL5(...) COL5_HELPER(__VA_ARGS__)
#define COL6(...) COL6_HELPER(__VA_ARGS__)
#define COL7(...) COL7_HELPER(__VA_ARGS__)
#define COL8(...) COL8_HELPER(__VA_ARGS__)
#define COL9(...) COL9_HELPER(__VA_ARGS__)
#define COL0(...) COL0_HELPER(__VA_ARGS__)

#define POS(_row, _col, _layer) COL##_col(ROW##_row(_layer))
const uint16_t PROGMEM colemak_combo_slsh[]  = {POS(3, 7, LAYOUT_LAYER_COLEMAK), POS(3, 8, LAYOUT_LAYER_COLEMAK), COMBO_END};
const uint16_t PROGMEM qwerty_combo_slsh[]   = {POS(3, 7, LAYOUT_LAYER_QWERTY),  POS(3, 8, LAYOUT_LAYER_QWERTY),  COMBO_END};
#undef POS

combo_t key_combos[] = {
  COMBO(colemak_combo_slsh, KC_SLSH),
  COMBO(qwerty_combo_slsh,  KC_SLSH),
};

void keyboard_post_init_user(void) {
  initialize_auto_completion();
}

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    state = update_tri_layer_state(state, LAYER_NUMBER, LAYER_EXTEND, LAYER_FUNCTION);
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

bool shutdown_user(bool jump_to_bootloader) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb(RGB_RED);
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif // RGB_MATRIX_ENABLE
    return jump_to_bootloader;
}
