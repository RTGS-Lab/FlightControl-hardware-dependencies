/******************************************************************************
IIOExpander.h
Interface for 16 bit IO expander
Based on original PCAL9535A implementation
© 2025 Regents of the University of Minnesota. All rights reserved.
******************************************************************************/

#ifndef IIOExpander_h
#define IIOExpander_h

#include <stdint.h>
#include "../../FlightControl-platform-dependencies/src/IWire.h" // Use platform-independent IWire

// Define constants needed for interface users
#define PORT_A 0
#define PORT_B 1

enum IDriveStrength: uint8_t {
    DRIVE_STRENGTH_DEFAULT    = 0,
    DRIVE_STRENGTH_HIGH       = 1,
    DRIVE_STRENGTH_STANDARD   = 2
};

/**
 * @brief Abstract interface for PCAL9535A I/O expander functionality
 */
class IIOExpander {
public:
    // Safe mode constants
    static constexpr int SAFEOFF = -1; // No additional error logging
    static constexpr int SAFE1 = 0;    // I2C error logging only
    static constexpr int SAFE2 = 1;    // Memory and read write error logging
    static constexpr int SAFE3 = 2;    // Output error logging
    static constexpr int SAFE = 99;    // Turn on all possible safety protocols
    
    // IntAge enum for clearInterrupt and getAllInterrupts methods
    enum IntAge {
        CURRENT = 0,
        STALE = 1,
        BOTH = 2,
    };

    enum IPinMode {
        INPUT = 0,
        OUTPUT = 1,
        INPUT_PULLUP = 2,
    };

    enum ILevel: uint8_t {
        LOW = 0,
        HIGH = 1
    };

    // Virtual destructor
    virtual ~IIOExpander() = default;
    
    // Core functionality
    virtual int begin(void) = 0;
    
    // Pin control methods
    virtual int pinMode(int Pin, uint8_t State, bool Port) = 0;
    virtual int pinMode(int Pin, uint8_t State) = 0;
    virtual int digitalWrite(int Pin, bool State, bool Port) = 0;
    virtual int digitalWrite(int Pin, bool State) = 0;
    virtual int digitalRead(int Pin, bool Port) = 0;
    virtual int digitalRead(int Pin) = 0;
    
    // Drive strength methods
    virtual int pinSetDriveStrength(int Pin, IDriveStrength State, bool Port) = 0;
    virtual int pinSetDriveStrength(int Pin, IDriveStrength State) = 0;
    
    // Interrupt methods
    virtual int setInterrupt(int Pin, bool State, bool Port) = 0;
    virtual int setInterrupt(int Pin, bool State) = 0;
    virtual int getInterrupt(int Pin) = 0;
    virtual uint16_t getAllInterrupts(uint8_t Option) = 0;
    virtual uint16_t getInterruptMask() = 0;
    virtual unsigned int clearInterrupt(uint8_t age) = 0;
    virtual bool isInterrupt(uint8_t age) = 0;
    
    // Latch methods
    virtual int setLatch(int Pin, bool State, bool Port) = 0;
    virtual int setLatch(int Pin, bool State) = 0;
    virtual uint16_t getLatch() = 0;
    
    // Input polarity methods
    virtual int setInputPolarity(int Pin, bool State, bool Port) = 0;
    virtual int setInputPolarity(int Pin, bool State) = 0;
    virtual bool getInputPolarity(int Pin, bool Port) = 0;
    virtual bool getInputPolarity(int Pin) = 0;
    
    // Configuration methods
    virtual int setIntPinConfig(int Pin, bool Latch) = 0;
    virtual int setBusOutput(uint8_t mode, bool Port) = 0;
    virtual uint8_t getBusOutput() = 0;
    
    // Bus read method
    virtual uint16_t readBus() = 0;
    
    // Error handling methods
    virtual uint16_t getError() = 0;
    virtual uint16_t clearError() = 0;
    virtual void safeMode(int state = SAFE) = 0;
    
    // Additional methods
    virtual uint16_t readWord(int Pos, int &Error) = 0;
};

#endif // IIOExpander_h