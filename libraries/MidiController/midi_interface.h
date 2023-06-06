#ifndef MidiInterface_h
#define MidiInterface_h

#include <Arduino.h>

class MidiInterface {
 public:
  virtual void sendNoteOn(byte channel, byte pitch, byte velocity) = 0;
  virtual void sendNoteOff(byte channel, byte pitch, byte velocity) = 0;
  virtual void sendCCMessage(byte channel, byte control, byte value) = 0;
  virtual void flushMidi() = 0;
};

#endif