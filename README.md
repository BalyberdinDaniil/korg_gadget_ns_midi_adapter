# MIDI-to-HID Adapter for "Korg Gadget for Nintendo Switch"™

A specialized bridge that allows you to play **Korg Gadget for Nintendo Switch** using any standard MIDI controller. It converts MIDI notes into HID keyboard strokes with low latency and includes hardware configuration options.

## Features
- **Plug & Play:** Recognized by Nintendo Switch as a standard USB Keyboard.
- **Musical Mapping:** Full support for the Gadget keyboard layout (Z-M, Q-I, 9-P).
- **Octave Control:** Dedicated MIDI notes to switch octaves within the Gadget interface.
- **Hardware Channel Select:** Use 4 DIP-switches to set the MIDI channel (1-16) on startup.
- **Panic Button:** Dedicated MIDI note to release all stuck keys.

## Hardware Requirements
- **Microcontroller:** Arduino Pro Micro, Leonardo, or any ATmega32U4-based board (required for USB HID support).
- **MIDI Input:** 5-pin DIN MIDI (ready-made module)
- **Channel Selector (Optional):** 4-position DIP switch.

## MIDI Channel Selection (DIP Switches)

The MIDI channel is determined at startup by the state of pins 2, 3, 4, and 5. 
**Note:** `OFF` means the pin is HIGH (internal pull-up), `ON` means the pin is connected to **GND**.

| Switch 1 (Pin 2) | Switch 2 (Pin 3) | Switch 3 (Pin 4) | Switch 4 (Pin 5) | MIDI Channel |
| :--- | :--- | :--- | :--- | :--- |
| OFF | OFF | OFF | OFF | 1 |
| ON | OFF | OFF | OFF | 2 |
| OFF | ON | OFF | OFF | 3 |
| ON | ON | OFF | OFF | 4 |
| OFF | OFF | ON | OFF | 5 |
| ON | OFF | ON | OFF | 6 |
| OFF | ON | ON | OFF | 7 |
| ON | ON | ON | OFF | 8 |
| OFF | OFF | OFF | ON | 9 |
| ON | OFF | OFF | ON | 10 |
| OFF | ON | OFF | ON | 11 |
| ON | ON | OFF | ON | 12 |
| OFF | OFF | ON | ON | 13 |
| ON | OFF | ON | ON | 14 |
| OFF | ON | ON | ON | 15 |
| ON | ON | ON | ON | 16 |

## Musical Range

The adapter maps MIDI notes to the Gadget keyboard in the following range:
- **MIDI Notes:** `60` — `88`
- **Notation:** `C3` — `E5`
- **Keyboard Layout:** Mapped to keys `Z` through `P` (including numbers for sharps).

*Notes outside this range are ignored unless they are System Commands (90, 92, 94).*

## System Commands (MIDI Notes)
- **Note 90:** Switch Octave Down (Ctrl + Left Arrow)
- **Note 92:** Switch Octave Up (Ctrl + Right Arrow)
- **Note 94:** Emergency Release All Keys

## Installation
1. Install the [HID-Project](https://github.com/NicoHood/HID) and [Arduino MIDI Library](https://github.com/FortySevenEffects/arduino_midi_library) in your Arduino IDE.
2. Upload the provided `.ino` sketch to your board.
3. Connect the Arduino to your Nintendo Switch via USB.
4. Set the desired MIDI channel using the DIP switches and power on the device.

## Author
**Balyberdin Daniil** Date: January 11, 2026

## License
This project is licensed under the **MIT License**.
