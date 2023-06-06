#ifndef ControllerElements_h
#define ControllerElements_h

#include <Arduino.h>

enum class Commands {
  NOTE,
  CC,
  TOGGLE
};

class Mux
{
  public:
    Mux(byte outpin, byte numPins, bool isAnalog);

    byte _outPin;
    byte _numPins;
    bool _isAnalog;
};

//************************************************************************
//Button (Pin Number, Command, Note Number, Channel, Debounce Time)
class Button
{
  public:
    Button(byte pin, Commands command, byte value, byte channel, byte debounce);
    Button(Mux mux, byte muxPin, Commands command, byte pitch, byte channel, byte debounce);

    byte getValue();
    void muxUpdate();
    
    Commands _command;
    byte _pitch;
    byte _channel;
    byte _toggle;

  private:
    byte previous_;
    byte current_;
    unsigned long time_;
    int debounce_;
    byte pin_;
    byte muxPin_;
    byte numMuxPins_;
    bool isBusy_;
    byte status_;
    byte last_;
    byte enablePin_;
};
//*************************************************************************
class Pot
{
  public:
    Pot(byte pin, byte control, byte channel);
    Pot(Mux mux, byte muxPin, byte control, byte channel);
    
    void muxUpdate();
    byte getValue();

    byte _control;
    byte _channel;

  private:
    byte pin_;
    byte muxPin_;
    byte numMuxPins_;
    int value_;
    int oldValue_;
    bool hasChanged;
    byte enablePin_;
};
//*************************************************************************

#endif