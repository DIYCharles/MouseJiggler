MouseJiggler
=========

This is a build of a HID emulating device that will continuously move the mouse to keep the computer from sleeping as well as preserve the online status of applications. It uses an Arduino Pro Micro and QMK Firmware 

![alt text](https://raw.githubusercontent.com/DIYCharles/MouseJiggler/master/photos/img3.jpg "img3.jpg")


Table of contents
=================

<!--ts-->
   * [Why](#Why)
   * [Wiring](#Wiring)
   * [Build](#Build)
   * [QMK Firmware](#QMK-Firmware)
   * [Compile And Flash](#Compile-And-Flash)
<!--te-->

Why
============
Q: Why not just use a shell script, ahk, or an existing program to do this? </br>

A: Some people do not have the ability to run scripts as cmd and powershell is blocked on their computers. Also IT may be monitoring or blocking additional programs added to the computer without approval. If you don't have these issues I strongly suggest mousejiggler or caffeine.

Q: Why not just buy a premade mouse mover usb dongle online? </br>

A: All USB products have hardware identification parameters so they can show up as a suspect usb device. With this solution you can spoof all the device identification parameters and it is recognized as a generic keyboard. For all intents and purposes after it is flashed it is a keyboard and acts exactly like it. 


Wiring
============

Pretty simple wiring. I wired a switch to pins 9 and 6 that corespond to B5 and D7. This is declared here in config.h
```h
#define MATRIX_ROW_PINS { B5 }
#define MATRIX_COL_PINS { D7 }
```
![alt text](https://raw.githubusercontent.com/DIYCharles/MouseJiggler/master/photos/img1.jpg "img1.jpg")

QMK Firmware
============

The important part of this project is the code as it can be added to any other keyboard using QMK. All the code can be found in the [MouseJiggler/QMK firmware/mousejiggler/](https://github.com/DIYCharles/MouseJiggler/tree/master/QMK%20firmware/mousejiggler) folder. Also there I a premade hex you can use in [MouseJiggler/QMK firmware/Premade Hex file/](https://github.com/DIYCharles/MouseJiggler/tree/master/QMK%20firmware/Premade%20Hex%20file) if you just want to copy the project exactly or don't want to learn QMK.

 Here's a quick breakdown of the code

Here I declare the macro MOUSEJIGGLERMACRO and then I put it where I want it on the keymap. Since this is just a 1x1 board it is the only key. 
```c
 enum custom_keycodes {
  MOUSEJIGGLERMACRO
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	KEYMAP(
		MOUSEJIGGLERMACRO)
};
```
Here I set a value mouse_jiggle_mode to false
```c
bool mouse_jiggle_mode = false;
```
Here is where the macro is registered. When the switch is down or closed the value of mouse_jiggle_mode is set to true. When it is released it is set back to false.
```c
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
```
In this next part we piggyback onto a mostly unused function that scans the keyboard repetitively on a loop. We use this loop to read our value mouse_jiggle_mode and if true it runs a set of mouse and wheel movements. This continues until the switch is toggled.
```c
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
```

Compile And Flash
=====
I put a guide for this in my other repo [here](https://github.com/DIYCharles/DIYKeyboards) 

Build
============

I didn't put much thought into the design or build. There are 3D print files for the shell in the 3D files folder.
