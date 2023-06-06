#include "controller_elements.h"

//****************************************************************************************
Mux::Mux(byte outPin, byte numPins, bool isAnalog) {
  _outPin = outPin;
  _numPins = numPins;
  _isAnalog = isAnalog;

  if (!_isAnalog) {
    pinMode(_outPin, INPUT_PULLUP);
  }

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  if (_numPins > 8){
   pinMode(5, OUTPUT);
  }
}

//****************************************************************************************
// Command can be: 
//    · 0 for notes
//    · 1 for CC
//    · 2 for toggle
// Button (Pin Number, Command, Note Number, Channel, Debounce Time)
Button::Button(byte pin, Commands command, byte pitch, byte channel, byte debounce) {
  pin_ = pin;
  pinMode(pin_, INPUT_PULLUP);
  debounce_ = debounce;

  time_ = 0;
  isBusy_ = false;
  status_ = 0b00000010;
  last_ = 1;
  
  _command = command;
  _pitch = pitch;
  _channel = channel;
  _toggle = 0;
}

Button::Button(Mux mux, byte muxPin, Commands command, byte pitch, byte channel, byte debounce) {
  pin_ = mux._outPin;
  numMuxPins_ = mux._numPins;
  muxPin_ = muxPin;
  debounce_ = debounce;
  
  time_ = 0;
  isBusy_ = false;
  status_ = 0b00000010;
  last_ = 1;
  
  _command = command;
  _pitch = pitch;
  _channel = channel;
  _toggle = 0;
}

void Button::muxUpdate() {
  byte temp = muxPin_;
  temp = temp << 2;
  // Port registers allow for lower-level and faster manipulation of the i/o pins of the microMidiController on an Arduino board. The chips used on the Arduino board (the ATmega8 and ATmega168) have three ports:
  // B (digital pin 8 to 13)
  // C (analog input pins)
  // D (digital pins 0 to 7)

  // We set to LOW the digital pins between 2 and 5 for more than 8 pins, or from 2 to 4 for less than 8
  if (numMuxPins_ > 8)
    PORTD = PORTD & B11000011;
  else
    PORTD = PORTD & B11100011;

  // We then set to HIGH the digital pins corresponding to the address
  PORTD = PORTD | temp;
}

byte Button::getValue() {
  // If BUSY bit not set - read button
  if (bitRead(status_, 0) == false) {          // If busy false
    if (digitalRead(pin_) == last_) return 2;  // If same as last state - exit
  }

  // If NEW Bit set - Key just pressed, record time
  if (bitRead(status_, 1) == true) {  // If new is true
    bitSet(status_, 0);               // Set busy TRUE
    bitClear(status_, 1);             // Set New FALSE
    time_ = millis();
    return 255;
  }

  // Check if debounce time has passed - If no, exit
  if (millis() - time_ < debounce_) return 255;

  // Debounce time has passed. Read pin to see if still set the same
  // If it has changed back - assume false alarm
  if (digitalRead(pin_) == last_) {
    bitClear(status_, 0);  // Set busy false
    bitSet(status_, 1);    // Set new true
    return 255;
  }

  // If this point is reached, event is valid. return event type
  else {
    bitClear(status_, 0);             // Set busy false
    bitSet(status_, 1);               // Set new true
    last_ = ((~last_) & 0b00000001);  // invert last_
    return last_;
  }
}

//********************************************************************
Pot::Pot(byte pin, byte control, byte channel) {
  pin_ = pin;

  value_ = analogRead(pin_);
  value_ = value_ >> 3;
  oldValue_ = value_ << 3;
  value_ = value_ << 3;
  
  _control = control;
  _channel = channel;
}

void Pot::muxUpdate() {
  byte temp = muxPin_;
  temp = temp << 2;
  if (numMuxPins_ > 8)
    PORTD = PORTD & B11000011;
  else
    PORTD = PORTD & B11100011;
  // PORTD = PORTD & B11000011;
  PORTD = PORTD | temp;
}

Pot::Pot(Mux mux, byte muxPin, byte control, byte channel) {
  pin_ = mux._outPin;
  numMuxPins_ = mux._numPins;
  muxPin_ = muxPin;
  muxUpdate();
  
  value_ = analogRead(pin_);
  value_ = value_ >> 3;
  oldValue_ = value_ << 3;
  value_ = value_ << 3;

  _control = control;
  _channel = channel;
}

byte Pot::getValue() {
  value_ = analogRead(pin_);
  int tmp = (oldValue_ - value_);
  // Analog read gives values between 0 and 1023 (10 bytes), while MIDI only uses 7 bytes. So we reject the three rightmost buts
  if (tmp >= 8 || tmp <= -8) {
    oldValue_ = value_ >> 3;
    oldValue_ = oldValue_ << 3;
    return value_ >> 3;
  }
  return 255;
}