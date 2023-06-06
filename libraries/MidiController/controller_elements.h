#ifndef ControllerElements_h
#define ControllerElements_h

#include <Arduino.h>

class Mux
{
  public:
    Mux(byte outpin, byte numPins, bool isAnalog);

    byte outPin_;
    byte numPins_;
    bool isAnalog_;
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
    Pot(byte pin, byte control, byte channel);
    Pot(Mux mux, byte muxpin, byte control, byte channel);
    
    void muxUpdate();
    void newValue(byte value, byte channel);
    byte getValue();

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