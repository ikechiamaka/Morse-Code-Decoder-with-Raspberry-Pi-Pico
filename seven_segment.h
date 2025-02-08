/* Seven-segment display (5161BS) header file */

#pragma once

#include "hardware/gpio.h"
#include <stdint.h>

/** Segment Definitions **/
#define SEGMENT_A            7  // Pin 10 (GPIO 07)
#define SEGMENT_B            6  // Pin 09 (GPIO 06)
#define SEGMENT_C           20  // Pin 26 (GPIO 20)
#define SEGMENT_D           19  // Pin 25 (GPIO 19)
#define SEGMENT_E           18  // Pin 24 (GPIO 18)
#define SEGMENT_F            8  // Pin 11 (GPIO 08)
#define SEGMENT_G            9  // Pin 12 (GPIO 09)
// Add DP if your display has a decimal point.

/** All Segments Array **/
static const unsigned int ALL_SEGMENTS[] = {
    SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G
    // Add DP to this array if applicable.
};

#define ALL_SEGMENTS_COUNT  7  // Update this count if you add DP.

/** Character Patterns (Numbers and Letters) **/
// Extend this array to include more characters.

/** COMMON ANODE**/
// uint8_t values[] = {
//     // Numbers 0-9
//     0b11111100,  // 0
//     0b01100000,  // 1
//     0b11011010,  // 2
//     0b11110010,  // 3
//     0b01100110,  // 4
//     0b10110110,  // 5
//     0b10111110,  // 6
//     0b11100000,  // 7
//     0b11111110,  // 8
//     0b11110110,  // 9
//     // Letters A-Z
//     0b00001000,  // A
//     0b00000011,  // B
//     0b01000110,  // C
//     0b00100001,  // D
//     0b00000110,  // E
//     0b10001110,  // F
//     0b00010000,  // G
//     0b00001001,  // H
//     0b01001111,  // I
//     0b01100001,  // J
//     0b00001001,  // // K 
//     0b01000111,  // L
//     0b01101010,// M 
//     0b00101011,  // N
//     0b01000000,  // O
//     0b00001100,  // P
//     0b00011000,  // Q
//     0b00101111,  // R
//     0b00010010,  // S
//     0b00000111,  // T
//     0b01000001,  // U
//     0b01100011,// V 
//     0b01010101,// W 
//     0b00001001,// X 
//     0b00010001,  // Y
//     0b00100100,// Z 
//     // Add pattern for error indication
// };



/** COMMON CATHODE**/
uint8_t values[] = {
    // Numbers 0-9
    0b00000011,  // 0
    0b10011111,  // 1
    0b00100101,  // 2
    0b00001101,  // 3
    0b10011001,  // 4
    0b01001001,  // 5
    0b01000001,  // 6
    0b00011111,  // 7
    0b00000001,  // 8
    0b00001001,  // 9
    // Letters A-Z
    0b11110111,  // A
    0b11111100,  // B
    0b10111001,  // C
    0b11011110,  // D
    0b11111001,  // E
    0b01110001,  // F
    0b11101111,  // G
    0b11110110,  // H
    0b10110000,  // I
    0b10011110,  // J
    0b11110110,  // K 
    0b10111000,  // L
    0b10010101,  // M 
    0b11010100,  // N
    0b10111111,  // O
    0b11110011,  // P
    0b11100111,  // Q
    0b11010000,  // R
    0b11101101,  // S
    0b11111000,  // T
    0b10111110,  // U
    0b10011100,  // V 
    0b10101010,  // W 
    0b11110110,  // X 
    0b11101110,  // Y
    0b11011011,  // Z 
    // Add pattern for error indication
};


/**
 * Initialize the GPIO pins for the seven-segment display.
 */
void seven_segment_init() {
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++) {
        gpio_init(ALL_SEGMENTS[i]);
        gpio_set_dir(ALL_SEGMENTS[i], GPIO_OUT);
    }
}

/**
 * Turn off the seven-segment display.
 */
void seven_segment_off() {
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++) {
        gpio_put(ALL_SEGMENTS[i], false); // true for COMMON ANODE
    }
}

/**
 * Display a character on the seven-segment display.
 * @param charIndex Index of the character in the `values` array.
 */
void seven_segment_show(char c) {
    // Assuming 'A' maps to index 10, 'B' to 11, ..., 'H' to 17 in the values array.
    int index = c - 'A' + 10; // Adjust this based on your array's indexing

    if (index < 0 || index >= sizeof(values)) {
        // Handle invalid index
        return;
    }

    for (int i = 0; i < ALL_SEGMENTS_COUNT; i++) {
        bool segmentOn = values[index] & (1 << i);
        gpio_put(ALL_SEGMENTS[i], segmentOn);
    }
}
