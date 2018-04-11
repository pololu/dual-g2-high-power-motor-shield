#pragma once

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || \
    defined(__AVR_ATmega328PB__) || defined (__AVR_ATmega32U4__)
  #define DUALG2HIGHPOWERMOTORSHIELD_TIMER1_AVAILABLE
#endif

#include <Arduino.h>

class DualG2HighPowerMotorShield
{
  public:
    // CONSTRUCTORS
    DualG2HighPowerMotorShield();
    DualG2HighPowerMotorShield(unsigned char M1nSLEEP,
                               unsigned char M1DIR,
                               unsigned char M1PWM,
                               unsigned char M1nFAULT,
                               unsigned char M1CS,
                               unsigned char M2nSLEEP,
                               unsigned char M2DIR,
                               unsigned char M2PWM,
                               unsigned char M2nFAULT,
                               unsigned char M2CS);

    // PUBLIC METHODS
    void init();
    void setM1Speed(int speed); // Set speed for M1.
    void setM2Speed(int speed); // Set speed for M2.
    void setSpeeds(int m1Speed, int m2Speed); // Set speed for both M1 and M2.
    unsigned char getM1Fault(); // Get fault reading from M1.
    unsigned char getM2Fault(); // Get fault reading from M2.
    void flipM1(boolean flip); // Flip the direction of the speed for M1.
    void flipM2(boolean flip); // Flip the direction of the speed for M2.
    void enableM1Driver(); // Enables the MOSFET driver for M1.
    void enableM2Driver(); // Enables the MOSFET driver for M2.
    void enableDrivers(); // Enables the MOSFET drivers for both M1 and M2.
    void disableM1Driver(); // Puts the MOSFET driver for M1 into sleep mode.
    void disableM2Driver(); // Puts the MOSFET driver for M2 into sleep mode.
    void disableDrivers(); // Puts the MOSFET drivers for both M1 and M2 into sleep mode.
    unsigned int getM1CurrentReading();
    unsigned int getM2CurrentReading();
    void calibrateM1CurrentOffset();
    void calibrateM2CurrentOffset();
    void calibrateCurrentOffsets();
    unsigned int getM1CurrentMilliamps(int gain);
    unsigned int getM2CurrentMilliamps(int gain);

  protected:
    unsigned int _offsetM1;
    unsigned int _offsetM2;

  private:
    unsigned char _M1PWM;
    static const unsigned char _M1PWM_TIMER1_PIN = 9;
    unsigned char _M2PWM;
    static const unsigned char _M2PWM_TIMER1_PIN = 10;
    unsigned char _M1nSLEEP;
    unsigned char _M2nSLEEP;
    unsigned char _M1DIR;
    unsigned char _M2DIR;
    unsigned char _M1nFAULT;
    unsigned char _M2nFAULT;
    unsigned char _M1CS;
    unsigned char _M2CS;
    static boolean _flipM1;
    static boolean _flipM2;

};

class DualG2HighPowerMotorShield24v14 : public DualG2HighPowerMotorShield
{
  public:
    using DualG2HighPowerMotorShield::DualG2HighPowerMotorShield;
    unsigned int getM1CurrentMilliamps(); // Get current reading for M1.
    unsigned int getM2CurrentMilliamps(); // Get current reading for M2.
};

class DualG2HighPowerMotorShield18v18 : public DualG2HighPowerMotorShield
{
  public:
    using DualG2HighPowerMotorShield::DualG2HighPowerMotorShield;
    unsigned int getM1CurrentMilliamps(); // Get current reading for M1.
    unsigned int getM2CurrentMilliamps(); // Get current reading for M2.
};

class DualG2HighPowerMotorShield24v18 : public DualG2HighPowerMotorShield
{
  public:
    using DualG2HighPowerMotorShield::DualG2HighPowerMotorShield;
    unsigned int getM1CurrentMilliamps(); // Get current reading for M1.
    unsigned int getM2CurrentMilliamps(); // Get current reading for M2.
};

class DualG2HighPowerMotorShield18v22 : public DualG2HighPowerMotorShield
{
  public:
    using DualG2HighPowerMotorShield::DualG2HighPowerMotorShield;
    unsigned int getM1CurrentMilliamps(); // Get current reading for M1.
    unsigned int getM2CurrentMilliamps(); // Get current reading for M2.
};
