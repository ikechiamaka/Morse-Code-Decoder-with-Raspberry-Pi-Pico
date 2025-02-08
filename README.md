# Morse Code Decoder with Raspberry Pi Pico

This project implements a Morse code decoder on a Raspberry Pi Pico. It reads Morse code input from a button (via a GPIO pin), decodes the sequence into an alphanumeric character, and displays the result on a seven-segment display. The decoder uses precise timing to differentiate between dots and dashes and includes inactivity detection to automatically process the input sequence.


---

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)


---

## Overview

This project leverages the Raspberry Pi Pico and its SDK along with a seven-segment display to decode Morse code entered via a push button. The program measures the duration of button presses to determine whether a dot or a dash has been entered. After a pause (letter gap) or an inactivity timeout, the entered Morse sequence is decoded into a character, which is then displayed on the seven-segment display and printed to the terminal.

---

## Features

- **Morse Code Decoding:** Differentiates between dots (`.`) and dashes (`-`) based on button press duration.
- **Seven-Segment Display:** Shows the decoded character.
- **Inactivity Handling:** Clears the input sequence after a set period of inactivity.
- **Debug Output:** Prints Morse sequence and decoded characters to the serial terminal for debugging.
- **Debounce Handling:** Implements debounce logic to improve button press detection.

---

## Requirements

### Hardware
- **Raspberry Pi Pico** (or any other supported microcontroller using the Pico SDK)
- **Push Button** connected to GPIO pin 16 (or adjust the pin in the code)
- **Seven-Segment Display** with an appropriate driver (using the provided `seven_segment.h` library)
- Breadboard, jumper wires, and necessary components for wiring the button and display

### Software
- [Pico SDK](https://github.com/raspberrypi/pico-sdk) for development on the Raspberry Pi Pico
- A toolchain for compiling and flashing Pico programs (such as CMake and Visual Studio Code or another IDE)
- Standard C libraries: `stdio.h`, `string.h`
- Custom library: `seven_segment.h` (make sure this file is included in your project)

---

## Installation

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/yourusername/morse-code-decoder.git
    cd morse-code-decoder
    ```

2. **Set Up the Pico SDK:**
   - Follow the [official Raspberry Pi Pico SDK setup instructions](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) to configure your development environment.

3. **Add the Seven-Segment Library:**
   - Ensure that `seven_segment.h` (and its corresponding source file, if required) is placed in your project directory or in an include path accessible to your build system.

4. **Configure the Hardware:**
   - Connect the push button to GPIO pin 16 (or modify the `BUTTON_PIN` definition in the code).
   - Wire your seven-segment display as specified by your `seven_segment.h` implementation.
   - Verify all wiring connections before powering the board.

5. **Build and Flash the Code:**
   - Use CMake (or your preferred build system) to compile the project.
   - Flash the generated binary onto your Raspberry Pi Pico.

---

## Usage

1. **Power Up and Run:**
   - Once the code is flashed, power up your Pico. The terminal will display a welcome message:
     ```
     Morse Code Decoder Program Started
     ```

2. **Entering Morse Code:**
   - Press and release the button:
     - A short press (less than 250 ms) is interpreted as a dot (`.`).
     - A longer press (equal to or greater than 250 ms) is interpreted as a dash (`-`).
   - After finishing a Morse sequence (i.e., after a pause longer than the defined letter gap of 1000 ms), the program will decode the sequence and display the corresponding character on the seven-segment display as well as print it to the terminal.

3. **Inactivity Timeout:**
   - If no button presses occur for 5000 ms, the current Morse sequence is cleared automatically.

---

## Code Structure

### `main.c`
This file contains the main program logic:
- **Initialization:**
  - Sets up serial communication, the seven-segment display, and the button GPIO.
- **Main Loop:**
  - Continuously checks for button presses.
  - Measures the press duration to determine dot vs. dash.
  - Uses timing gaps to trigger the decoding of the current Morse sequence.
- **Decoding Functions:**
  - `checkButton()`: Determines if a button press is a dot or a dash.
  - `decoder()`: Converts the accumulated Morse sequence to a character and displays it.
  - `morseToChar()`: Maps known Morse code sequences to their corresponding alphanumeric characters.

