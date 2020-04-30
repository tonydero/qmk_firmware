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
#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
// Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)
// 
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define TENKY TG(_ADJUST)

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7,
  QUADRUPLE_TAP = 8,
  QUADRUPLE_HOLD = 9
};

//Tap dance enums
enum {
  S_M = 0,
  C_M = 1,
  A_M = 2,
  G_M = 3,
  SOME_OTHER_DANCE
};

int cur_dance (qk_tap_dance_state_t *state);

//for the shift tap dance. Put it here so it can be used in any keymap
void sft_finished (qk_tap_dance_state_t *state, void *user_data);
void sft_reset (qk_tap_dance_state_t *state, void *user_data);
void ctl_finished (qk_tap_dance_state_t *state, void *user_data);
void ctl_reset (qk_tap_dance_state_t *state, void *user_data);
void alt_finished (qk_tap_dance_state_t *state, void *user_data);
void alt_reset (qk_tap_dance_state_t *state, void *user_data);
void gui_finished (qk_tap_dance_state_t *state, void *user_data);
void gui_reset (qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_PSCR, KC_INS,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NLCK, KC_DEL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_GESC, KC_BSPC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_TAB,  KC_ENT , KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
  KC_CAPS, AU_TOG,  TD(A_M), LOWER,   TD(S_M), TD(C_M), TD(G_M), KC_SPC,  RAISE,   ADJUST,  KC_QUOT, KC_BSLS  \
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_grid( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_PSCR, KC_INS,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    UC_MOD,  KC_DEL,  KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, \
  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_GESC, KC_BSPC, KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_TAB,  KC_ENT , KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
  KC_LEAD, AU_TOG,  TD(A_M), LOWER,   TD(S_M), TD(C_M), TD(G_M), KC_SPC,  RAISE,   ADJUST,  KC_QUOT, KC_BSLS  \
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_preonic_grid( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_PSCR, KC_INS,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_NLCK, KC_DEL,  KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    \
  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_GESC, KC_BSPC, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    \
  KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_TAB,  KC_ENT , KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    \
  KC_CAPS, AU_TOG,  TD(A_M), LOWER,   TD(S_M), TD(C_M), TD(G_M), KC_SPC,  RAISE,   ADJUST,  KC_QUOT, KC_BSLS  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX, XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F11,  \
  XXXXXXX, KC_UNDS, KC_MINS, KC_EQL,  KC_PLUS, KC_GRV,  XXXXXXX, KC_DQUO, KC_QUOT, KC_BSLS, KC_PIPE, KC_F12,  \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, KC_RALT, _______, _______, XXXXXXX, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX  \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX, XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F11,  \
  CK_TOGG, CK_DOWN, CK_UP,   KC_LBRC, KC_RBRC, KC_GRV,  XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_F12,  \
  KC_INS,  XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, \
  XXXXXXX, XXXXXXX, KC_RALT, _______, _______, XXXXXXX, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, KC_NLCK, KC_PSLS, KC_PAST, XXXXXXX, \
  XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX, XXXXXXX, _______, KC_NLCK, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
  XXXXXXX, KC_INS,  KC_HOME, KC_PGUP, XXXXXXX, XXXXXXX, _______, KC_PSLS, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, \
  XXXXXXX, KC_DEL,  KC_END,  KC_PGDN, XXXXXXX, XXXXXXX, _______, KC_PAST, KC_P1,   KC_P2,   KC_P3,   KC_PEQL, \
  MU_TOG,  MU_MOD,  _______, XXXXXXX, _______, _______, _______, KC_P0,   _______, _______, KC_PDOT, KC_PENT  \
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_DVORAK);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            PORTE &= ~(1<<6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            PORTE |= (1<<6);
            #endif
          }
          return false;
          break;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
   }
}

bool did_lead_succeed;
#ifdef AUDIO_ENABLE
//float lead_start[][2] = SONG(ONE_UP_SOUND);
float lead_succeed[][2] = SONG(ONE_UP_SOUND);
float lead_fail[][2] = SONG(MARIO_GAMEOVER);
#endif

/*
void leader_begin(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(lead_start);
#endif
}
*/

