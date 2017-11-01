#ifndef DualG2HighPowerMotorShield_h
#define DualG2HighPowerMotorShield_h

#include <Arduino.h>

class DualG2HighPowerMotorShield
{
  public:  
    // CONSTRUCTORS
    DualG2HighPowerMotorShield(); // Default pin selection.
    DualG2HighPowerMotorShield(unsigned char M1nSLEEP, unsigned char M2nSLEEP, unsigned char M1nFAULT, unsigned char M1CS, 
                        unsigned char M1DIR, unsigned char M2DIR, unsigned char M2nFAULT, unsigned char M2CS); // User-defined pin selection. 
    
    // PUBLIC METHODS
    void init(); // Initialize TIMER 1, set the PWM to 20kHZ. 
    void setM1Speed(int speed); // Set speed for M1.
    void setM2Speed(int speed); // Set speed for M2.
    void setSpeeds(int m1Speed, int m2Speed); // Set speed for both M1 and M2.
    unsigned int getM1CurrentMilliamps(); // Get current reading for M1. 
    unsigned int getM2CurrentMilliamps(); // Get current reading for M2.
    unsigned char getM1Fault(); // Get fault reading from M1.
    unsigned char getM2Fault(); // Get fault reading from M2.
	void flipM1(boolean flip); // Flip the direction of the speed for M1.
    void flipM2(boolean flip); // Flip the direction of the speed for M2.
    
  private:
    unsigned char _INA1;
    unsigned char _INB1;
    static const unsigned char _M1PWM = 9;
    unsigned char _EN1DIAG1;
    unsigned char _CS1;
    unsigned char _INA2;
    unsigned char _INB2;
    static const unsigned char _M2PWM = 10;
    unsigned char _EN2DIAG2;
    unsigned char _CS2;
    
};

#endif