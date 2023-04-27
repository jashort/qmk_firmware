/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _FUNC
};


// Aliases for readability
#define QWERTY   DF(_QWERTY)

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define MOUSE    MO(_MSE)
#define FKEYS    OSL(_FUNC)
#define MSE_QUOT LT(_MSE, KC_QUOTE)
#define ADJUST   MO(_ADJUST)
#define WRD_L    LCTL(KC_LEFT)
#define WRD_R    LCTL(KC_RIGHT)

#define GUI_ESC  MT(MOD_LGUI, KC_ESC)
//#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define SCNSHT   LGUI(LSFT(LCTL(KC_4)))
#define ENT_SYM  LT(SYM, KC_ENTER)

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * | TAB  |  Q   |  W   |  E   |  R   |  T   |                              |  Y   |  U   |  I   |  O   |  P   | \ |  |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |GUI_ES|  A   |  S   |  D   |  F   |  G   |                              |  H   |  J   |  K   |  L   | ; :  |   '  |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * | LSFT |  Z   |  X   |  C   |  V   |  B   |SCNSHT| CAPS |  |FKEYS |      |  N   |  M   | , <  | . >  | / ?  | RSFT |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      | LALT | LCTL |SPACE | BSPC |FKEYS |  |DELETE|FKEYS |ENT_SY| NAV  | RALT |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 *                                                                               generated by [keymapviz] */


    [_QWERTY] = LAYOUT(
     KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,    KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSLS,
     GUI_ESC , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H,    KC_J ,  KC_K ,   KC_L ,KC_SCLN, KC_QUOTE,
     KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B ,SCNSHT,KC_CAPS,     FKEYS  , _______, KC_N,    KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
     KC_LALT , KC_LCTL, KC_SPACE, KC_BSPC, FKEYS,     KC_DELETE , FKEYS  , ENT_SYM, NAV, KC_RALT
    ),

/*
 * Nav Layer: Media, navigation, bracketsg
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      | = +  |                              | PGUP |WRD_L |  UP  |WRD_R | HOME | = +  |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      | LGUI | LALT | LCTL | LSFT |      |                              | PGDN | LEFT | DOWN | RGHT | END  |  +   |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |  [   |  ]   |  {   |  }   | - _  |      | SCRL |  |      |      |      |      |      |      |      | PSCR |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'*/

    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, KC_EQL ,                                     KC_PGUP, WRD_L  , KC_UP  , WRD_R  ,  KC_HOME, KC_EQL,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_PLUS,
      _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_MINS, _______, KC_SCRL, _______, _______, _______, _______, _______, _______, _______, KC_PSCR,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * | ` ~  |  1   |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   | = +  |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |  ~   |  !   |  @   |  #   |  $   |  %   |                              |  ^   |  &   |  *   |  (   |  )   |  +   |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |  [   |  ]   |  {   |  }   | - _  |      |      |  |      |      | - _  |  _   | , <  | . >  | / ?  |  ?   |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 *                                                                               generated by [keymapviz] */


    [_SYM] = LAYOUT(
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
     KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
     _______ , KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_MINS, _______, _______, _______, _______, KC_MINS, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Function Layer: Function keys
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |      |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |                              |      | RSFT | RCTL | LALT | RGUI |      |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |  F9  | F10  | F11  | F12  |      |      |      |  | MPRV | MNXT |      | VOLD | VOLU |      |      |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [_FUNC] = LAYOUT(
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4, _______,                                     _______, _______, _______, _______, _______, _______,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
      _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______, _______, _______, KC_MPRV, KC_MNXT, _______, KC_VOLD, KC_VOLU, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Mouse Layer
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      |      |                              |      | WH_U | MS_U |      |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                              |      | MS_L | MS_D | MS_R |      |      |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      |      | WH_D |      |      |      |      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      | BTN1 | BTN2 |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 *                                                                               generated by [keymapviz] */

//    [_MSE] = LAYOUT(
//      _______, _______, _______, _______, _______, _______,                                    _______, KC_WH_U, KC_MS_U, _______, _______, _______,
//      _______, _______, _______, _______, _______, _______,                                    _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
//      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, KC_WH_D, _______, _______, _______, _______,
//                                 _______, _______, _______,_______, _______, _______, _______, KC_BTN1, KC_BTN2, _______
//    ),


/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |QWERTY|      |      |                              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                              |RGB_TO|RGB_SA|RGB_HU|RGB_VA|RGB_MO|      |
 * |------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  |      |      |      |RGB_SA|RGB_HU|RGB_VA|RGB_RM|      |
 * `------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+------'
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      |      |      |      |      |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
//    [_ADJUST] = LAYOUT(
//      _______, _______, _______, QWERTY , _______, _______,                                    _______, _______, _______, _______,  _______, _______,
//      _______, _______, _______, _______, _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
//      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
//                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
//    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    rgblight_sethsv_noeeprom(HSV_PURPLE);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

void housekeeping_task_user(void) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case 0:
            // Default layer
            rgblight_sethsv_noeeprom(HSV_PURPLE);
            break;
        case 1:
            rgblight_sethsv_noeeprom(HSV_RED);
            break;
        case 2:
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case 3:
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        case 4:
            rgblight_sethsv_noeeprom(HSV_ORANGE);
            break;
        case 5:
            rgblight_sethsv_noeeprom(HSV_YELLOW);
            break;
    }
}
#endif