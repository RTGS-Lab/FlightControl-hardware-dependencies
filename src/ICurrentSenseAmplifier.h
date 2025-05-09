// src/hardware/ICurrentSenseAmplifier.h

#ifndef ICURRENT_SENSE_AMPLIFIER_H
#define ICURRENT_SENSE_AMPLIFIER_H

#include <stdint.h>
#include <stdbool.h>

enum IChannel {
    CSA_CH1 = 0,
    CSA_CH2 = 1,
    CSA_CH3 = 2,
    CSA_CH4 = 3,
};

enum IFrequency {
    CSA_SPS_8 = 0b11,
    CSA_SPS_64 = 0b10,
    CSA_SPS_256 = 0b01,
    CSA_SPS_1024 = 0b00
  };

#define CSA_BIDIRECTIONAL 1
#define CSA_UNIDIRECTIONAL 0

/**
 * @brief Abstract interface for current sensing amplifiers
 * 
 * Provides methods to interact with current sensing amplifiers in a
 * platform-agnostic way, enabling dependency injection and testing.
 */
class ICurrentSenseAmplifier {
public:
    virtual ~ICurrentSenseAmplifier() = default;
    
    // Configuration methods
    virtual bool begin() = 0;
    virtual bool setAddress(uint8_t addr) = 0;
    virtual bool enableChannel(uint8_t Unit, bool State ) = 0;
    virtual bool setFrequency(uint16_t frequency) = 0;
    virtual int getFrequency() = 0;

    // Measurement direction
    virtual void setVoltageDirection(uint8_t Unit, bool Direction) = 0;
    virtual void setCurrentDirection(uint8_t Unit, bool Direction) = 0;
    virtual bool getVoltageDirection(uint8_t Unit) = 0;
    virtual bool getCurrentDirection(uint8_t Unit) = 0;

    // Measurement methods
    virtual float getBusVoltage(uint8_t Unit, bool Avg, bool &Stat) = 0;
    virtual float getBusVoltage(uint8_t Unit, bool Avg = false) = 0;
    virtual float getSenseVoltage(uint8_t Unit, bool Avg, bool &Stat) = 0;
    virtual float getSenseVoltage(uint8_t Unit, bool Avg = false) = 0; 
    virtual float getCurrent(uint8_t Unit, bool Avg, bool &Stat) = 0;
    virtual float getCurrent(uint8_t Unit, bool Avg = false) = 0;
    virtual float getPowerAvg(uint8_t Unit, bool& Stat) = 0;
    virtual float getPowerAvg(uint8_t Unit) = 0;

    // Status and control
    virtual uint8_t update(uint8_t Clear = false) = 0;
    virtual bool testOverflow() = 0;
};

#endif // ICURRENT_SENSE_AMPLIFIER_H