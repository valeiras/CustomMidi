/////////////////////////////////////////////
// Define your board, choose:
// "ATMEGA328" if using ATmega328 - Uno, Mega, Nano...
// "ATMEGA32U4" if using with ATmega32U4 - Micro, Pro Micro, Leonardo...
// "DEBUG" if you just want to debug the code in the serial monitor

// #define ATMEGA328
#define DEBUG

#ifdef ATMEGA328
#include "midi_interface328.h"
#elif defined(ATMEGA32U4)
#include "midi_interface32U4.h"
#endif

#include <HCSR04.h>
#include "MovingAverage.h"

const byte NB_SENSORS = 2;
const byte MIDI_CH = 1;
const byte MOVING_AVG_LENGTH = 4;
const float MAX_DISTANCE = 35.0;

#if defined(ATMEGA328) || defined(ATMEGA32U4)
MidiInterface *interface;
#endif

const byte triggerPin = 12;
const byte echoPins[NB_SENSORS] = { 6, 11 };
const byte controlChanges[NB_SENSORS] = {20, 21};
const byte channels[NB_SENSORS] = {MIDI_CH, MIDI_CH};
MovingAverage<uint8_t, MOVING_AVG_LENGTH> filters[NB_SENSORS] = {MovingAverage<uint8_t, MOVING_AVG_LENGTH>(), MovingAverage<uint8_t, MOVING_AVG_LENGTH>()};

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

  HCSR04.begin(triggerPin, echoPins, NB_SENSORS);
}

void loop() {
  double* distances = HCSR04.measureDistanceCm();

  for(int ii = 0; ii<NB_SENSORS; ii++){
    if(0.0 < distances[ii] && distances[ii] < MAX_DISTANCE){
      int midiValue = map(distances[ii], 0.0, MAX_DISTANCE, 0, 127);
      filters[ii].add(midiValue);
      #if defined(ATMEGA328) || defined(ATMEGA32U4)
      interface->sendCCMessage(channels[ii], controlChanges[ii], filters[ii].get());
      #else
      Serial.println(filters[ii].get());
      #endif
    }
  }
}
