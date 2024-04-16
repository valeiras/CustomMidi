# CustomMidi

Custom Midi with Arduino

Custom Miid controller based on the Arduino MIDI controller by Notes and Volts. Designed to work with Arduino Uno and and Arduino Pro Micro.

# Installation of the MocoLufa dual boot firmware

## Flash the ATMega16U2

Download and install the [flip software](https://www.microchip.com/en-us/development-tool/FLIP#Software) in order to flash the ATMega16U2.

With the board connected via USB, jump ICSP2 pins 1 and 2 in order to put the Arduino in flash mode.

<img src = "assets/FlashAtMega16U2.png?raw=true" width=400>

Once the Arduino is in flash mode, we should be able to see the ATMega16u2 in the device manager.

Note: for some unofficial boards, I have needed to [burn the bootloader](https://support.arduino.cc/hc/en-us/articles/4841602539164-Burn-the-bootloader-on-UNO-Mega-and-classic-Nano-using-another-Arduino) for this step to work

We then select ATMega16U2 in flip, open the USB connection, load the HEX file and hit RUN. This completes the installation of the MocoLufa dual boot firmware.

## Boot as Arduino

Connect ICSP2 pins 1 and 3 in order to boot the board as an Arduino and upload new sketches.

<img src = "assets/BootAsArduino.png?raw=true" width=400>

# Installation

## MIDI library

Install the [MIDI](https://github.com/FortySevenEffects/arduino_midi_library/releases/tag/5.0.2) library.

## Custom libraries

Move the the content inside "libraries" to the Arduino's libraries folder.

## HC-SR04 library:

For the ultrasonic sensors, install the [HC-SR04](https://github.com/d03n3rfr1tz3/HC-SR04) library.

## MPU-9250

For the gyroscope and accelerometer, install the [MPU-9250](https://github.com/bolderflight/invensense-imu) library.

# Usage
