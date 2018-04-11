#include "DualG2HighPowerMotorShield.h"

boolean DualG2HighPowerMotorShield::_flipM1 = false;
boolean DualG2HighPowerMotorShield::_flipM2 = false;

// Constructors ////////////////////////////////////////////////////////////////

DualG2HighPowerMotorShield::DualG2HighPowerMotorShield()
{
  _M1nSLEEP = 2;
  _M1nFAULT = 6;
  _M1DIR = 7;
  _M1PWM = 9;
  _M1CS = A0;

  _M2nSLEEP = 4;
  _M2nFAULT = 12;
  _M2DIR = 8;
  _M2PWM = 10;
  _M2CS = A1;
}

DualG2HighPowerMotorShield::DualG2HighPowerMotorShield(unsigned char M1nSLEEP,
                                                       unsigned char M1DIR,
                                                       unsigned char M1PWM,
                                                       unsigned char M1nFAULT,
                                                       unsigned char M1CS,
                                                       unsigned char M2nSLEEP,
                                                       unsigned char M2DIR,
                                                       unsigned char M2PWM,
                                                       unsigned char M2nFAULT,
                                                       unsigned char M2CS)
{
  _M1nSLEEP = M1nSLEEP;
  _M1nFAULT = M1nFAULT;
  _M1DIR = M1DIR;
  _M1PWM = M1PWM;
  _M1CS = M1CS;

  _M2nSLEEP = M2nSLEEP;
  _M2nFAULT = M2nFAULT;
  _M2DIR = M2DIR;
  _M2PWM = M2PWM;
  _M2CS = M2CS;
}

// Public Methods //////////////////////////////////////////////////////////////
void DualG2HighPowerMotorShield::init()
{
  pinMode(_M1nSLEEP, OUTPUT);
  pinMode(_M2nSLEEP, OUTPUT);
  pinMode(_M1PWM, OUTPUT);
  pinMode(_M1nFAULT, INPUT_PULLUP);
  pinMode(_M1CS, INPUT);
  pinMode(_M1DIR, OUTPUT);
  pinMode(_M2DIR, OUTPUT);
  pinMode(_M2PWM, OUTPUT);
  pinMode(_M2nFAULT, INPUT_PULLUP);
  pinMode(_M2CS, INPUT);

#ifdef DUALG2HIGHPOWERMOTORSHIELD_TIMER1_AVAILABLE
  if (_M1PWM == _M1PWM_TIMER1_PIN && _M2PWM == _M2PWM_TIMER1_PIN)
  {
    // Timer 1 configuration
    // prescaler: clockI/O / 1
    // outputs enabled
    // phase-correct PWM
    // top of 400
    //
    // PWM frequency calculation
    // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
    TCCR1A = 0b10100000;
    TCCR1B = 0b00010001;
    ICR1 = 400;
  }
#endif
}
// Set speed for motor 1, speed is a number betwenn -400 and 400
void DualG2HighPowerMotorShield::setM1Speed(int speed)
{
  unsigned char reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;

#ifdef DUALG2HIGHPOWERMOTORSHIELD_TIMER1_AVAILABLE
  if (_M1PWM == _M1PWM_TIMER1_PIN && _M2PWM == _M2PWM_TIMER1_PIN)
  {
    OCR1A = speed;
  }
  else
  {
    analogWrite(_M1PWM, speed * 51 / 80); // map 400 to 255
  }
#else
  analogWrite(_M1PWM, speed * 51 / 80); // map 400 to 255
#endif

  if (reverse ^ _flipM1) // flip if speed was negative or _flipM1 setting is active, but not both
  {
    digitalWrite(_M1DIR, HIGH);
  }
  else
  {
    digitalWrite(_M1DIR, LOW);
  }
}

// Set speed for motor 2, speed is a number betwenn -400 and 400
void DualG2HighPowerMotorShield::setM2Speed(int speed)
{
  unsigned char reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // make speed a positive quantity
    reverse = 1;  // preserve the direction
  }
  if (speed > 400)  // Max
    speed = 400;

#ifdef DUALG2HIGHPOWERMOTORSHIELD_TIMER1_AVAILABLE
  if (_M1PWM == _M1PWM_TIMER1_PIN && _M2PWM == _M2PWM_TIMER1_PIN)
  {
    OCR1B = speed;
  }
  else
  {
    analogWrite(_M2PWM, speed * 51 / 80); // map 400 to 255
  }
#else
  analogWrite(_M2PWM, speed * 51 / 80); // map 400 to 255
#endif

  if (reverse ^ _flipM2) // flip if speed was negative or _flipM1 setting is active, but not both
  {
    digitalWrite(_M2DIR, HIGH);
  }
  else
  {
    digitalWrite(_M2DIR, LOW);
  }
}

// Set speed for motor 1 and 2
void DualG2HighPowerMotorShield::setSpeeds(int m1Speed, int m2Speed)
{
  setM1Speed(m1Speed);
  setM2Speed(m2Speed);
}

// Return error status for motor 1
unsigned char DualG2HighPowerMotorShield::getM1Fault()
{
  return !digitalRead(_M1nFAULT);
}

// Return error status for motor 2
unsigned char DualG2HighPowerMotorShield::getM2Fault()
{
  return !digitalRead(_M2nFAULT);
}

void DualG2HighPowerMotorShield::flipM1(boolean flip)
{
  DualG2HighPowerMotorShield::_flipM1 = flip;
}

void DualG2HighPowerMotorShield::flipM2(boolean flip)
{
  DualG2HighPowerMotorShield::_flipM2 = flip;
}

