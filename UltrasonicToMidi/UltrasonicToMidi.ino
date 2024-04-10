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

#include <VARSTEP_ultrasonic.h>
#include "MovingAverage.h"

const byte MIDI_CH = 1;
const byte MOVING_AVG_LENGTH = 2;
const float MAX_DISTANCE = 50.0;


#if defined(ATMEGA328) || defined(ATMEGA32U4)
MidiInterface* interface;
#endif

const byte NB_SENSORS = 1;
const byte TRIGGER_PIN = 4;
const byte ECHO_PIN = 6;  // PWM
const byte CC = 20;
byte value = 0;

VARSTEP_ultrasonic HCSR04(TRIGGER_PIN, ECHO_PIN);
MovingAverage<uint8_t, MOVING_AVG_LENGTH> filter;

void setup() {
#ifdef ATMEGA328
  interface = new MidiInterface328();
#elif defined(ATMEGA32U4)
  Serial.begin(9600);
  interface = new MidiInterface32U4();
#elif defined(DEBUG)
  Serial.begin(9600);
  delay(1000);
#endif
}

void loop() {
  long int t1 = millis();
  double distance = HCSR04.distance_cm();

  if (0.0 < distance && distance < MAX_DISTANCE) {
    // int midiValue = map(distances[0], 0.0, MAX_DISTANCE, 0, 127);
    filter.add(distance);
#if defined(ATMEGA328) || defined(ATMEGA32U4)
    // interface->sendCCMessage(MIDI_CH, CC, filter.get());
#endif
#if defined(DEBUG) || defined(ATMEGA32U4)
    Serial.print("Measure:");
    Serial.print(filter.get());
    Serial.print(", Low-limit:");
    Serial.print(0);
    Serial.print(", High-limit:");
    Serial.println(MAX_DISTANCE);
    long int t2 = millis();
    Serial.print("Time:");
    Serial.print(t2 - t1);
#endif
  }
}
