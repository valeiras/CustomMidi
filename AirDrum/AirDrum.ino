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
const byte NB_SENSORS = 2;
const byte MIDI_NOTE[NB_SENSORS] = { 40, 41 };

const byte TRIGGER_PIN = 4;
const byte ECHO_PIN1 = 2;
const byte ECHO_PIN2 = 7;

const unsigned short MAX_DISTANCE_CM = 50;

const float THRESHOLD = 10;
const byte NB_HITS_REQUIRED = 2;
const unsigned int REFACTORY_PERIOD_MS = 50;

unsigned long timeLastNote[NB_SENSORS] = { 0, 0 };
int hitCount[NB_SENSORS] = { 0, 0 };
bool isNoteOn[NB_SENSORS] = { false, false };

#if defined(ATMEGA328) || defined(ATMEGA32U4)
MidiInterface* interface;
#endif

HC_SR04_BASE* slaves[] = { new HC_SR04<ECHO_PIN2>() };
HC_SR04<ECHO_PIN1> sensors(TRIGGER_PIN, slaves, NB_SENSORS - 1);

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
  sensors.beginAsync();
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
  sensors.startAsync();
#endif
}

void loop() {
  for (int ii = 0; ii < sensors.getNumberOfSensors(); ii++) {
    if (sensors.isFinished(ii)) {

      float distance = sensors.getDist_cm(ii);
      if (isNoteOn[ii]) {
        if (distance > THRESHOLD || distance < 0) hitCount[ii]++;
        else hitCount[ii] = 0;
      } else {
        if (distance > 0 && distance < THRESHOLD) hitCount[ii]++;
        else hitCount[ii] = 0;
      }
      if (hitCount[ii] > NB_HITS_REQUIRED && millis() - timeLastNote[ii] > REFACTORY_PERIOD_MS) {
        isNoteOn[ii] = !isNoteOn[ii];
        hitCount[ii] = 0;
        timeLastNote[ii] = millis();
        sendNote(isNoteOn[ii], MIDI_CH, MIDI_NOTE[ii], 64);
      }
      sensors.startAsync(0, ii);
    }
  }

  // // --------- Serial plotter -------
  // Serial.print("Distance 1:");
  // Serial.print(min(sensors.getDist_cm(0), MAX_DISTANCE_CM));
  // Serial.print("Distance 2:");
  // Serial.print(min(sensors.getDist_cm(1), MAX_DISTANCE_CM));
  // Serial.print(", Threshold:");
  // Serial.print(THRESHOLD);
  // Serial.print(", zero:");
  // Serial.print(0);
  // Serial.print(", max:");
  // Serial.println(MAX_DISTANCE_CM);
}
