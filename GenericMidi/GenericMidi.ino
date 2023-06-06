/////////////////////////////////////////////
// Define your board, choose:
// "ATMEGA328" if using ATmega328 - Uno, Mega, Nano...
// "ATMEGA32U4" if using with ATmega32U4 - Micro, Pro Micro, Leonardo...
// "TEENSY" if using a Teensy board
// "DEBUG" if you just want to debug the code in the serial monitor

#define ATMEGA328

#ifdef ATMEGA328
#include "midi_interface328.h"
#elif defined(ATMEGA32U4)
#include "midi_interface32U4.h"
#endif

#include "midi_controller.h"

const byte NB_BUTTONS = 0;
const byte NB_POTS = 4;
const byte NB_MUX_BUTTONS = 0;
const byte NB_MUX_POTS = 0;

const byte MIDI_CH = 1;

MidiInterface *interface;
MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS> *controller;


void setup() {
#ifdef ATMEGA328
  interface = new MidiInterface328();
#elif defined(ATMEGA32U4)
  Serial.begin(9600);
  interface = new MidiInterface32U4();
#endif
  controller = new MidiController<NB_BUTTONS, NB_POTS, NB_MUX_BUTTONS, NB_MUX_POTS>(interface);
  
  byte pins[NB_POTS] = {A0, A1, A2, A3};
  byte controlChanges[NB_POTS] = {20, 21, 22, 23};
  byte channels[NB_POTS] = {MIDI_CH, MIDI_CH, MIDI_CH, MIDI_CH};

  controller->setupPots(pins, controlChanges, channels);
}

void loop() {
  interface->sendNoteOn(1, 48, 127);  // Channel 1, middle C, normal velocity
  interface->flushMidi();
  delay(500);
  interface->sendNoteOff(1, 48, 127);  // Channel 1, middle C, normal velocity
  interface->flushMidi();
  delay(500);
}