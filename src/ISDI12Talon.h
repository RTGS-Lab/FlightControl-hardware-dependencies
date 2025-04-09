/******************************************************************************
ISDI12Talon.h
Interface for SDI12 Talon
© 2025 Regents of the University of Minnesota. All rights reserved.
******************************************************************************/

#ifndef ISDI12_TALON_H
#define ISDI12_TALON_H

#include <stdint.h>
#include <time.h>
#include "../../Driver_-_Talon/src/Talon.h" // Include the Talon base class

/**
 * @brief Interface for SDI12 Talon functionality
 *
 * Defines the contract for SDI12 Talon operations used by sensors like Li710.
 * This interface allows for dependency injection and testing.
 */
class ISDI12Talon {
public:
    virtual ~ISDI12Talon() = default;

    // SDI12 communication methods
    virtual int getAddress() = 0;
    virtual String sendCommand(String command) = 0;
    virtual String command(String commandStr, int address) = 0;
    virtual String continuousMeasurmentCRC(int Measure, int Address) = 0;
    virtual bool testCRC(String message) = 0;
    
    // Port management methods
    virtual int enableData(uint8_t port, bool state) = 0;
    virtual int enablePower(uint8_t port, bool state) = 0;
    virtual void disableDataAll() = 0;
    virtual uint8_t getNumPorts() = 0;
    
    // Sensor interrogation
    virtual bool isPresent() = 0;
    
    // Error handling and state reporting
    //virtual int throwError(uint32_t error) = 0;
    virtual String getSensorPortString() = 0;
    virtual String getTalonPortString() = 0;
    virtual uint8_t getSensorPort() = 0;
    virtual uint8_t getTalonPort() = 0;
    virtual int restart() = 0;
};

#endif // ISDI12_TALON_H