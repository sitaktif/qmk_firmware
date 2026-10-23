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

// Note: QK_CYCLE_LAYERS is not used anymore: we don't go next/previous layer,
// we activate each layer with each M1-M5 key. Keeping the code to cycle layers
// around in case it's useful in the future.
enum custom_keycodes {
    KC_CYCLE_LAYERS = QK_USER
};

enum layers {
    L0,
    L1,
    L2,
    L3,
    L4
};

// TODO: try KC_WWW_HOME KC_MSEL KC_MYCM KC_CALC

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L0] = LAYOUT_numpad_6x5(
        KC_MUTE, KC_WWW_HOME, KC_MSEL, KC_MYCM, KC_CALC,
        TO(L0),  KC_NUM,   KC_PSLS, KC_PAST,  KC_PMNS,
        TO(L1),  KC_P7,    KC_P8,   KC_P9,    KC_PPLS,
        TO(L2),  KC_P4,    KC_P5,   KC_P6,
        TO(L3),  KC_P1,    KC_P2,   KC_P3,    KC_PENT,
        TO(L4),  KC_P0,             KC_PDOT),

    [L1] = LAYOUT_numpad_6x5(
        RM_TOGG, KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L0),  KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L1),  KC_INT7, KC_INT8, KC_INT9, KC_LNG4,
        TO(L2),  KC_INT4, KC_INT5, KC_INT6,
        TO(L3),  KC_INT1, KC_INT2, KC_INT3,  KC_LNG3,
        TO(L4),  KC_LNG1,          KC_LNG2),

    [L2] = LAYOUT_numpad_6x5(
        RM_TOGG, KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L0),  KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L1),  KC_INT7, KC_INT8, KC_INT9, KC_LNG4,
        TO(L2),  KC_INT4, KC_INT5, KC_INT6,
        TO(L3),  KC_INT1, KC_INT2, KC_INT3,  KC_LNG3,
        TO(L4),  KC_LNG1,          KC_LNG2),

    [L3] = LAYOUT_numpad_6x5(
        RM_TOGG, KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L0),  KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L1),  KC_INT7, KC_INT8, KC_INT9, KC_LNG4,
        TO(L2),  KC_INT4, KC_INT5, KC_INT6,
        TO(L3),  KC_INT1, KC_INT2, KC_INT3,  KC_LNG3,
        TO(L4),  KC_LNG1,          KC_LNG2),

    [L4] = LAYOUT_numpad_6x5(
        RM_TOGG, KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L0),  KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L1),  KC_INT7, KC_INT8, KC_INT9, KC_LNG4,
        TO(L2),  KC_INT4, KC_INT5, KC_INT6,
        TO(L3),  KC_INT1, KC_INT2, KC_INT3,  KC_LNG3,
        TO(L4),  KC_LNG1,          KC_LNG2),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [L0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [L1] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [L2] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [L3] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [L4] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
};
#endif // ENCODER_MAP_ENABLE

// Define the RGB matrix index numbers for your shape keys
// (Replace these numbers with the exact LED IDs for your specific Keychron model)
#define LED_CIRCLE   0  // LED behind circle key (the are shifted by one vs keycodes because key 0 is a knob without LED)


// No background colors.
void keyboard_post_init_user(void) {
    // Set the effect to a solid static color without writing to EEPROM
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);

    // Set the solid color to completely off/black
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}


// Highlight M1, ..., M5 keycap that corresponds to layer number
const uint8_t M_LAYER_LED_INDICES[] = {4, 9, 14, 18, 23};

bool rgb_matrix_indicators_user(void) {
    uint8_t current_layer = get_highest_layer(layer_state);

    if (current_layer >= 0 && current_layer < 5) {
        rgb_matrix_set_color(M_LAYER_LED_INDICES[current_layer], 170, 255, 255);
    }
    return true;
}

// Loop through layers with a key is mapped to KC_CYCLE_LAYERS.

#define LAYER_CYCLE_START 0
#define LAYER_CYCLE_END   4

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CYCLE_LAYERS:
            // Trigger only when the key is pressed down (not on release)
            if (record->event.pressed) {
                uint8_t current_layer = get_highest_layer(layer_state);

                // Calculate the next layer.
                uint8_t next_layer = current_layer + 1;
                if (next_layer > LAYER_CYCLE_END) {
                    next_layer = LAYER_CYCLE_START;
                }

                // Clear all temporary layers and jump directly to the target layer
                layer_move(next_layer);
            }
            return false; // Tells QMK we handled this key, stop processing further

        default:
            return true; // Pass all other standard keys through normally
    }
}
