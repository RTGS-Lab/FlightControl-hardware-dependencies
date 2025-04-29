/**
 * @file IGPS.h
 * @brief Interface for abstracting GPS functionality
 *
 * Defines a contract for GPS operations independent of
 * the underlying hardware implementation (e.g., SFE_UBLOX_GNSS).
 *
 * © 2025 Regents of the University of Minnesota. All rights reserved.
 */

#ifndef IGPS_H
#define IGPS_H

#include <stdint.h>

/**
 * @brief Abstract interface for GPS modules
 */
class IGps {
public:
    virtual ~IGps() = default;

    /**
     * @brief Initialize the GPS module
     * @return true on success, false on failure
     */
    virtual bool begin() = 0;

    /**
     * @brief Set I2C output format
     * @param comType The communication protocol to use
     */
    virtual void setI2COutput(uint8_t comType) = 0;

    /**
     * @brief Set how many solutions per second are produced
     * @param navFreq Navigation frequency (1-10 Hz)
     * @return true on success, false on failure
     */
    virtual bool setNavigationFrequency(uint8_t navFreq) = 0;

    /**
     * @brief Enable/disable automatic PVT messaging
     * @param autoPVT true to enable, false to disable
     */
    virtual void setAutoPVT(bool autoPVT) = 0;

    /**
     * @brief Get current navigation frequency setting
     * @return The navigation frequency (Hz)
     */
    virtual uint8_t getNavigationFrequency() = 0;

    /**
     * @brief Get current measurement rate
     * @return The measurement rate
     */
    virtual uint8_t getMeasurementRate() = 0;

    /**
     * @brief Get current navigation rate
     * @return The navigation rate
     */
    virtual uint8_t getNavigationRate() = 0;

    /**
     * @brief Get roll angle from attitude data
     * @return Roll angle in degrees * 100 (divide by 100 to get degrees)
     */
    virtual int16_t getATTroll() = 0;

    /**
     * @brief Get pitch angle from attitude data
     * @return Pitch angle in degrees * 100 (divide by 100 to get degrees)
     */
    virtual int16_t getATTpitch() = 0;

    /**
     * @brief Get heading from attitude data
     * @return Heading in degrees * 100 (divide by 100 to get degrees)
     */
    virtual int16_t getATTheading() = 0;

    /**
     * @brief Set packet configuration payload size
     * @param payloadSize Size of the payload in bytes
     */
    virtual void setPacketCfgPayloadSize(uint16_t payloadSize) = 0;

    /**
     * @brief Get number of satellites in view
     * @return Number of satellites
     */
    virtual uint8_t getSIV() = 0;

    /**
     * @brief Get current fix type (0=no fix, 2=2D, 3=3D)
     * @return Fix type
     */
    virtual uint8_t getFixType() = 0;

    /**
     * @brief Get Position, Velocity, and Time data
     * @return true if new data available, false otherwise
     */
    virtual bool getPVT() = 0;

    /**
     * @brief Check if a valid GNSS fix is available
     * @return true if fix is valid, false otherwise
     */
    virtual bool getGnssFixOk() = 0;

    /**
     * @brief Get current altitude
     * @return Altitude in mm above mean sea level
     */
    virtual long getAltitude() = 0;

    /**
     * @brief Get current longitude
     * @return Longitude in degrees * 10^-7 (divide by 10000000 to get degrees)
     */
    virtual long getLongitude() = 0;

    /**
     * @brief Get current latitude
     * @return Latitude in degrees * 10^-7 (divide by 10000000 to get degrees)
     */
    virtual long getLatitude() = 0;

    /**
     * @brief Get hour component of current time
     * @return Hour (0-23)
     */
    virtual uint8_t getHour() = 0;

    /**
     * @brief Get minute component of current time
     * @return Minute (0-59)
     */
    virtual uint8_t getMinute() = 0;

    /**
     * @brief Get second component of current time
     * @return Second (0-59)
     */
    virtual uint8_t getSecond() = 0;

    /**
     * @brief Check if date is valid
     * @return true if date is valid, false otherwise
     */
    virtual bool getDateValid() = 0;

    /**
     * @brief Check if time is valid
     * @return true if time is valid, false otherwise
     */
    virtual bool getTimeValid() = 0;

    /**
     * @brief Check if time is fully resolved
     * @return true if time is fully resolved, false otherwise
     */
    virtual bool getTimeFullyResolved() = 0;

    /**
     * @brief Power off GPS with interrupt wake-up option
     * @param enableInterrupt true to enable wake on interrupt
     * @return true if successful, false otherwise
     */
    virtual bool powerOffWithInterrupt(bool enableInterrupt) = 0;
};

#endif // IGPS_H