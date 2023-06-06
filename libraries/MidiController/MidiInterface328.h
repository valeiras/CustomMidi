#ifndef MidiInterface328_h
#define MidiInterface328_h

#ifdef ATMEGA328

#include <MIDI.h>
#include "MidiInterface.h"

MIDI_CREATE_DEFAULT_INSTANCE();

// For boards using ATmega328 - Uno, Mega, Nano...
class MidiInterface328 : public MidiInterface {
public:
  MidiInterface328();

  void sendNoteOn(byte channel, byte control, byte value);
  void sendNoteOff(byte channel, byte control, byte value);
  void sendCCMessage(byte channel, byte control, byte value);
  void flushMidi();
};

MidiInterface328::MidiInterface328() {
   MIDI.begin(MIDI_CHANNEL_OFF);
}

void MidiInterface328::sendNoteOn(byte channel, byte pitch, byte velocity) {
   MIDI.sendNoteOn(pitch, velocity, channel);
}

void MidiInterface328::sendNoteOff(byte channel, byte pitch, byte velocity) {
   MIDI.sendNoteOff(pitch, velocity, channel);
}

void MidiInterface328::sendCCMessage(byte channel, byte control, byte value) {
   MIDI.sendControlChange(control, value, channel);
}

void MidiInterface328::flushMidi() {
}

#endif
#endif