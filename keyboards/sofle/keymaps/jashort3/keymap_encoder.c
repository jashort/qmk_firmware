#include QMK_KEYBOARD_H


#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code16(SGUI(KC_Z));
        } else {
            tap_code16(LGUI(KC_Z));
        }
    }
    return false;
}

#endif
