/////////////////////////////////////////////
// Define your board, choose:
// "ATMEGA328" if using ATmega328 - Uno, Mega, Nano...
// "ATMEGA32U4" if using with ATmega32U4 - Micro, Pro Micro, Leonardo...
// "DEBUG" if you just want to debug the code in the serial monitor

// #define ATMEGA328
#define ATMEGA32U4
// #define DEBUG

#ifdef ATMEGA328
#include "midi_interface328.h"
#elif defined(ATMEGA32U4)
#include "midi_interface32U4.h"
#endif

// Pins that accept interrupts in arduino micro: 0, 1, 2, 3, 7

// The library being used is the following: https://github.com/bjoernboeckle/HC_SR04
// In the case of asynchronous measurement, the echo pin must support interrupts.
#include <HC_SR04.h>

const byte MIDI_CH = 1;
const byte MIDI_NOTE = 40;

const byte TRIGGER_PIN = 4;
const byte ECHO_PIN = 2;

const unsigned short MAX_DISTANCE_CM = 50;

const float THRESHOLD = 10;
const byte NB_HITS_REQUIRED = 2;
const unsigned int REFACTORY_PERIOD_MS = 50;

unsigned long timeLastNote = 0;
int hitCount = 0;
bool isNoteOn = false;

#if defined(ATMEGA328) || defined(ATMEGA32U4)
MidiInterface* interface;
#endif

HC_SR04<ECHO_PIN> sensor(TRIGGER_PIN);

void setup() {
#ifdef ATMEGA328
  interface = new MidiInterface328();
#elif defined(ATMEGA32U4)
  Serial.begin(115200);
  interface = new MidiInterface32U4();

#elif defined(DEBUG)
  Serial.begin(9600);
  delay(1000);
#endif
  sensor.beginAsync();
}

void sendNote(bool isNoteOn, byte midiCh, byte midiNote, byte vel) {
#if defined(ATMEGA328) || defined(ATMEGA32U4)
  if (isNoteOn) {
    interface->sendNoteOn(midiCh, midiNote, vel);
  } else {
    interface->sendNoteOff(midiCh, midiNote, vel);
  }
  interface->flushMidi();
#elif defined(DEBUG)
  Serial.print(midiNote);
  if (isNoteOn) {
    Serial.println(": ON!!");
  } else {
    Serial.println(": OFF!!");
  }
  sensor.startAsync();
#endif
}

void loop() {
  if (sensor.isFinished()) {
    float distance = sensor.getDist_cm();
    if (isNoteOn) {
      if (distance > THRESHOLD || distance < 0) hitCount++;
      else hitCount = 0;
    } else {
      if (distance > 0 && distance < THRESHOLD) hitCount++;
      else hitCount = 0;
    }
    if (hitCount > NB_HITS_REQUIRED && millis() - timeLastNote > REFACTORY_PERIOD_MS) {
      isNoteOn = !isNoteOn;
      hitCount = 0;
      timeLastNote = millis();
      sendNote(isNoteOn, MIDI_CH, MIDI_NOTE, 64);
    }
    sensor.startAsync();
  }

  // // --------- Serial plotter -------
  // Serial.print("Distance 1:");
  // Serial.print(min(sensor.getDist_cm(0), MAX_DISTANCE_CM));
  // Serial.print("Distance 2:");
  // Serial.print(min(sensor.getDist_cm(1), MAX_DISTANCE_CM));
  // Serial.print(", Threshold:");
  // Serial.print(THRESHOLD);
  // Serial.print(", zero:");
  // Serial.print(0);
  // Serial.print(", max:");
  // Serial.println(MAX_DISTANCE_CM);
}
