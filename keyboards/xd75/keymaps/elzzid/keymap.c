/* Copyright 2017 Wunder
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
#include "xd75.h"

// Layer shorthand
#define _QW 0
#define _LO 1
#define _RA 2
#define _FN 3
#define _SY 4

enum unicode_names {
    KATAKANA_TU,
    MACRON,
    O_STRIKE,
    ENYE,
    CENT
};

#define S_K_TU X(KATAKANA_TU)
#define S_MCRN X(MACRON)      
#define S_OSTR X(O_STRIKE)  
#define S_ENYE X(ENYE)  
#define S_CENT X(CENT)   


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


 [_QW] = { /* QWERTY */
  //{ XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
  {    KC_1 ,    KC_2 ,    KC_3 ,    KC_4 ,    KC_5 , KC_PSCR ,  KC_F13 ,  KC_F14 ,  KC_F15 ,  KC_INS ,    KC_6 ,    KC_7 ,    KC_8 ,    KC_9 , KC_0    } ,
  {    KC_Q ,    KC_W ,    KC_E ,    KC_R ,    KC_T ,  UC_MOD ,  KC_F10 ,  KC_F11 ,  KC_F12 ,  KC_DEL ,    KC_Y ,    KC_U ,    KC_I ,    KC_O , KC_P    } ,
  {    KC_A ,    KC_S ,    KC_D ,    KC_F ,    KC_G , KC_GESC ,   KC_F7 ,   KC_F8 ,   KC_F9 , KC_BSPC ,    KC_H ,    KC_J ,    KC_K ,    KC_L , KC_SCLN } ,
  {    KC_Z ,    KC_X ,    KC_C ,    KC_V ,    KC_B ,  KC_TAB ,   KC_F4 ,   KC_F5 ,   KC_F6 ,  KC_ENT ,    KC_N ,    KC_M , KC_COMM ,  KC_DOT , KC_SLSH } ,
  { XXXXXXX , RGB_TOG , KC_LALT , MO(_LO) , KC_LSFT , KC_LCTL ,   KC_F1 ,   KC_F2 ,   KC_F3 , KC_LGUI ,  KC_SPC , MO(_RA) , TO(_FN) , KC_QUOT , KC_BSLS } ,
  //{ KC_LEAD, AU_TOG,  TD(A_M), LOWER,   TD(S_M), TD(C_M), XXXXXXX, XXXXXXX, XXXXXXX, TD(G_M), KC_SPC,  RAISE,   ADJUST,  KC_QUOT, KC_BSLS },
 },

 [_LO] = { /* LOWER */
  //{ XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
  {   KC_F1 ,   KC_F2 ,   KC_F3 ,   KC_F4 ,   KC_F5 , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 , KC_F10  } ,
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_F11  } ,
  { XXXXXXX , KC_UNDS , KC_MINS ,  KC_EQL , KC_PLUS ,  KC_ESC , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_DQUO , KC_QUOT , KC_BSLS , KC_PIPE , KC_F12  } ,
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
  { XXXXXXX , RGB_MOD , KC_RALT , _______ , _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ , XXXXXXX , MO(_SY) , XXXXXXX , XXXXXXX , XXXXXXX } ,
 },

 [_RA] = { /* RAISE */
  //{ XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
  { KC_EXLM ,   KC_AT , KC_HASH ,  KC_DLR , KC_PERC , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN } ,
  { KC_EXLM ,   KC_AT , KC_HASH ,  KC_DLR , KC_PERC , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN } ,
  { KC_PSCR , KC_SLCK , KC_PAUS , KC_LBRC , KC_RBRC ,  KC_GRV , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_LEFT , KC_DOWN ,   KC_UP , KC_RGHT , XXXXXXX } ,
  {  KC_INS , XXXXXXX , XXXXXXX , KC_LCBR , KC_RCBR , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_HOME , KC_PGDN , KC_PGUP ,  KC_END , XXXXXXX } ,
  { XXXXXXX , RGB_M_K , KC_RALT , MO(_SY) , _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ , XXXXXXX , _______ , XXXXXXX , XXXXXXX , XXXXXXX } ,
 },

 [_FN] = { /* FUNCTION */
  //{ XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,   RESET , XXXXXXX , XXXXXXX , XXXXXXX , KC_NLCK , KC_PSLS , KC_PAST , XXXXXXX } ,
  {   KC_F1 ,   KC_F2 ,   KC_F3 ,   KC_F4 ,   KC_F5 , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_NLCK ,   KC_P7 ,   KC_P8 ,   KC_P9 , KC_PPLS } ,
  {   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,  KC_F10 , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_PSLS ,   KC_P4 ,   KC_P5 ,   KC_P6 , KC_PPLS } ,
  {  KC_F11 ,  KC_F12 , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_PAST ,   KC_P1 ,   KC_P2 ,   KC_P3 , KC_PEQL } ,
  { XXXXXXX , XXXXXXX , _______ , XXXXXXX , _______ , _______ , XXXXXXX , XXXXXXX , XXXXXXX , _______ ,   KC_P0 , _______ , TO(_QW) , KC_PDOT , KC_PENT } ,
 },

 [_SY] = { /* SYMBOLS */
  //{ XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,   RESET , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,  S_OSTR , XXXXXXX } ,
  { XXXXXXX ,  S_MCRN , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
  {  S_K_TU , XXXXXXX ,  S_CENT , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,  S_ENYE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ , XXXXXXX , XXXXXXX , XXXXXXX } ,
 }

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};

void matrix_init_user(void) {
  rgblight_enable();
  rgblight_setrgb(0, 43, 0);
  set_unicode_input_mode(UC_LNX);
};

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _LO:
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_setrgb(0, 0, 255);
        break;
    case _RA:
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_setrgb(255, 63, 0);
        break;
    case _FN:
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_setrgb(255, 0, 0);
        break;
    case _SY:
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_setrgb(127, 0, 255);
        break;
    default: //  for any other layers, or the default layer
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_setrgb(0, 43, 0);
        break;
    }
  return state;
};

const uint32_t PROGMEM unicode_map[] = {
    [KATAKANA_TU] = 0x30C4, // ツ
    [MACRON]      = 0x00AF, // ¯
    [O_STRIKE]    = 0x00F8, // ø
    [ENYE]        = 0x00F1, // ñ
    [CENT]        = 0x00A2, // ¢
};
