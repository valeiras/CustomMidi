/////////////////////////////////////////////
// Define your board, choose:
// "ATMEGA328" if using ATmega328 - Uno, Mega, Nano...
// "ATMEGA32U4" if using with ATmega32U4 - Micro, Pro Micro, Leonardo...
// "TEENSY" if using a Teensy board
// "DEBUG" if you just want to debug the code in the serial monitor

#define ATMEGA328

#ifdef ATMEGA328
#include "MidiInterface328.h"
#elif defined(ATMEGA32U4)
#include "MidiInterface32U4.h"
#endif

MidiInterface *midiInterface;

void setup() {
#ifdef ATMEGA328
  midiInterface = new MidiInterface328();
#elif defined(ATMEGA32U4)
  Serial.begin(9600);
  midiInterface = new MidiInterface32U4();
#endif
}

void loop() {
  midiInterface->sendNoteOn(1, 48, 127);  // Channel 1, middle C, normal velocity
  midiInterface->flushMidi();
  delay(500);
  midiInterface->sendNoteOff(1, 48, 127);  // Channel 1, middle C, normal velocity
  midiInterface->flushMidi();
  delay(500);
}