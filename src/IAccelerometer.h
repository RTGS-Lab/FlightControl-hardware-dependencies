/**
 * @file IAccelerometer.h
 * @brief Interface for abstracting accelerometer functionality
 *
 * Defines a contract for accelerometer operations independent of
 * the underlying hardware implementation (e.g., MXC6655, BMA456).
 *
 * © 2025 Regents of the University of Minnesota. All rights reserved.
 */

 #ifndef I_ACCELEROMETER_H
 #define I_ACCELEROMETER_H
 
 #include <stdint.h>
 
 /**
  * @brief Abstract interface for accelerometer sensors
  */
 class IAccelerometer {
 public:
     virtual ~IAccelerometer() = default;
 
     /**
      * @brief Initialize the accelerometer
      * @return 0 on success, error code on failure
      */
     virtual int begin() = 0;
 
     /**
      * @brief Get acceleration value for a specific axis
      * @param axis Axis to read (0=X, 1=Y, 2=Z)
      * @param range Sensitivity range setting
      * @return Acceleration in g units
      */
     virtual float getAccel(uint8_t axis, uint8_t range = 0) = 0;
 
     /**
      * @brief Update acceleration values for all axes at once
      * @return 0 on success, error code on failure
      */
     virtual int updateAccelAll() = 0;
 
     /**
      * @brief Get current temperature from the sensor
      * @return Temperature in degrees Celsius
      */
     virtual float getTemp() = 0;
 
     /**
      * @brief Access to acceleration data array
      * @return Pointer to the acceleration data array [X, Y, Z]
      */
     virtual float* getData() = 0;
 
     /**
      * @brief Access to offset data array
      * @return Pointer to the offset data array [X, Y, Z]
      */
     virtual float* getOffset() = 0;
 
     /**
      * @brief Set offset values for each axis
      * @param offsetX X-axis offset value
      * @param offsetY Y-axis offset value
      * @param offsetZ Z-axis offset value
      */
     virtual void setOffset(float offsetX, float offsetY, float offsetZ) = 0;
 };
 
 #endif // I_ACCELEROMETER_H