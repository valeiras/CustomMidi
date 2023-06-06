#ifndef MidiController_h
#define MidiController_h

#include <Arduino.h>

#include "controller_elements.h"
#include "midi_interface.h"

/*************************************************************
  MIDI CONTROLLER

  Modified from the controller by Notes and Volts
  www.notesandvolts.com

//************************************************************/

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
class MidiController {
 public:
  MidiController(MidiInterface *interface);

  void setupButton(byte buttonIdx, byte pin, byte command, byte value, byte channel, byte debounce);
  void setupPot(byte potIdx, byte pin, byte control, byte channel);
  void setupMuxButton(byte buttonIdx, Mux *mux, byte muxPin, byte command, byte value, byte channel, byte debounce);
  void setupMuxPot(byte potIdx, Mux *mux, byte muxPin, byte control, byte channel);

  void setupButtons(byte pins[NB_BUTTONS], byte commands[NB_BUTTONS], byte values[NB_BUTTONS], byte channels[NB_BUTTONS], byte debounces[NB_BUTTONS]);
  void setupPots(byte pins[NB_POTS], byte controls[NB_POTS], byte channels[NB_POTS]);
  void setupMuxButtons(Mux *mux[NB_BUTTONS], byte muxPins[NB_BUTTONS], byte commands[NB_BUTTONS], byte values[NB_BUTTONS], byte channels[NB_BUTTONS], byte debounces[NB_BUTTONS]);
  void setupMuxPots(Mux *mux[NB_POTS], byte muxPins[NB_POTS], byte controls[NB_POTS], byte channels[NB_POTS]);

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
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupButton(byte buttonIdx, byte pin, byte command, byte value, byte channel, byte debounce) {
  if (buttonIdx < NB_BUTTONS) {
    buttons_[buttonIdx] = new Button(pin, command, value, channel, debounce);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupPot(byte potIdx, byte pin, byte control, byte channel) {
  if (potIdx < NB_POTS) {
    pots_[potIdx] = new Pot(pin, control, channel);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupMuxButton(byte buttonIdx, Mux *mux, byte muxPin, byte command, byte value, byte channel, byte debounce) {
  if (buttonIdx < NB_BUTTONS) {
    buttons_[buttonIdx] = new Button(*mux, muxPin, command, value, channel, debounce);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupMuxPot(byte potIdx, Mux *mux, byte muxPin, byte control, byte channel) {
  if (potIdx < NB_POTS) {
    pots_[potIdx] = new Pot(*mux, muxPin, control, channel);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupButtons(byte pins[NB_BUTTONS], byte commands[NB_BUTTONS], byte values[NB_BUTTONS], byte channels[NB_BUTTONS], byte debounces[NB_BUTTONS]) {
  for (unsigned int ii = 0; ii < NB_BUTTONS; ii++) {
    buttons_[ii] = new Button(pins[ii], commands[ii], values[ii], channels[ii], debounces[ii]);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupPots(byte pins[NB_POTS], byte controls[NB_POTS], byte channels[NB_POTS]) {
  for (unsigned int ii = 0; ii < NB_POTS; ii++) {
    pots_[ii] = new Pot(pins[ii], controls[ii], channels[ii]);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupMuxButtons(Mux *mux[NB_BUTTONS], byte muxPins[NB_BUTTONS], byte commands[NB_BUTTONS], byte values[NB_BUTTONS], byte channels[NB_BUTTONS], byte debounces[NB_BUTTONS]) {
  for (unsigned int ii = 0; ii < NB_BUTTONS; ii++) {
    buttons_[ii] = new Button(*(mux[ii]), muxPins[ii], commands[ii], values[ii], channels[ii], debounces[ii]);
  }
}

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
void MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>::setupMuxPots(Mux *mux[NB_POTS], byte muxPins[NB_POTS], byte controls[NB_POTS], byte channels[NB_POTS]) {
  for (unsigned int ii = 0; ii < NB_POTS; ii++) {
    pots_[ii] = new Pot(*(mux[ii]), muxPins[ii], controls[ii], channels[ii]);
  }
}

#endif
