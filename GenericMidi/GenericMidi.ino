/////////////////////////////////////////////
// Define your board, choose:
// "ATMEGA328" if using ATmega328 - Uno, Mega, Nano...
// "ATMEGA32U4" if using with ATmega32U4 - Micro, Pro Micro, Leonardo...
// "TEENSY" if using a Teensy board
// "DEBUG" if you just want to debug the code in the serial monitor

#define ATMEGA32U4

/////////////////////////////////////////////
// LIBRARIES
// -- Defines the MIDI library -- //

// if using with ATmega328 - Uno, Mega, Nano...
#ifdef ATMEGA328
#include <MIDI.h> // by Francois Best
MIDI_CREATE_DEFAULT_INSTANCE();

// if using with ATmega32U4 - Micro, Pro Micro, Leonardo...
#elif ATMEGA32U4
#include "MIDIUSB.h"

#endif

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
