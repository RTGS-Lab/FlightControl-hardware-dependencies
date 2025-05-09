// src/hardware/ILed.h
#ifndef ILED_H
#define ILED_H

#include <stdint.h>

/**
 * @brief Interface for LED driver functionality
 * 
 * This interface abstracts LED control operations to enable
 * dependency injection and testing of components that use LED drivers.
 */
class ILed {
public:
    // Ensure proper virtual destructor
    virtual ~ILed() = default;

    // Enums copied from PCA9634 library to maintain compatibility
    enum class IGroupMode {
        Dim = 0,
        Blink = 1
    };

    enum class IOutputMode {
        OpenDrain = 0,
        TotemPole = 1
    };

    enum class IPortState {
        Off = 0,
        On = 1,
        PWM = 2,
        Group = 3
    };

    // Core initialization methods
    virtual int begin() = 0;
    virtual int sleep(bool State) = 0;

    // LED mode configuration
    virtual int setOutputMode(IOutputMode State) = 0;
    virtual int setGroupMode(IGroupMode State) = 0;

    // Group control methods
    virtual int setGroupBlinkPeriod(uint16_t Period) = 0;
    virtual int setGroupOnTime(uint16_t Period) = 0;
    
    // Brightness control
    virtual int setBrightness(uint8_t Pos, float Brightness) = 0;
    virtual int setBrightnessArray(float Brightness) = 0;

    // Output state control
    virtual int setOutput(uint8_t Pos, IPortState State) = 0;
    virtual int setOutputArray(IPortState Val) = 0;
};

#endif // ILED_H