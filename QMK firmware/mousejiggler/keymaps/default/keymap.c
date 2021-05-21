#include "mousejiggler.h" 

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  MOUSEJIGGLERMACRO
};


bool mouse_jiggle_mode = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
		MOUSEJIGGLERMACRO)

};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
  if (mouse_jiggle_mode) {
    tap_code(KC_MS_UP);
    tap_code(KC_MS_DOWN);
    tap_code(KC_MS_LEFT);
    tap_code(KC_MS_RIGHT);
    tap_code(KC_MS_WH_UP);
    tap_code(KC_MS_WH_DOWN);
  } else {

  }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MOUSEJIGGLERMACRO:
      if (record->event.pressed) {
        mouse_jiggle_mode = true;
      } else {
        mouse_jiggle_mode = false;
      }
      break;
  }
  return true;
}

    /*    SEND_STRING("1");
    tap_code(KC_MS_BTN1);
    tap_code(KC_MS_BTN1);
    SEND_STRING(SS_LCTL("c"));
    tap_code(KC_RIGHT);
    SEND_STRING(SS_LCTL("v"));
    SEND_STRING("yaughtyaughtyaught");
    tap_code(KC_MS_BTN1);
    tap_code(KC_MS_BTN1);
    tap_code(KC_MS_BTN1);*/