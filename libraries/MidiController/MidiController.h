#ifndef MidiController_h
#define MidiController_h

#include <Arduino.h>

/*************************************************************
  MIDI CONTROLLER

  Modified from the controller by Notes and Volts
  www.notesandvolts.com

//************************************************************/

template <byte NB_BUTTONS, byte NB_POTS, byte NB_MUX_BUTTONS, byte NB_MUX_POTS>
class MidiController {
 public:
  MidiController();

 private:
  Pot *pots_[NB_POTS];
  Button *buttons_[NB_BUTTONS];
  Button *muxButtons_[NB_MUX_BUTTONS];
  Pot *muxPots_[NB_MUX_POTS];
};
#endif
