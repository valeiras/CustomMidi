#include "MIDIUSB.h"

#define NB_POT 4
const int POT_PINS[NB_POT] = { A0, A1, A2, A3 };

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Serial.println("Sending note on");
  // noteOn(0, 48, 64);  // Channel 0, middle C, normal velocity
  // MidiUSB.flush();
  // delay(500);
  // Serial.println("Sending note off");
  // noteOff(0, 48, 64);  // Channel 0, middle C, normal velocity
  // MidiUSB.flush();
  // delay(1500);
  Serial.print("0,1023,");
  for (unsigned int ii = 0; ii < NB_POT-1; ii++) {
    Serial.print(analogRead(POT_PINS[ii]));
    Serial.print(",");
    delay(5);
  }
  Serial.println(analogRead(POT_PINS[NB_POT-1]));
  delay(5);
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = { 0x09, 0x90 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = { 0x08, 0x80 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = { 0x0B, 0xB0 | channel, control, value };
  MidiUSB.sendMIDI(event);
}