void leader_end(void) {
  if (did_lead_succeed) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(lead_succeed);
#endif
  } else {
#ifdef AUDIO_ENABLE
    PLAY_SONG(lead_fail);
#endif
  }
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif

  LEADER_DICTIONARY() {
    did_lead_succeed = leading = false;

    SEQ_ONE_KEY(KC_E) {
      SEND_STRING(SS_LCTRL(SS_LSFT("t")));
      did_lead_succeed = true;
    } else 
    SEQ_ONE_KEY(KC_S) {
      //send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
      did_lead_succeed = true;
    } else 
    SEQ_TWO_KEYS(KC_E, KC_D) {
      SEND_STRING("test");
      did_lead_succeed = true;
    }
    leader_end();
  }
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}


/*
enum unicode_names {
  BANG,
  IRONY,
  SNEK,
};

const uint32_t PROGMEM unicode_map[] = {
  [BANG]  = 0x203D,  // ‽
  [IRONY] = 0x2E2E,  // ⸮
  [SNEK]  = 0x1F40D, // 🐍
};
*/

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  //Assumes no one is trying to type the same letter four times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 4) {
    if (state->interrupted || !state->pressed)  return QUADRUPLE_TAP;
    else return QUADRUPLE_HOLD;
  }
  else return 10; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'shift' tap dance.
static tap sfttap_state = {
  .is_press_action = true,
  .state = 0
};

//instanalize an instance of 'tap' for the 'ctrl' tap dance.
static tap ctltap_state = {
  .is_press_action = true,
  .state = 0
};

//instanalize an instance of 'tap' for the 'alt' tap dance.
static tap alttap_state = {
  .is_press_action = true,
  .state = 0
};

//instanalize an instance of 'tap' for the 'gui' tap dance.
static tap guitap_state = {
  .is_press_action = true,
  .state = 0
};

void sft_finished (qk_tap_dance_state_t *state, void *user_data) {
  sfttap_state.state = cur_dance(state);
  switch (sfttap_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); break;
    case SINGLE_HOLD: register_code(KC_LSFT); break;
    case DOUBLE_TAP: register_code(KC_LALT); register_code(KC_TAB); break;
    case DOUBLE_HOLD: register_code(KC_LSFT); register_code(KC_LCTL); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_LSFT);
    case TRIPLE_TAP: register_code(KC_LALT); register_code(KC_ESC); break;
    case TRIPLE_HOLD: register_code(KC_LSFT); register_code(KC_LCTL); register_code(KC_LALT); break;
    case QUADRUPLE_TAP: register_code(KC_LALT); register_code(KC_TAB); break;
    case QUADRUPLE_HOLD: register_code(KC_LSFT); register_code(KC_LCTL); register_code(KC_LALT); register_code(KC_LGUI); break;
    //DOUBLE_SINGLE_TAP case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`,
    //which by default is 200ms.
  }
}

void sft_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (sfttap_state.state) {
    case SINGLE_TAP: unregister_code(KC_LSFT); break;
    case SINGLE_HOLD: unregister_code(KC_LSFT); break;
    case DOUBLE_TAP: unregister_code(KC_LALT); unregister_code(KC_TAB); break;
    case DOUBLE_HOLD: unregister_code(KC_LSFT); unregister_code(KC_LCTL); break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_LSFT);
    case TRIPLE_TAP: unregister_code(KC_LALT); unregister_code(KC_ESC); break;
    case TRIPLE_HOLD: unregister_code(KC_LSFT); unregister_code(KC_LCTL); unregister_code(KC_LALT); break;
    case QUADRUPLE_TAP: unregister_code(KC_LALT); unregister_code(KC_TAB); break;
    case QUADRUPLE_HOLD: unregister_code(KC_LSFT); unregister_code(KC_LCTL); unregister_code(KC_LALT); unregister_code(KC_LGUI); break;
  }
  sfttap_state.state = 0;
}

void ctl_finished (qk_tap_dance_state_t *state, void *user_data) {
  ctltap_state.state = cur_dance(state);
  switch (ctltap_state.state) {
    case SINGLE_TAP: register_code(KC_LCTL); break;
    case SINGLE_HOLD: register_code(KC_LCTL); break;
    case DOUBLE_TAP: register_code(KC_LCTL); break;
    case DOUBLE_HOLD: register_code(KC_LCTL); register_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_LCTL);
    case TRIPLE_TAP: register_code(KC_LCTL); break;
    case TRIPLE_HOLD: register_code(KC_LCTL); register_code(KC_LSFT); register_code(KC_LGUI); break;
    case QUADRUPLE_TAP: register_code(KC_LCTL); break;
    case QUADRUPLE_HOLD: register_code(KC_LCTL); register_code(KC_LSFT); register_code(KC_LALT); register_code(KC_LGUI); break;
    //DOUBLE_SINGLE_TAP case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`,
    //which by default is 200ms.
  }
}

