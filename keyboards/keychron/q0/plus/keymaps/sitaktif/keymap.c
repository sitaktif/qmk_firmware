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
    L4,
    L5,
    L6,
    L7,
    L8,
    L9,
    L10,
    L11
};

// Pressing two or three contiguous TO(Ln) keys together activates the matching new layer.
enum combos {
    COMBO_L5,
    COMBO_L6,
    COMBO_L7,
    COMBO_L8,
    COMBO_L9,
    COMBO_L10,
    COMBO_L11
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

    [L5] = LAYOUT_numpad_6x5(
        RM_TOGG, KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L0),  KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L1),  KC_INT7, KC_INT8, KC_INT9, KC_LNG4,
        TO(L2),  KC_INT4, KC_INT5, KC_INT6,
        TO(L3),  KC_INT1, KC_INT2, KC_INT3,  KC_LNG3,
        TO(L4),  KC_LNG1,          KC_LNG2),

    [L6] = LAYOUT_numpad_6x5(
        RM_TOGG, KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L0),  KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L1),  KC_INT7, KC_INT8, KC_INT9, KC_LNG4,
        TO(L2),  KC_INT4, KC_INT5, KC_INT6,
        TO(L3),  KC_INT1, KC_INT2, KC_INT3,  KC_LNG3,
        TO(L4),  KC_LNG1,          KC_LNG2),

    [L7] = LAYOUT_numpad_6x5(
        RM_TOGG, KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L0),  KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L1),  KC_INT7, KC_INT8, KC_INT9, KC_LNG4,
        TO(L2),  KC_INT4, KC_INT5, KC_INT6,
        TO(L3),  KC_INT1, KC_INT2, KC_INT3,  KC_LNG3,
        TO(L4),  KC_LNG1,          KC_LNG2),

    [L8] = LAYOUT_numpad_6x5(
        RM_TOGG, KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L0),  KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L1),  KC_INT7, KC_INT8, KC_INT9, KC_LNG4,
        TO(L2),  KC_INT4, KC_INT5, KC_INT6,
        TO(L3),  KC_INT1, KC_INT2, KC_INT3,  KC_LNG3,
        TO(L4),  KC_LNG1,          KC_LNG2),

    [L9] = LAYOUT_numpad_6x5(
        RM_TOGG, KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L0),  KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L1),  KC_INT7, KC_INT8, KC_INT9, KC_LNG4,
        TO(L2),  KC_INT4, KC_INT5, KC_INT6,
        TO(L3),  KC_INT1, KC_INT2, KC_INT3,  KC_LNG3,
        TO(L4),  KC_LNG1,          KC_LNG2),

    [L10] = LAYOUT_numpad_6x5(
        RM_TOGG, KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L0),  KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L1),  KC_INT7, KC_INT8, KC_INT9, KC_LNG4,
        TO(L2),  KC_INT4, KC_INT5, KC_INT6,
        TO(L3),  KC_INT1, KC_INT2, KC_INT3,  KC_LNG3,
        TO(L4),  KC_LNG1,          KC_LNG2),

    [L11] = LAYOUT_numpad_6x5(
        RM_TOGG, KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L0),  KC_LNG8, KC_LNG7, KC_LNG6, KC_LNG5,
        TO(L1),  KC_INT7, KC_INT8, KC_INT9, KC_LNG4,
        TO(L2),  KC_INT4, KC_INT5, KC_INT6,
        TO(L3),  KC_INT1, KC_INT2, KC_INT3,  KC_LNG3,
        TO(L4),  KC_LNG1,          KC_LNG2),
};

const uint16_t PROGMEM combo_l5[]  = {TO(L0), TO(L1), COMBO_END};
const uint16_t PROGMEM combo_l6[]  = {TO(L1), TO(L2), COMBO_END};
const uint16_t PROGMEM combo_l7[]  = {TO(L2), TO(L3), COMBO_END};
const uint16_t PROGMEM combo_l8[]  = {TO(L3), TO(L4), COMBO_END};
const uint16_t PROGMEM combo_l9[]  = {TO(L0), TO(L1), TO(L2), COMBO_END};
const uint16_t PROGMEM combo_l10[] = {TO(L1), TO(L2), TO(L3), COMBO_END};
const uint16_t PROGMEM combo_l11[] = {TO(L2), TO(L3), TO(L4), COMBO_END};

combo_t key_combos[] = {
    [COMBO_L5]  = COMBO(combo_l5, KC_NO),
    [COMBO_L6]  = COMBO(combo_l6, KC_NO),
    [COMBO_L7]  = COMBO(combo_l7, KC_NO),
    [COMBO_L8]  = COMBO(combo_l8, KC_NO),
    [COMBO_L9]  = COMBO(combo_l9, KC_NO),
    [COMBO_L10] = COMBO(combo_l10, KC_NO),
    [COMBO_L11] = COMBO(combo_l11, KC_NO),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) {
        return;
    }
    switch (combo_index) {
        case COMBO_L5:  layer_move(L5); break;
        case COMBO_L6:  layer_move(L6); break;
        case COMBO_L7:  layer_move(L7); break;
        case COMBO_L8:  layer_move(L8); break;
        case COMBO_L9:  layer_move(L9); break;
        case COMBO_L10: layer_move(L10); break;
        case COMBO_L11: layer_move(L11); break;
    }
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [L0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [L1] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [L2] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [L3] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [L4] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [L5] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [L6] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [L7] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [L8] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [L9] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [L10] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [L11] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
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

// New layers L5..L11 come from pressing two or three TO keys together, so they
// highlight the M keycaps of all their source layers (e.g. L5 from L0 + L1 lights
// M1 and M2). Unused entries are 0xFF.
#define NO_SOURCE 0xFF
const uint8_t M_COMBO_LAYER_SOURCES[][3] = {
    {L0, L1, NO_SOURCE},  // L5
    {L1, L2, NO_SOURCE},  // L6
    {L2, L3, NO_SOURCE},  // L7
    {L3, L4, NO_SOURCE},  // L8
    {L0, L1, L2},         // L9
    {L1, L2, L3},         // L10
    {L2, L3, L4},         // L11
};

bool rgb_matrix_indicators_user(void) {
    uint8_t current_layer = get_highest_layer(layer_state);

    if (current_layer >= L0 && current_layer <= L4) {
        rgb_matrix_set_color(M_LAYER_LED_INDICES[current_layer], 170, 255, 255);
    } else if (current_layer >= L5 && current_layer <= L11) {
        const uint8_t *sources = M_COMBO_LAYER_SOURCES[current_layer - L5];
        for (uint8_t i = 0; i < 3 && sources[i] != NO_SOURCE; i++) {
            rgb_matrix_set_color(M_LAYER_LED_INDICES[sources[i]], 170, 255, 255);
        }
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