// Enables the MOSFET driver for M1.
void DualG2HighPowerMotorShield::enableM1Driver()
{
  digitalWrite(_M1nSLEEP, HIGH);
}

// Enables the MOSFET driver for M2.
void DualG2HighPowerMotorShield::enableM2Driver()
{
  digitalWrite(_M2nSLEEP, HIGH);
}

// Enables the MOSFET drivers for both M1 and M2.
void DualG2HighPowerMotorShield::enableDrivers()
{
  enableM1Driver();
  enableM2Driver();
}

// Puts the MOSFET driver for M1 into sleep mode.
void DualG2HighPowerMotorShield::disableM1Driver()
{
  digitalWrite(_M1nSLEEP, LOW);
}

// Puts the MOSFET driver for M2 into sleep mode.
void DualG2HighPowerMotorShield::disableM2Driver()
{
  digitalWrite(_M2nSLEEP, LOW);
}

// Puts the MOSFET drivers for both M1 and M2 into sleep mode.
void DualG2HighPowerMotorShield::disableDrivers()
{
  disableM1Driver();
  disableM2Driver();
}

unsigned int DualG2HighPowerMotorShield::getM1CurrentReading()
{
  return analogRead(_M1CS);
}

unsigned int DualG2HighPowerMotorShield::getM2CurrentReading()
{
  return analogRead(_M2CS);
}

// Set voltage offset of M1 current reading at 0 speed.
void DualG2HighPowerMotorShield::calibrateM1CurrentOffset()
{
  setM1Speed(0);
  enableM1Driver();
  delay(1);
  DualG2HighPowerMotorShield::_offsetM1 = getM1CurrentReading();
}

// Set voltage offset of M2 current reading at 0 speed.
void DualG2HighPowerMotorShield::calibrateM2CurrentOffset()
{
  setM2Speed(0);
  enableM2Driver();
  delay(1);
  DualG2HighPowerMotorShield::_offsetM2 = getM2CurrentReading();
}

// Get voltage offset of M1 and M2 current readings.
void DualG2HighPowerMotorShield::calibrateCurrentOffsets()
{
  setSpeeds( 0, 0);
  enableDrivers();
  delay(1);
  DualG2HighPowerMotorShield::_offsetM1 = getM1CurrentReading();
  DualG2HighPowerMotorShield::_offsetM2 = getM2CurrentReading();
}


// Return M1 current value in milliamps using the gain value for the specific version.
unsigned int DualG2HighPowerMotorShield::getM1CurrentMilliamps(int gain)
{
  // 5V / 1024 ADC counts / gain mV per A
  // The 24v14, 18v18 and 24v18 results in 244 mA per count.
  // The 18v22 results in 488 mA per count.
  unsigned int mAPerCount = 5000000/1024/gain;
  int reading = (getM1CurrentReading() - DualG2HighPowerMotorShield::_offsetM1);
  if (reading > 0)
  {
    return reading * mAPerCount;
  }
  return 0;
}

// Return M2 current value in milliamps using the gain value for the specific version.
unsigned int DualG2HighPowerMotorShield::getM2CurrentMilliamps(int gain)
{
  // 5V / 1024 ADC counts / gain mV per A
  // The 24v14, 18v18 and 24v18 results in 244 mA per count.
  // The 18v22 results in 488 mA per count.
  unsigned int mAPerCount = 5000000/1024/gain;
  int reading = (getM2CurrentReading() - DualG2HighPowerMotorShield::_offsetM2);
  if (reading > 0)
  {
    return reading * mAPerCount;
  }
  return 0;
}

// Return M1 current value in milliamps for 24v14 version.
unsigned int DualG2HighPowerMotorShield24v14::getM1CurrentMilliamps()
{
  return DualG2HighPowerMotorShield::getM1CurrentMilliamps(20);
}

// Return M2 current value in milliamps for 24v14 version.
unsigned int DualG2HighPowerMotorShield24v14::getM2CurrentMilliamps()
{
  return DualG2HighPowerMotorShield::getM2CurrentMilliamps(20);
}

// Return M1 current value in milliamps for 18v18 version.
unsigned int DualG2HighPowerMotorShield18v18::getM1CurrentMilliamps()
{
  return DualG2HighPowerMotorShield::getM1CurrentMilliamps(20);
}

// Return M2 current value in milliamps for 18v18 version.
unsigned int DualG2HighPowerMotorShield18v18::getM2CurrentMilliamps()
{
  return DualG2HighPowerMotorShield::getM2CurrentMilliamps(20);
}

// Return M1 current value in milliamps for 24v18 version.
unsigned int DualG2HighPowerMotorShield24v18::getM1CurrentMilliamps()
{
  return DualG2HighPowerMotorShield::getM1CurrentMilliamps(20);
}

// Return M2 current value in milliamps for 24v18 version.
unsigned int DualG2HighPowerMotorShield24v18::getM2CurrentMilliamps()
{
  return DualG2HighPowerMotorShield::getM2CurrentMilliamps(20);
}
// Return M1 current value in milliamps for 18v22 version.
unsigned int DualG2HighPowerMotorShield18v22::getM1CurrentMilliamps()
{
  return DualG2HighPowerMotorShield::getM1CurrentMilliamps(10);
}

// Return M2 current value in milliamps for 18v22 version.
unsigned int DualG2HighPowerMotorShield18v22::getM2CurrentMilliamps()
{
  return DualG2HighPowerMotorShield::getM2CurrentMilliamps(10);
}
