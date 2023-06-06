#ifndef MidiController_h
#define MidiController_h

#include <Arduino.h>

#include "controller_elements.h"
#include "midi_interface.h"

/*************************************************************
  MIDI CONTROLLER

  Derived from the great controller by the great Notes and Volts
  www.notesandvolts.com

//************************************************************/

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
class MidiController {
 public:
  MidiController(MidiInterface *interface);

  void setupButton(byte buttonIdx, byte pin, Commands command, byte pitch, byte channel, byte debounce);
  void setupPot(byte potIdx, byte pin, byte control, byte channel);
  void setupMuxButton(byte buttonIdx, Mux *mux, byte muxPin, Commands command, byte pitch, byte channel, byte debounce);
  void setupMuxPot(byte potIdx, Mux *mux, byte muxPin, byte control, byte channel);

  void setupButtons(byte pins[NB_BUTTONS], Commands commands[NB_BUTTONS], byte pitches[NB_BUTTONS], byte channels[NB_BUTTONS], byte debounces[NB_BUTTONS]);
  void setupPots(byte pins[NB_POTS], byte controls[NB_POTS], byte channels[NB_POTS]);
  void setupMuxButtons(Mux *mux[NB_BUTTONS], byte muxPins[NB_BUTTONS], Commands commands[NB_BUTTONS], byte pitches[NB_BUTTONS], byte channels[NB_BUTTONS], byte debounces[NB_BUTTONS]);
  void setupMuxPots(Mux *mux[NB_POTS], byte muxPins[NB_POTS], byte controls[NB_POTS], byte channels[NB_POTS]);

  void updateButtons();
  void updateMuxButtons();
  void updatePots();
  void updateMuxPots();

 private:
  Pot *pots_[NB_POTS];
  Button *buttons_[NB_BUTTONS];
  Button *muxButtons_[NB_MUX_BUTTONS];
  Pot *muxPots_[NB_MUX_POTS];

  MidiInterface *interface_;
};

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::MidiController(MidiInterface *interface) {
  interface_ = interface;
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupButton(byte buttonIdx, byte pin, Commands command, byte pitch, byte channel, byte debounce) {
  if (buttonIdx < NB_BUTTONS) {
    buttons_[buttonIdx] = new Button(pin, command, pitch, channel, debounce);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupPot(byte potIdx, byte pin, byte control, byte channel) {
  if (potIdx < NB_POTS) {
    pots_[potIdx] = new Pot(pin, control, channel);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupMuxButton(byte buttonIdx, Mux *mux, byte muxPin, Commands command, byte pitch, byte channel, byte debounce) {
  if (buttonIdx < NB_BUTTONS) {
    buttons_[buttonIdx] = new Button(*mux, muxPin, command, pitch, channel, debounce);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupMuxPot(byte potIdx, Mux *mux, byte muxPin, byte control, byte channel) {
  if (potIdx < NB_POTS) {
    pots_[potIdx] = new Pot(*mux, muxPin, control, channel);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupButtons(byte pins[NB_BUTTONS], Commands commands[NB_BUTTONS], byte pitches[NB_BUTTONS], byte channels[NB_BUTTONS], byte debounces[NB_BUTTONS]) {
  for (unsigned int ii = 0; ii < NB_BUTTONS; ii++) {
    buttons_[ii] = new Button(pins[ii], commands[ii], pitches[ii], channels[ii], debounces[ii]);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupPots(byte pins[NB_POTS], byte controls[NB_POTS], byte channels[NB_POTS]) {
  for (unsigned int ii = 0; ii < NB_POTS; ii++) {
    pots_[ii] = new Pot(pins[ii], controls[ii], channels[ii]);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupMuxButtons(Mux *mux[NB_BUTTONS], byte muxPins[NB_BUTTONS], Commands commands[NB_BUTTONS], byte pitches[NB_BUTTONS], byte channels[NB_BUTTONS], byte debounces[NB_BUTTONS]) {
  for (unsigned int ii = 0; ii < NB_BUTTONS; ii++) {
    buttons_[ii] = new Button(*(mux[ii]), muxPins[ii], commands[ii], pitches[ii], channels[ii], debounces[ii]);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupMuxPots(Mux *mux[NB_POTS], byte muxPins[NB_POTS], byte controls[NB_POTS], byte channels[NB_POTS]) {
  for (unsigned int ii = 0; ii < NB_POTS; ii++) {
    pots_[ii] = new Pot(*(mux[ii]), muxPins[ii], controls[ii], channels[ii]);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::updateButtons() {
  // Cycle through Button array
  for (unsigned int ii = 0; ii < NB_BUTTONS; ii++) {
    byte message = buttons_[ii]->getValue();

    // Serial.println("Updating buttons");
    //  Serial.print("Updating button ");
    //  Serial.print(ii);
    //  Serial.print(" with message ");
    //  Serial.println(message);

    //  Button is pressed
    if (message == 0) {
      switch (buttons_[ii]->_command) {
        case Commands::NOTE:
          interface_->sendNoteOn(buttons_[ii]->_channel, buttons_[ii]->_pitch, 127);
          break;
        case Commands::CC:
          interface_->sendCCMessage(buttons_[ii]->_channel, buttons_[ii]->_pitch, 127);
          break;
        case Commands::TOGGLE:
          if (buttons_[ii]->_toggle == 0) {
            interface_->sendCCMessage(buttons_[ii]->_channel, buttons_[ii]->_pitch, 127);
            buttons_[ii]->_toggle = 1;
          } else if (buttons_[ii]->_toggle == 1) {
            interface_->sendCCMessage(buttons_[ii]->_channel, buttons_[ii]->_pitch, 0);
            buttons_[ii]->_toggle = 0;
          }
          break;
      }
    }

    //  Button is not pressed
    if (message == 1) {
      switch (buttons_[ii]->_command) {
        case Commands::NOTE:
          interface_->sendNoteOff(buttons_[ii]->_channel, buttons_[ii]->_pitch, 127);
          break;
        case Commands::CC:
          interface_->sendCCMessage(buttons_[ii]->_channel, buttons_[ii]->_pitch, 0);
          break;
      }
    }
  }
  interface_->flushMidi();
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::updateMuxButtons() {
  interface_->flushMidi();
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::updatePots() {
  for (unsigned int ii = 0; ii < NB_POTS; ii++) {
    byte potmessage = pots_[ii]->getValue();
    if (potmessage != 255) {
      interface_->sendCCMessage(pots_[ii]->_channel, pots_[ii]->_control, potmessage);
    }
  }
  interface_->flushMidi();
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::updateMuxPots() {
  interface_->flushMidi();
}

#endif
