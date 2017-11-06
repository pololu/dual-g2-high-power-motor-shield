#ifndef DualG2HighPowerMotorShield_h
#define DualG2HighPowerMotorShield_h

#include <Arduino.h>

class DualG2HighPowerMotorShield
{
  public:  
    // CONSTRUCTORS
    DualG2HighPowerMotorShield(); // Default pin selection.
    DualG2HighPowerMotorShield(	unsigned char M1nSLEEP, unsigned char M1DIR, unsigned char M1nFAULT, unsigned char M1CS, 
								unsigned char M2nSLEEP, unsigned char M2DIR, unsigned char M2nFAULT, unsigned char M2CS); // User-defined pin selection. 
    
    // PUBLIC METHODS
    void init(); // Initialize TIMER 1, set the PWM to 20kHZ. 
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
	signed int getM1CurrentReading();
	signed int getM2CurrentReading();
	void calibrateM1CurrentOffset();
	void calibrateM2CurrentOffset();
	void calibrateCurrentOffset();
    
  private:
    static const unsigned char _M1PWM = 9;
	static const unsigned char _M2PWM = 10;
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
	unsigned int _offsetM1 = 0;
	unsigned int _offsetM2 = 0;
    
};

class DualG2HighPowerMotorShield18v : public DualG2HighPowerMotorShield
{
  public:
	DualG2HighPowerMotorShield18v(): DualG2HighPowerMotorShield() {}
    DualG2HighPowerMotorShield18v(unsigned char M1nSLEEP, unsigned char M1DIR, unsigned char M1nFAULT, unsigned char M1CS, 
                        unsigned char M2nSLEEP, unsigned char M2DIR, unsigned char M2nFAULT, unsigned char M2CS) : 
						DualG2HighPowerMotorShield(M1nSLEEP, M1DIR, M1nFAULT, M1CS, M2nSLEEP, M2DIR, M2nFAULT, M2CS) {}

    unsigned int getM1CurrentMilliamps(); // Get current reading for M1. 
    unsigned int getM2CurrentMilliamps(); // Get current reading for M2.
};

class DualG2HighPowerMotorShield24v : public DualG2HighPowerMotorShield
{
  public:
	DualG2HighPowerMotorShield24v() : DualG2HighPowerMotorShield() {}
    DualG2HighPowerMotorShield24v(unsigned char M1nSLEEP, unsigned char M1DIR, unsigned char M1nFAULT, unsigned char M1CS, 
                        unsigned char M2nSLEEP, unsigned char M2DIR, unsigned char M2nFAULT, unsigned char M2CS) : 
						DualG2HighPowerMotorShield(M1nSLEEP, M1DIR, M1nFAULT, M1CS, M2nSLEEP, M2DIR, M2nFAULT, M2CS) {}

    unsigned int getM1CurrentMilliamps(); // Get current reading for M1. 
    unsigned int getM2CurrentMilliamps(); // Get current reading for M2.
};

#endif