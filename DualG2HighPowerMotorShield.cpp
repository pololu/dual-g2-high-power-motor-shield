#include "DualG2HighPowerMotorShield.h"
boolean DualG2HighPowerMotorShield::_flipM1 = false;
boolean DualG2HighPowerMotorShield::_flipM2 = false;

// Constructors ////////////////////////////////////////////////////////////////

DualG2HighPowerMotorShield::DualG2HighPowerMotorShield()
{
  //Pin map
  _M1nSLEEP = 2;
  _M1nFAULT = 6;
  _M1DIR = 7;
  _M1CS = A0; 
  
  _M2nSLEEP = 4;
  _M2nFAULT = 12;
  _M2DIR = 8;
  _M2CS = A1;
}

DualG2HighPowerMotorShield::DualG2HighPowerMotorShield(	unsigned char M1nSLEEP, 
														unsigned char M1DIR, 
														unsigned char M1nFAULT, 
														unsigned char M1CS, 
														unsigned char M2nSLEEP, 
														unsigned char M2DIR, 
														unsigned char M2nFAULT, 
														unsigned char M2CS) // User-defined pin selection. 
{
  //Pin map
  //PWM1 and PWM2 cannot be remapped because the library assumes PWM is on timer1
  _M1nSLEEP = M1nSLEEP;
  _M1nFAULT = M1nFAULT;
  _M1DIR = M1DIR;
  _M1CS = M1CS;
  
  _M2nSLEEP = M2nSLEEP;
  _M2nFAULT = M2nFAULT;
  _M2DIR = M2DIR;
  _M2CS = M2CS;
}

// Public Methods //////////////////////////////////////////////////////////////
void DualG2HighPowerMotorShield::init()
{
// Define pinMode for the pins and set the frequency for timer1.

  pinMode(_M1nSLEEP,OUTPUT);
  pinMode(_M2nSLEEP,OUTPUT);
  pinMode(_M1PWM,OUTPUT);
  pinMode(_M1nFAULT,INPUT);
  pinMode(_M1CS,INPUT);
  pinMode(_M1DIR,OUTPUT);
  pinMode(_M2DIR,OUTPUT);
  pinMode(_M2PWM,OUTPUT);
  pinMode(_M2nFAULT,INPUT);
  pinMode(_M2CS,INPUT);
  #if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
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
  #if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
  OCR1A = speed;
  #else
  analogWrite(_M1PWM,speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
  #endif
  if (speed == 0)
  {
    digitalWrite(_M1nSLEEP,LOW);  
    
  }
  else if (reverse ^ _flipM1) // flip if speed was negative or _flipM1 setting is active, but not both
  {
    digitalWrite(_M1nSLEEP,HIGH);
    digitalWrite(_M1DIR,HIGH);
  }
  else
  {
    digitalWrite(_M1nSLEEP,HIGH);
    digitalWrite(_M1DIR,LOW);
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
  #if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
  OCR1B = speed;
  #else
  analogWrite(_M2PWM,speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
  #endif 
  if (speed == 0)
  {
    digitalWrite(_M2nSLEEP,LOW); 
  }
  else if (reverse ^ _flipM2) // flip if speed was negative or _flipM1 setting is active, but not both
  {
    digitalWrite(_M2nSLEEP,HIGH);
    digitalWrite(_M2DIR,HIGH);
  }
  else
  {
    digitalWrite(_M2nSLEEP,HIGH);
    digitalWrite(_M2DIR,LOW);
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

// Return motor 1 current value in milliamps for 18V version.
unsigned int DualG2HighPowerMotorShield18v::getM1CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 10 mV per A = 488 mA per count
  return analogRead(_M1CS) * 488;
}

// Return motor 2 current value in milliamps for 18V version.
unsigned int DualG2HighPowerMotorShield18v::getM2CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 10 mV per A = 488 mA per count
  return analogRead(_M2CS) * 488;
}

// Return motor 1 current value in milliamps for 24V version.
unsigned int DualG2HighPowerMotorShield24v::getM1CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 20 mV per A = 244 mA per count
  return analogRead(_M1CS) * 244;
}

// Return motor 2 current value in milliamps for 24V version.
unsigned int DualG2HighPowerMotorShield24v::getM2CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 20 mV per A = 244 mA per count
  return analogRead(_M2CS) * 244;
}