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

#define MAX_PAYLOAD_SIZE 276 // We need >=250 bytes for getProtocolVersion on the NEO-F10N
#define GPS_COM_TYPE_UBX 1

typedef enum
{
  SUCCESS,
  FAIL,
  CRC_FAIL,
  TIMEOUT,
  COMMAND_NACK, // Indicates that the command was unrecognised, invalid or that the module is too busy to respond
  OUT_OF_RANGE,
  INVALID_ARG,
  INVALID_OPERATION,
  MEM_ERR,
  HW_ERR,
  DATA_SENT,     // This indicates that a 'set' was successful
  DATA_RECEIVED, // This indicates that a 'get' (poll) was successful
  I2C_COMM_FAILURE,
  DATA_OVERWRITTEN // This is an error - the data was valid but has been or _is being_ overwritten by another packet
} Isfe_ublox_status_e;

typedef enum
{
  VALIDITY_NOT_VALID,
  VALIDITY_VALID,
  VALIDITY_NOT_DEFINED,
  NOTACKNOWLEDGED // This indicates that we received a NACK
} Isfe_ublox_packet_validity_e;

struct IUbxPacket
{
  uint8_t cls;
  uint8_t id;
  uint16_t len;          // Length of the payload. Does not include cls, id, or checksum bytes
  uint16_t counter;      // Keeps track of number of overall bytes received. Some responses are larger than 255 bytes.
  uint16_t startingSpot; // The counter value needed to go past before we begin recording into payload array
  uint8_t *payload;      // We will allocate RAM for the payload if/when needed.
  uint8_t checksumA;     // Given to us from module. Checked against the rolling calculated A/B checksums.
  uint8_t checksumB;
  Isfe_ublox_packet_validity_e valid;           // Goes from NOT_DEFINED to VALID or NOT_VALID when checksum is checked
  Isfe_ublox_packet_validity_e classAndIDmatch; // Goes from NOT_DEFINED to VALID or NOT_VALID when the Class and ID match the requestedClass and requestedID
};

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
     * @brief Power off the GPS receiver for a specified duration or indefinitely,
     *        configuring hardware wakeup sources.
     * @param durationInMs Duration to sleep in milliseconds. Set to 0 for indefinite sleep until wakeup event.
     * @param wakeupSources Bitmask indicating which sources can wake the module.
     *                      Commonly uses constants like VAL_RXM_PMREQ_WAKEUPSOURCE_EXTINT0,
     *                      VAL_RXM_PMREQ_WAKEUPSOURCE_EXTINT1, VAL_RXM_PMREQ_WAKEUPSOURCE_UARTRX,
     *                      VAL_RXM_PMREQ_WAKEUPSOURCE_SPICS (defined by the underlying u-blox library).
     * @param forceWhileUsb Set to true to force power down even if USB is connected (recommended).
     *                      Set to false to prevent power down if USB is enumerated.
     * @return true if the command was successfully sent/acknowledged, false otherwise.
     */
    virtual bool powerOffWithInterrupt(uint32_t durationInMs, uint32_t wakeupSources, bool forceWhileUsb = true) = 0;
    
    /**
     * @brief Send a command to the GPS module
     * @param outgoingUBX Pointer to the outgoing UBX packet
     * @param maxWait Maximum wait time for response (in milliseconds)
     * @return Status of the command
     */
    virtual Isfe_ublox_status_e sendCommand(IUbxPacket *outgoingUBX, uint16_t maxWait = 1100) = 0;
};

#endif // IGPS_H