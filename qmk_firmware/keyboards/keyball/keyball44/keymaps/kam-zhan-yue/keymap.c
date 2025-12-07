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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Layer 1 - Default
  [0] = LAYOUT_universal(
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
    KC_ESC   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_ENT   ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
              KC_LOPT,KC_LGUI,KC_LCTL     ,LT(1,KC_NO),LT(2,KC_NO),                  KC_BSPC,KC_SPC, _______, _______  , KC_PSCR
  ),
  // TODO: Setup
  // Layer 1 - Symbol Layer
  [1] = LAYOUT_universal(
    SSNP_FRE ,  _______ , S(KC_7)  , S(KC_8)   , S(KC_9)    , _______ ,                                         _______ , KC_MINUS , S(KC_MINUS), KC_EQUAL    , S(KC_EQUAL)   , _______   ,
    SSNP_VRT ,  _______ , S(KC_4)  , S(KC_5)   , S(KC_6)    , _______ ,                                         KC_QUOTE    , S(KC_0)  , S(KC_9)    , S(KC_RBRC)  , S(KC_LBRC)  , _______   ,
    SSNP_HOR ,  _______ , S(KC_1)  , S(KC_2)   , S(KC_3)    , _______ ,                                         S(KC_QUOTE)     , KC_RBRC  , KC_LBRC    , KC_BSLS  , S(KC_BSLS)  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),
  // TODO: Setup
  // Layer 2 - Scroll / Num Layer
  [2] = LAYOUT_universal(
    _______  ,  _______   , _______    , _______   , _______    , _______    ,                             _______    , KC_7    , KC_8    , KC_9    , _______   , _______   ,
    _______  ,  _______ , KC_LCTL  , KC_LOPT   , KC_LGUI   , _______   ,                                     _______  , KC_4  , KC_5    , KC_6  , _______  , _______  ,
    _______  ,  _______ , _______  , _______ , _______  , _______  ,                                         KC_0  , KC_1  , KC_2    , KC_3  , _______  , _______  ,
                  _______  , _______ , _______  ,   _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),
  // TODO: Figure this out lol
  // Layer 3 - Unused / Modifiers
  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                        RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
                  QK_BOOT  , KBC_RST  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , KBC_RST  , QK_BOOT
  ),
  // TODO: Add more buttons
  // Mouse Layer
  [4] = LAYOUT_universal(
    _______  ,  _______   , _______    , _______   , _______    , _______    ,                             _______    , _______    , _______    , _______    , _______   , _______   ,
    _______  ,  _______ , _______  , _______   , _______   , _______   ,                                     _______  , KC_BTN1  , KC_BTN2    , SCRL_MO  , _______  , _______  ,
    _______  ,  _______ , _______  , _______ , _______  , _______  ,                                         _______  , _______  , _______    , _______  , _______  , _______  ,
                  _______  , _______ , _______  ,   _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case 2:
            // Auto enable scroll mode when the highest layer is 3
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            keyball_set_scroll_mode(true);
            break;
        default:
            set_auto_mouse_enable(true);
            keyball_set_scroll_mode(false);
            break;
    }

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
