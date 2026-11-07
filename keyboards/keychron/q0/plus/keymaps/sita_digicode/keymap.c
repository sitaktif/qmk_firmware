/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

// clang-format off

enum layers {
    BASE,
};

// Holding the knob (wheel-down) and pressing 2 then 2 starts the digicode game.
// Holding it and pressing 1 then 1 goes back to the keypad.
#define DIGICODE_START_DIGIT 2
#define DIGICODE_STOP_DIGIT  1

// The secret combination, in the order it must be entered. It must have 2 to 8
// digits, all different: the checks below fail the build otherwise.
#define DIGICODE_DIGITS(X) X(4) X(1) X(8) X(3) X(7) X(2)

#define DIGICODE_AS_ENTRY(d)    d,
#define DIGICODE_AS_CASE(d)     case d:
#define DIGICODE_CHECK_DIGIT(d) _Static_assert((d) >= 0 && (d) <= 9, "digicode digits must be 0 to 9");

static const uint8_t digicode[] = {DIGICODE_DIGITS(DIGICODE_AS_ENTRY)};
#define DIGICODE_LENGTH (sizeof(digicode) / sizeof(digicode[0]))

// A repeated digit is a duplicate case label, which the compiler rejects.
static inline void digicode_check_combination(void) {
    _Static_assert(DIGICODE_LENGTH >= 2 && DIGICODE_LENGTH <= 8, "digicode must have 2 to 8 digits");
    DIGICODE_DIGITS(DIGICODE_CHECK_DIGIT)
    switch (0) {
        DIGICODE_DIGITS(DIGICODE_AS_CASE)
            break;
    }
}

#define FLASH_HALF_PERIOD_MS    200
#define DIGICODE_OK_FLASH_MS    3000
#define DIGICODE_WRONG_FLASH_MS 2000

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_numpad_6x5(
        KC_MUTE, KC_WWW_HOME, KC_MSEL, KC_MYCM, KC_CALC,
        KC_NO,   KC_NUM,   KC_PSLS, KC_PAST,  KC_PMNS,
        KC_NO,   KC_P7,    KC_P8,   KC_P9,    KC_PPLS,
        KC_NO,   KC_P4,    KC_P5,   KC_P6,
        KC_NO,   KC_P1,    KC_P2,   KC_P3,    KC_PENT,
        KC_NO,   KC_P0,             KC_PDOT),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif // ENCODER_MAP_ENABLE

// RGB matrix indices, from g_led_config in plus.c. The knob has no LED.
// The top keys are circle, triangle, square and cross.
const uint8_t LED_SHAPE_KEYS[] = {0, 1, 2, 3};

// The numpad block: NUM, /, *, -, 7-9, +, 4-6, 1-3, enter, 0 and .
const uint8_t LED_NUMPAD_BLOCK[] = {5, 6, 7, 8, 10, 11, 12, 13, 15, 16, 17, 19, 20, 21, 22, 24, 25};

// LED of each digit key, indexed by digit.
const uint8_t LED_DIGIT[] = {24, 19, 20, 21, 15, 16, 17, 10, 11, 12};

static bool digicode_active = false;
static uint8_t entered[DIGICODE_LENGTH];
static uint8_t entered_count = 0;
static bool top_green = false;
static bool flashing = false;
static bool flash_correct = false;
static uint16_t flash_start = 0;
static uint16_t flash_duration = 0;

static bool knob_held = false;
static bool knob_used = false;
static int8_t knob_prev_digit = -1;

// No background colors.
void keyboard_post_init_user(void) {
    // Set the effect to a solid static color without writing to EEPROM
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);

    // Set the solid color to completely off/black
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

static int8_t keycode_to_digit(uint16_t keycode) {
    switch (keycode) {
        case KC_P0: return 0;
        case KC_P1: return 1;
        case KC_P2: return 2;
        case KC_P3: return 3;
        case KC_P4: return 4;
        case KC_P5: return 5;
        case KC_P6: return 6;
        case KC_P7: return 7;
        case KC_P8: return 8;
        case KC_P9: return 9;
        default:    return -1;
    }
}

static void set_leds_red_or_green(const uint8_t *leds, uint8_t count, bool green) {
    for (uint8_t i = 0; i < count; i++) {
        if (green) {
            rgb_matrix_set_color(leds[i], 0, 255, 0);
        } else {
            rgb_matrix_set_color(leds[i], 255, 0, 0);
        }
    }
}

static void digicode_set_active(bool active) {
    digicode_active = active;
    entered_count = 0;
    flashing = false;
    top_green = false;
}

static bool digicode_is_correct(void) {
    for (uint8_t i = 0; i < DIGICODE_LENGTH; i++) {
        if (entered[i] != digicode[i]) {
            return false;
        }
    }
    return true;
}

static void digicode_press(uint8_t digit) {
    if (flashing) {
        return;
    }
    entered[entered_count++] = digit;
    if (entered_count < DIGICODE_LENGTH) {
        return;
    }

    // Evaluate. Resetting the count switches the orange digit LEDs off first.
    entered_count = 0;
    flash_correct = digicode_is_correct();
    flash_duration = flash_correct ? DIGICODE_OK_FLASH_MS : DIGICODE_WRONG_FLASH_MS;
    flash_start = timer_read();
    flashing = true;
}

static void digicode_knob_digit(int8_t digit) {
    // Two of the same digit in a row, while the knob is held
    if (digit == knob_prev_digit) {
        if (digit == DIGICODE_START_DIGIT && !digicode_active) {
            digicode_set_active(true);
        } else if (digit == DIGICODE_STOP_DIGIT && digicode_active) {
            digicode_set_active(false);
        }
    }
    knob_prev_digit = digit;
}

static void knob_key(keyrecord_t *record) {
    if (record->event.pressed) {
        knob_held = true;
        knob_used = false;
        knob_prev_digit = -1;
        return;
    }

    knob_held = false;
    // A plain tap of the knob still mutes, unless it was used as a modifier
    if (!knob_used && !digicode_active) {
        tap_code(KC_MUTE);
    }
}

void matrix_scan_user(void) {
    if (flashing && timer_elapsed(flash_start) >= flash_duration) {
        flashing = false;
        if (flash_correct) {
            top_green = !top_green;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_ENCODEREVENT(record->event)) {
        // Turning the knob only changes the volume on the keypad
        return !digicode_active;
    }

    if (keycode == KC_MUTE) {
        knob_key(record);
        return false;
    }

    int8_t digit = keycode_to_digit(keycode);

    if (knob_held && record->event.pressed) {
        knob_used = true;
    }

    if (knob_held && digit >= 0) {
        // With the knob held, digits switch modes and are not sent
        if (record->event.pressed) {
            digicode_knob_digit(digit);
        }
        return false;
    }

    if (digicode_active) {
        // In digicode mode, no key reaches the OS
        if (record->event.pressed && digit >= 0) {
            digicode_press(digit);
        }
        return false;
    }

    return true;
}

bool rgb_matrix_indicators_user(void) {
    if (!digicode_active) {
        return true;
    }

    set_leds_red_or_green(LED_SHAPE_KEYS, ARRAY_SIZE(LED_SHAPE_KEYS), top_green);

    if (flashing && (timer_elapsed(flash_start) / FLASH_HALF_PERIOD_MS) % 2 == 0) {
        set_leds_red_or_green(LED_NUMPAD_BLOCK, ARRAY_SIZE(LED_NUMPAD_BLOCK), flash_correct);
    }

    for (uint8_t i = 0; i < entered_count; i++) {
        rgb_matrix_set_color(LED_DIGIT[entered[i]], 255, 128, 0);
    }
    return true;
}