void ctl_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ctltap_state.state) {
    case SINGLE_TAP: unregister_code(KC_LCTL); break;
    case SINGLE_HOLD: unregister_code(KC_LCTL); break;
    case DOUBLE_TAP: unregister_code(KC_LCTL); break;
    case DOUBLE_HOLD: unregister_code(KC_LCTL); unregister_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_LCTL);
    case TRIPLE_TAP: unregister_code(KC_LCTL); break;
    case TRIPLE_HOLD: unregister_code(KC_LCTL); unregister_code(KC_LSFT); unregister_code(KC_LGUI); break;
    case QUADRUPLE_TAP: unregister_code(KC_LCTL); break;
    case QUADRUPLE_HOLD: unregister_code(KC_LCTL); unregister_code(KC_LSFT); unregister_code(KC_LALT); unregister_code(KC_LGUI); break;
  }
  ctltap_state.state = 0;
}

void alt_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: register_code(KC_LALT); break;
    case SINGLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_TAP: register_code(KC_LALT); break;
    case DOUBLE_HOLD: register_code(KC_LALT); register_code(KC_LGUI); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_LALT);
    case TRIPLE_TAP: register_code(KC_LALT); break;
    case TRIPLE_HOLD: register_code(KC_LALT); register_code(KC_LGUI); register_code(KC_LSFT); break;
    case QUADRUPLE_TAP: register_code(KC_LALT); break;
    case QUADRUPLE_HOLD: register_code(KC_LALT); register_code(KC_LSFT); break;
    //DOUBLE_SINGLE_TAP case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`,
    //which by default is 200ms.
  }
}

void alt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: unregister_code(KC_LALT); break;
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    case DOUBLE_TAP: unregister_code(KC_LALT); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT); unregister_code(KC_LGUI); break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_LALT);
    case TRIPLE_TAP: unregister_code(KC_LALT); break;
    case TRIPLE_HOLD: unregister_code(KC_LALT); unregister_code(KC_LGUI); unregister_code(KC_LSFT); break;
    case QUADRUPLE_TAP: unregister_code(KC_LALT); break;
    case QUADRUPLE_HOLD: unregister_code(KC_LALT); unregister_code(KC_LSFT); break;
  }
  alttap_state.state = 0;
}

void gui_finished (qk_tap_dance_state_t *state, void *user_data) {
  guitap_state.state = cur_dance(state);
  switch (guitap_state.state) {
    case SINGLE_TAP: register_code(KC_LGUI); break;
    case SINGLE_HOLD: register_code(KC_LGUI); break;
    case DOUBLE_TAP: register_code(KC_LGUI); break;
    case DOUBLE_HOLD: register_code(KC_LGUI); register_code(KC_LSFT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_LGUI);
    case TRIPLE_TAP: register_code(KC_LGUI); break;
    case TRIPLE_HOLD: register_code(KC_LGUI); register_code(KC_LCTL); register_code(KC_LALT); break;
    case QUADRUPLE_TAP: register_code(KC_LGUI); break;
    case QUADRUPLE_HOLD: register_code(KC_LGUI); register_code(KC_LCTL); break;
    //DOUBLE_SINGLE_TAP case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`,
    //which by default is 200ms.
  }
}

void gui_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (guitap_state.state) {
    case SINGLE_TAP: unregister_code(KC_LGUI); break;
    case SINGLE_HOLD: unregister_code(KC_LGUI); break;
    case DOUBLE_TAP: unregister_code(KC_LGUI); break;
    case DOUBLE_HOLD: unregister_code(KC_LGUI); unregister_code(KC_LSFT); break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_LGUI);
    case TRIPLE_TAP: unregister_code(KC_LGUI); break;
    case TRIPLE_HOLD: unregister_code(KC_LGUI); unregister_code(KC_LCTL); unregister_code(KC_LALT); break;
    case QUADRUPLE_TAP: unregister_code(KC_LGUI); break;
    case QUADRUPLE_HOLD: unregister_code(KC_LGUI); unregister_code(KC_LCTL); break;
  }
  guitap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [S_M]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,sft_finished, sft_reset),
  [C_M]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,ctl_finished, ctl_reset),
  [A_M]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_finished, alt_reset),
  [G_M]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,gui_finished, gui_reset)
};
