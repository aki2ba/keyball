/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "quantum.h"

enum custom_keycodes {
  SS_LHOST = KEYBALL_SAFE_RANGE,
  SS_DC,
  TO0_MHEN,
  TO0_HENK,
  LT3_COPY
};

enum combos {
  CL_CPLK
};

const uint16_t PROGMEM cl_combo[] = {KC_C, KC_L, COMBO_END};

combo_t key_combos[] = {
  [CL_CPLK] = COMBO(cl_combo, S(KC_CAPS)),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_TAB     , KC_Q     , KC_W         , KC_E           , KC_R           , KC_T     ,                                        KC_Y     , KC_U        , KC_I           , KC_O            , KC_P     , KC_BSPC   ,
    KC_INT5    , KC_A     , KC_S         , CTL_T(KC_D)    , LT(2,KC_F)     , KC_G     ,                                        KC_H     , LT(2,KC_J)  , CTL_T(KC_K)    , ALT_T(KC_L)     , TO(2)    , TO(3)     ,
    KC_INT4    , KC_Z     , SFT_T(KC_X)  , LT(3,KC_C)     , LT(1,KC_V)     , KC_B     ,                                        KC_N     , LT(1,KC_M)  , LT(3,KC_COMM)  , 	SFT_T(KC_DOT) , KC_SLSH  , KC_DEL    ,
                TO(2)    , _______      , _______          , KC_SPC       , KC_ENT   ,                       KC_ESC,   KC_LWIN, 	S(KC_CAPS),     KC_MINS  , S(KC_INT1)
  ),

  [1] = LAYOUT_universal(
    KC_TAB     ,  S(KC_EQL)  , KC_1     , KC_2    , KC_3   , S(KC_4)   ,                                               S(KC_LBRC)   , S(KC_1)    , S(KC_2)    , S(KC_3)     , S(KC_SCLN)  , S(KC_QUOT)  ,
    TO0_MHEN   ,  KC_0       , KC_4     , KC_5    , KC_6   , S(KC_5)   ,                                               KC_LBRC      , S(KC_7)    , S(KC_8)    , S(KC_9)     , KC_SCLN     , KC_QUOT     ,
    TO0_HENK   ,  KC_EQL     , KC_7     , KC_8    , KC_9   , S(KC_6)   ,                                               S(KC_INT3)   , S(KC_MINS) , KC_MINS    , S(KC_INT1)  , KC_INT3     , KC_DEL      ,
                  _______  , _______ , _______  ,    KC_SPC,        KC_ENT,                            KC_ESC    , KC_LWIN      ,	S(KC_CAPS)       , KC_RBRC    , KC_BSLS
  ),

  [2] = LAYOUT_universal(
    KC_TAB    , C(KC_Q)    , KC_W      , C(KC_E)     , C(KC_R)     , C(KC_T)     ,                                        C(KC_Y)     , C(KC_PGUP)     , MS_BTN3        , C(KC_PGDN)      , C(KC_P)    , KC_BSPC   ,
    TO0_MHEN  , C(KC_A)    , MS_BTN1   , MS_BTN3     , MS_BTN2     , KC_ENT      ,                                        C(KC_H)     , MS_BTN1        , CTL_T(KC_UP)   , 	MS_BTN2        , _______    , TO(3)     ,
    TO0_HENK  , C(KC_Z)    , KC_LSFT   , LT3_COPY    , C(KC_V)     , A(KC_LEFT)  ,                                        A(KC_RGHT)  , LT(1,KC_LEFT)  , LT(3,KC_DOWN)  , SFT_T(KC_RGHT)  , KC_SLSH    , KC_DEL    ,
                  TO(3)     , _______       , _______        ,         KC_SPC      , KC_ENT,                KC_ESC   , KC_LWIN     , S(KC_CAPS)           , KC_HOME        , KC_END
  ),

  [3] = LAYOUT_universal(
    KC_TAB     , KC_F1     , KC_F2    , KC_F3      , KC_F4     , KC_F5    ,                                        KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_PSCR   ,
    TO0_MHEN   , KC_F11    , C(KC_S)  , C(KC_D)    , C(KC_F)   , KC_F12   ,                                        _______   , C(KC_J)   , C(KC_K)   , C(KC_L)   , TO(2)     , _______   ,
    TO0_HENK   , _______   , C(KC_X)  , S(KC_TAB)  , KC_TAB    , C(KC_B)  ,                                        C(KC_N)   , KC_LALT   , _______   , KC_LSFT   , _______   , _______   ,
                TO(2)     , _______  , _______    ,        _______  , _______  ,                   SS_LHOST  , SS_DC     , _______       , QK_BOOT  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case SS_LHOST:
          if (record->event.pressed) {
              SEND_STRING("localhost");
          }
          return false;
      case SS_DC:
          if (record->event.pressed) {
              SEND_STRING("docker compose");
          }
          return false;
      case TO0_MHEN:
          if (record->event.pressed) {
              layer_move(0);
              tap_code16(KC_INT5);
          }
      case TO0_HENK:
          if (record->event.pressed) {
              layer_move(0);
              tap_code16(KC_INT4);
          }
      case LT3_COPY:
          if (record->tap.count && record->event.pressed) {
              tap_code16(C(KC_C))
          } else if (record->event.pressed) {
              layer_on(3)
          } else {
              layer_off(3)
          }
  }

  return true;
}
