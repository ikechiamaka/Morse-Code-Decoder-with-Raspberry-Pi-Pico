#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "seven_segment.h"

#define BUTTON_PIN 16 // Pin 21 (GPIO 16)

// Morse code timing constants
#define DOT_DURATION 250    // Max duration for a dot (in milliseconds)
#define DASH_DURATION 250   // Min duration for a dash (in milliseconds)
#define LETTER_GAP 1000     // Duration to identify the end of a letter (in milliseconds)
#define DEBOUNCE_TIME 50 // 50 milliseconds debounce time
#define INACTIVITY_TIMEOUT 5000 // Inactivity timeout in milliseconds 


// Global variables
uint64_t button_pressed_time;
uint64_t button_released_time;
char morse_sequence[6]; // Morse code for one character (max 5 dots/dashes)
int morse_index = 0;
uint64_t last_input_time = 0;

// Function prototypes
void decoder();
void checkButton();
char morseToChar(const char* morse);


void main() {
    stdio_init_all();
    
    // Print welcome message
    printf("Morse Code Decoder Program Started\n");

    // Initialize the seven-segment display
    seven_segment_init();
    seven_segment_off();

    // Display a dash on the seven-segment display for testing
    gpio_put(SEGMENT_G, false); // FOR COMMON CATHODE, false for COMMON ANODE
    sleep_ms(1000);
    seven_segment_off();

    // Initialize the button's GPIO pin
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_down(BUTTON_PIN);

    memset(morse_sequence, 0, sizeof(morse_sequence)); // Clear the Morse code sequence

    while (true) {
        if (gpio_get(BUTTON_PIN)) {
            button_pressed_time = to_ms_since_boot(get_absolute_time());
            while (gpio_get(BUTTON_PIN)) {} // Wait until the button is released
            button_released_time = to_ms_since_boot(get_absolute_time());

            checkButton(); // Process the button press
            last_input_time = button_released_time;
        }

        if (to_ms_since_boot(get_absolute_time()) - last_input_time > LETTER_GAP && morse_index > 0) {
            decoder(); // Decode the Morse code sequence
            memset(morse_sequence, 0, sizeof(morse_sequence)); // Clear the Morse code sequence
            morse_index = 0;
        } else if (to_ms_since_boot(get_absolute_time()) - last_input_time > INACTIVITY_TIMEOUT) {
            printf("Inactivity detected. Clearing Morse sequence.\n");
            memset(morse_sequence, 0, sizeof(morse_sequence));
            morse_index = 0;
            last_input_time = to_ms_since_boot(get_absolute_time());
        }
    }
}
void decoder() {
    char decoded_char = morseToChar(morse_sequence);

    // Debug: print the Morse code sequence and the decoded character
    printf("Morse Sequence: %s, ", morse_sequence);

    if (decoded_char != '\0') {
        // Display the decoded character on the seven-segment display
        seven_segment_show(decoded_char);

        // Also print the character to the terminal
        printf("Decoded Character: %c\n", decoded_char);
        last_input_time = to_ms_since_boot(get_absolute_time());
    } else {
        // Handle error or invalid Morse code
        printf("Invalid Morse Code\n");
    }
}




// void checkButton() {
//     sleep_ms(DEBOUNCE_TIME); // Debounce delay

//     button_released_time = to_ms_since_boot(get_absolute_time());
//     uint64_t duration = button_released_time - button_pressed_time;

//     // Debug: Print duration and interpretation
//     printf("Button pressed for %llu ms. ", duration);

//     if (duration < DOT_DURATION) {
//         morse_sequence[morse_index++] = '.';
//         printf("Interpreted as DOT.\n");
//     } else if (duration >= DASH_DURATION) {
//         morse_sequence[morse_index++] = '-';
//         printf("Interpreted as DASH.\n");
//     }

//     if (morse_index >= sizeof(morse_sequence) - 1) {
//         morse_index = sizeof(morse_sequence) - 1;
//     }

//     if (duration >= LETTER_GAP) {
//         decoder();
//         memset(morse_sequence, 0, sizeof(morse_sequence));
//         morse_index = 0;
//         last_input_time = to_ms_since_boot(get_absolute_time());
//     }
// }
void checkButton() {
    sleep_ms(DEBOUNCE_TIME); // Debounce delay
    uint64_t duration = button_released_time - button_pressed_time;

    // Debug: Print duration and interpretation
    printf("Button pressed for %llu ms. ", duration);

    if (duration < DOT_DURATION) {
        morse_sequence[morse_index++] = '.';
        printf("Interpreted as DOT.\n");
    } else if (duration >= DASH_DURATION) {
        morse_sequence[morse_index++] = '-';
        printf("Interpreted as DASH.\n");
    }

    // Ensure morse_sequence does not overflow its bounds
    if (morse_index >= sizeof(morse_sequence) - 1) {
        morse_index = sizeof(morse_sequence) - 1;
    }
}

char morseToChar(const char* morse) {
    if (strcmp(morse, ".-") == 0) return 'A';
    else if (strcmp(morse, "-...") == 0) return 'B';
    else if (strcmp(morse, "-.-.") == 0) return 'C';
    else if (strcmp(morse, "-..") == 0) return 'D';
    else if (strcmp(morse, ".") == 0) return 'E';
    else if (strcmp(morse, "..-.") == 0) return 'F';
    else if (strcmp(morse, "--.") == 0) return 'G';
    else if (strcmp(morse, "....") == 0) return 'H';
    else if (strcmp(morse, "..") == 0) return 'I';
    else if (strcmp(morse, ".---") == 0) return 'J';
    else if (strcmp(morse, "-.-") == 0) return 'K';
    else if (strcmp(morse, ".-..") == 0) return 'L';
    else if (strcmp(morse, "--") == 0) return 'M';
    else if (strcmp(morse, "-.") == 0) return 'N';
    else if (strcmp(morse, "---") == 0) return 'O';
    else if (strcmp(morse, ".--.") == 0) return 'P';
    else if (strcmp(morse, "--.-") == 0) return 'Q';
    else if (strcmp(morse, ".-.") == 0) return 'R';
    else if (strcmp(morse, "...") == 0) return 'S';
    else if (strcmp(morse, "-") == 0) return 'T';
    else if (strcmp(morse, "..-") == 0) return 'U';
    else if (strcmp(morse, "...-") == 0) return 'V';
    else if (strcmp(morse, ".--") == 0) return 'W';
    else if (strcmp(morse, "-..-") == 0) return 'X';
    else if (strcmp(morse, "-.--") == 0) return 'Y';
    else if (strcmp(morse, "--..") == 0) return 'Z';
    else return '\0'; // Return null character if no match is found
}

