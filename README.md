# Arduino library for the Pololu Dual G2 High Power Motor Driver Shields

Version: 2.0.0<br>
Release Date: 2018-04-11<br>
[![Build Status](https://travis-ci.org/pololu/dual-g2-high-power-motor-shield.svg?branch=master)](https://travis-ci.org/pololu/dual-g2-high-power-motor-shield)<br>
[www.pololu.com](https://www.pololu.com/)

## Summary

This is a library for the Arduino IDE that interfaces with the Pololu
[Dual G2 High Power Motor Driver Shield 18v18](https://www.pololu.com/catalog/product/2515),
[Dual G2 High Power Motor Driver Shield 24v14](https://www.pololu.com/catalog/product/2516),
[Dual G2 High Power Motor Driver Shield 18v22](https://www.pololu.com/catalog/product/2517),
and [Dual G2 High Power Motor Driver Shield 24v18](https://www.pololu.com/catalog/product/2518).
It makes it simple to drive two brushed, DC motors.

## Supported platforms

This library is designed to work with the Arduino IDE versions 1.8.x
or later; we have not tested it with earlier versions.  This library
should support any Arduino-compatible board, including the
[Pololu A-Star 32U4 controllers](https://www.pololu.com/category/149/a-star-programmable-controllers).

## Getting started

### Hardware

The
[Dual G2 High Power Motor Driver Shields](https://www.pololu.com/category/218/pololu-dual-g2-high-power-motor-driver-shields)
can be purchased from Pololu's website.  Before continuing, careful
reading of the product page as well as the
[product user's guide](https://www.pololu.com/docs/0J72) is
recommended.

### Software

If you are using version 1.8.5 or later of the
[Arduino software (IDE)](https://www.arduino.cc/en/Main/Software), you can use
the Library Manager to install this library:

1. In the Arduino IDE, open the "Sketch" menu, select "Include Library", then
   "Manage Libraries...".
2. Search for "DualG2HighPowerMotorShield".
3. Click the DualG2HighPowerMotorShield entry in the list.
4. Click "Install".

If this does not work, you can manually install the library:

1. Download the
   [latest release archive from GitHub](https://github.com/pololu/dual-g2-high-power-motor-shield/releases)
   and decompress it.
2. Rename the folder "dual-g2-high-power-motor-shield-xxxx" to "DualG2HighPowerMotorShield".
3. Drag the "DualG2HighPowerMotorShield" folder into the "libraries"
   directory inside your Arduino sketchbook directory.  You can view
   your sketchbook location by opening the "File" menu and selecting
   "Preferences" in the Arduino IDE.  If there is not already a
   "libraries" folder in that location, you should make the folder
   yourself.
4. After installing the library, restart the Arduino IDE.


## Example

An example sketch is available that shows how to use the library.  You
can access it from the Arduino IDE by opening the "File" menu,
selecting "Examples", and then selecting "DualG2HighPowerMotorShield".  If
you cannot find these examples, the library was probably installed
incorrectly and you should retry the installation instructions above.

### Demo

The demo enables the drivers and ramps motor 1 from stopped to full speed
forward, ramps down to full speed reverse, and back to stopped.  Then, it
does the same with the other motor.  After motor 2 is stopped, sleep mode is
entered for 500 ms before the demo enables the drivers again.  Current
readings for each motor are sent over serial and can be seen with the serial
monitor.  If a fault is detected, a message is sent over serial.

## Documentation

This library defines a `DualG2HighPowerMotorShield` base class that implements
commands common to all versions of the Dual G2 High Power Motor Driver Shields.
Four derived classes,`DualG2HighPowerMotorShield24v14`,
`DualG2HighPowerMotorShield18v18`, `DualG2HighPowerMotorShield24v18`,
and `DualG2HighPowerMotorShield18v22`, handle commands specific to each version.

### Library Reference

#### DualG2HighPowerMotorShield

- `DualG2HighPowerMotorShield()`<br> Default constructor, selects the
  default pins as connected by the motor shield.
- `DualG2HighPowerMotorShield(unsigned char M1nSLEEP, unsigned char
  M1DIR, unsigned char M1PWM, unsigned char M1nFAULT, unsigned char
  M1CS, unsigned char M2nSLEEP, unsigned char M2DIR, unsigned char
  M2PWM, unsigned char M2nFAULT, unsigned char M2CS)` <br> Alternate
  constructor for shield connections remapped by user. If M1PWM and
  M2PWM are remapped, it will try to use analogWrite instead of
  timer1.
- `void init()` <br> Initialize pinModes and timer1.
- `void setM1Speed(int speed)` <br> Set speed and direction for motor 1.
  Speed should be between -400 and 400.  400 corresponds to motor
  current flowing from M1A to M1B.  -400 corresponds to motor current
  flowing from M1B to M1A.  0 corresponds to full coast.
- `void setM2Speed(int speed)` <br> Set speed and direction for motor 2.
  Speed should be between -400 and 400.  400 corresponds to motor
  current flowing from M2A to M2B.  -400 corresponds to motor current
  flowing from M2B to M2A.  0 corresponds to full coast.
- `void setSpeeds(int m1Speed, int m2Speed)` <br> Set speed and direction
  for motor 1 and 2.
- `unsigned char getM1Fault()` <br> Returns 1 if there is a fault on motor
  driver 1, 0 if no fault.
- `unsigned char getM2Fault()` <br> Returns 1 if there is a fault on motor
  driver 2, 0 if no fault.
- `void flipM1(bool flip)` <br> Flip the direction meaning of the speed
  passed to the setSpeeds function for motor 1. The default direction
  corresponds to flipM1(false) having been called.
- `void flipM2(bool flip)` <br> Flip the direction meaning of the speed
  passed to the setSpeeds function for motor 2. The default direction
  corresponds to flipM2(false) having been called.
- `void enableM1Driver()` <br> Enables the MOSFET driver for motor 1.
- `void enableM2Driver()` <br> Enables the MOSFET driver for motor 2.
- `void enableDrivers()` <br> Enables the MOSFET drivers for motor 1 and
  motor 2.
- `void disableM1Driver()` <br> Puts the MOSFET driver for motor 1 into
  low-power sleep mode.
- `void disableM2Driver()` <br> Puts the MOSFET driver for motor 2 into
  low-power sleep mode.
- `void disableDrivers()` <br> Puts the MOSFET drivers for motor 1 and
  2 into low-power sleep mode.
- `unsigned int getM1CurrentReading()` <br> Returns current reading from
  motor 1
- `unsigned int getM2CurrentReading()` <br> Returns current reading from
  motor 2
- `void calibrateM1CurrentOffset()` <br> Records the voltage offset of the
  current reading from motor 1 when speed is 0.
- `void calibrateM2CurrentOffset()` <br> Records the voltage offset of the
  current reading from motor 2 when speed is 0.
- `void calibrateCurrentOffsets()` <br> Records the voltage offsets of the
  current readings from motor 1 and 2 when speeds are 0.
- `unsigned int getM1CurrentMilliamps(int gain)` <br> Returns current
  reading for motor 1 in milliamps.  Gain (mV/A) can be specified for a
  specific version of the shield.
- `unsigned int getM2CurrentMilliamps(int gain)` <br> Returns current
  reading for motor 2 in milliamps.  Gain (mV/A) can be specified for a
  specific version of the shield.

#### DualG2HighPowerMotorShield24v14, DualG2HighPowerMotorShield18v18, DualG2HighPowerMotorShield24v18, DualG2HighPowerMotorShield18v22

- `unsigned int getM1CurrentMilliamps()` <br> Returns current reading for
  motor 1 in milliamps.
- `unsigned int getM2CurrentMilliamps()` <br> Returns current reading for
  motor 2 in milliamps.

### Current readings

The current readings returned by `getM1CurrentMilliamps` and
`getM2CurrentMilliamps` will be noisy and unreliable if you are using
a PWM frequency below about 5&nbsp;kHz.  We expect these readings to
work fine if you are using a board based on the ATmega168, ATmega328P,
or ATmega32U4, since this library uses 20&nbsp;kHz hardware PWM on
those boards.

On other boards, this library uses `analogWrite` to generate PWM
signals, which usually means that the PWM frequency will be too low to
get reliable current measurements.

## Version history
* 2.0.0 (2018-04-11): Allow PWM remapping (use analogWrite if PWM pins
  remapped).
* 1.0.0 (2017-11-09): Original release.
