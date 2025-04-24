/**
 * @file IAmbientLight.h
 * @brief Interface for abstracting ambient light sensor functionality
 *
 * Defines a contract for ambient light sensor operations independent of
 * the underlying hardware implementation (e.g., VEML3328).
 *
 * © 2025 Regents of the University of Minnesota. All rights reserved.
 */

 #ifndef I_AMBIENT_LIGHT_H
 #define I_AMBIENT_LIGHT_H
 
 #include <stdint.h>
 
 /**
  * @brief Abstract interface for ambient light sensors
  */
 class IAmbientLight {
 public:
     /**
      * @brief Color channel enumeration
      */
     enum class Channel : uint8_t {
         Clear = 0,
         Red = 1,
         Green = 2,
         Blue = 3,
         IR = 4
     };
 
     virtual ~IAmbientLight() = default;
 
     /**
      * @brief Initialize the sensor
      * @return 0 on success, error code on failure
      */
     virtual int begin() = 0;
 
     /**
      * @brief Get calibrated value from a specific channel
      * @param channel The color channel to read
      * @return The sensor reading as a float value
      */
     virtual float getValue(Channel channel) = 0;
 
     /**
      * @brief Get calibrated value from a specific channel with status
      * @param channel The color channel to read
      * @param state Will be set to true if error occurred, false if successful
      * @return The sensor reading as a float value
      */
     virtual float getValue(Channel channel, bool &state) = 0;
 
     /**
      * @brief Get the estimated ambient light in lux
      * @return Light level in lux
      */
     virtual float getLux() = 0;
 
     /**
      * @brief Automatically set the gain and integration time for optimal readings
      * @return 0 on success, error code on failure
      */
     virtual int autoRange() = 0;
 };
 
 #endif // I_AMBIENT_LIGHT_H