#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"

#define HOME G(KC_LEFT)
#define END G(KC_RGHT)
#define FWD G(KC_RBRC)
#define BACK G(KC_LBRC)
#define TAB_L G(S(KC_LBRC))
#define TAB_R G(S(KC_RBRC))
#define SPACE_L A(G(KC_LEFT))
#define SPACE_R A(G(KC_RGHT))
#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,  // Switch to next window         (cmd-tab)
    SW_LANG, // Switch to next input language (ctl-spc)
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE,
    WRD_L = LOPT(KC_LEFT),
    WRD_R = LOPT(KC_RIGHT),
    SSHOT = LCTL(SGUI(KC_4)),
    SSAV = SGUI(KC_4)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [DEF] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, XXXXXXX,
        XXXXXXX,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, XXXXXXX,
        XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    XXXXXXX,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
                       XXXXXXX,XXXXXXX, LA_NAV, KC_SPC , KC_BSPC,             KC_RSFT, KC_SPC, LA_SYM, XXXXXXX, XXXXXXX
        ),

    [SYM] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_ESC,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,                      KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC,  KC_GRV, XXXXXXX,
        XXXXXXX, KC_MINS, KC_ASTR,  KC_EQL, KC_UNDS,  KC_DLR,                      KC_HASH,  OS_CMD,  OS_ALT, OS_CTRL, OS_SHFT, XXXXXXX,
        XXXXXXX, KC_PLUS, KC_PIPE, KC_AT,   KC_SLSH, KC_PERC, _______,    _______, XXXXXXX, KC_BSLS, KC_AMPR, KC_QUES, KC_EXLM, XXXXXXX,
                      XXXXXXX, XXXXXXX, _______, _______, _______,             _______, _______, _______, XXXXXXX, XXXXXXX
        ),

    [NAV] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  KC_TAB,  SW_WIN,   TAB_L,   TAB_R, KC_VOLU,                      XXXXXXX,    HOME,   KC_UP,     END,  KC_DEL, XXXXXXX,
        XXXXXXX,  OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD, KC_VOLD,                      KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, XXXXXXX,
        XXXXXXX,  SPACE_L, SPACE_R,   BACK,     FWD  KC_MPLY, _______,    _______, aaXXXXXXX, KC_PGDN, KC_PGUP, SW_LANG,  KC_ENT, XXXXXXX,
                       XXXXXXX,  XXXXXXX,  _______, _______, _______,          _______,  _______, _______, XXXXXXX, XXXXXXX
        ),

    [NUM] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,    KC_7,    KC_5,    KC_3,    KC_1,    KC_9,                         KC_8,    KC_0,    KC_2,    KC_4,    KC_6, XXXXXXX,
        XXXXXXX, OS_SHFT, OS_CTRL,  OS_ALT,  OS_CMD,  KC_F11,                       KC_F10,  OS_CMD,  OS_ALT, OS_CTRL, OS_SHFT, XXXXXXX,
        XXXXXXX,   KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F9, _______,    _______,   KC_F8,  KC_F12,   KC_F2,   KC_F4,   KC_F6, XXXXXXX,
                      XXXXXXX, XXXXXXX, _______, _______, _______,             _______, _______, _______, XXXXXXX, XXXXXXX
        ),
};


bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_lang_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LCTL, KC_SPC, SW_LANG,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
