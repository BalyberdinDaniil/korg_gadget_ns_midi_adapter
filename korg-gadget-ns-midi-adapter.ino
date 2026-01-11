/*
  A specialized MIDI-to-HID adapter designed to play "Korg Gadget for Nintendo Switch"™ 
  using any MIDI controller.

  Date: January 11, 2026
  Author: Balyberdin Daniil
  License: MIT
  Github source: https://github.com/BalyberdinDaniil/korg_gadget_ns_midi_adapter/tree/main
*/

#include <MIDI.h>
#include <HID-Project.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void setup() {
  // MIDI Channel selection via DIP-switches (Binary 1-16)
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

  int midiChannel = 0;
  if (!digitalRead(2)) midiChannel += 1;  // Bit 0
  if (!digitalRead(3)) midiChannel += 2;  // Bit 1
  if (!digitalRead(4)) midiChannel += 4;  // Bit 2
  if (!digitalRead(5)) midiChannel += 8;  // Bit 3

  midiChannel += 1; // Convert 0-15 range to 1-16

  // Initialize HID Keyboard
  BootKeyboard.begin();

  // Initialize MIDI on selected channel
  MIDI.begin(midiChannel);
  MIDI.turnThruOff(); // Disable MIDI Thru to save CPU resources
}

// Maps MIDI note to Keyboard character
char getCharForNote(byte note) {
  if (note < 60 || note > 88) return 0;
  switch (note) {
    // Row 1 (Lower)
    case 60: return 'z'; case 61: return 's'; case 62: return 'x'; case 63: return 'd';
    case 64: return 'c'; case 65: return 'v'; case 66: return 'g'; case 67: return 'b';
    case 68: return 'h'; case 69: return 'n'; case 70: return 'j'; case 71: return 'm';
    // Row 2 (Upper)
    case 72: return 'q'; case 73: return '2'; case 74: return 'w'; case 75: return '3';
    case 76: return 'e'; case 77: return 'r'; case 78: return '5'; case 79: return 't';
    case 80: return '6'; case 81: return 'y'; case 82: return '7'; case 83: return 'u';
    case 84: return 'i';
    // Row 3 (Extra)
    case 85: return '9'; case 86: return 'o'; case 87: return '0'; case 88: return 'p';
    default: return 0;
  }
}

// Sends combinations (oct+, oct-)
void sendCombo(KeyboardKeycode modifier, KeyboardKeycode key) {
  BootKeyboard.press(modifier);
  delay(20);
  BootKeyboard.press(key);
  delay(20);
  BootKeyboard.releaseAll();
}

void handleMIDI() {
  byte type = MIDI.getType();
  byte note = MIDI.getData1();
  byte velocity = MIDI.getData2();

  // Identify action: Press or Release
  bool isPress = (type == midi::NoteOn && velocity > 0);
  bool isRelease = (type == midi::NoteOff || (type == midi::NoteOn && velocity == 0));

  switch (type) {
    case midi::NoteOn:
    case midi::NoteOff:
      // Handle System Commands only on NoteOn
      if (isPress) {
        switch (note) {
          case 90:
            sendCombo(KEY_LEFT_CTRL, KEY_LEFT_ARROW);
            return; 
          case 92:
            sendCombo(KEY_LEFT_CTRL, KEY_RIGHT_ARROW);
            return;
          case 94:
            BootKeyboard.releaseAll();
            return;
        }
      }

      // Handle Musical Notes
      {
        char k = getCharForNote(note);
        if (k != 0) {
          if (isPress) BootKeyboard.press(k);
          else if (isRelease) BootKeyboard.release(k);
        }
      }
      break;

    default:
      break;
  }
}

void loop() {
  // Process all pending MIDI messages in a single loop cycle
  while (MIDI.read()) {
    handleMIDI();
  }
}
