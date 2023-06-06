#ifndef MidiInterface32U4_h
#define MidiInterface32U4_h

// "ATMEGA32U4" if using with ATmega32U4 - Micro, Pro Micro, Leonardo...
// Otherwise "MIDIUSB.h won't compile"

#ifdef ATMEGA32U4

#include "MIDIUSB.h"
#include "midi_interface.h"


class MidiInterface32U4 : public MidiInterface {
 public:
  MidiInterface32U4();

  void sendNoteOn(byte channel, byte pitch, byte velocity);
  void sendNoteOff(byte channel, byte pitch, byte velocity);
  void sendCCMessage(byte channel, byte control, byte value);
  void flushMidi();
};

MidiInterface32U4::MidiInterface32U4() {
}

void MidiInterface32U4::sendNoteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = { 0x09, 0x90 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOn);
}

void MidiInterface32U4::sendNoteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = { 0x08, 0x80 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOff);
}

void MidiInterface32U4::sendCCMessage(byte channel, byte control, byte value) {
  midiEventPacket_t event = { 0x0B, 0xB0 | channel, control, value };
  MidiUSB.sendMIDI(event);
}

void MidiInterface32U4::flushMidi() {
  MidiUSB.flush();
}

#endif
#endif