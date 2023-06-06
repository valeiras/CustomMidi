#ifndef ControllerElements_h
#define ControllerElements_h

#include <Arduino.h>

class Mux
{
  public:
    Mux(byte _outpin, byte _numPins, bool _isAnalog);

    byte outPin;
    byte numPins;
    bool isAnalog;
};

//************************************************************************
//Button (Pin Number, Command, Note Number, Channel, Debounce Time)
class Button
{
  public:
    Button(byte pin, byte command, byte value, byte channel, byte debounce);
    Button(Mux mux, byte muxpin, byte command, byte value, byte channel, byte debounce);

    byte getValue();
    void muxUpdate();
    void newValue(byte command, byte value, byte channel);
    
    byte Bcommand;
    byte Bvalue;
    byte Bchannel;
    byte Btoggle;

  private:
    byte previous_;
    byte current_;
    unsigned long time_;
    int debounce_;
    byte pin_;
    byte muxPin_;
    byte numMuxPins_;
    byte value_;
    byte command_;
    bool isBusy_;
    byte status_;
    byte last_;
    byte enablePin_;
};
//*************************************************************************
class Pot
{
  public:
    Pot(byte pin, byte command, byte control, byte channel);
    Pot(Mux mux, byte muxpin ,byte command, byte control, byte channel);
    
    void muxUpdate();
    void newValue(byte command, byte value, byte channel);
    byte getValue();
    
    byte Pcommand;
    byte Pcontrol;
    byte Pchannel;

  private:
    byte pin_;
    byte muxPin_;
    byte numMuxPins_;
    byte control_;
    int value_;
    int oldValue_;
    bool hasChanged;
    byte enablePin_;
};
//*************************************************************************

#endif