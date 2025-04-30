/**
 * @file IHumidityTemperature.h
 * @brief Interface for abstracting humidity and temperature sensor functionality
 *
 * Defines a contract for humidity and temperature sensor operations independent of
 * the underlying hardware implementation (e.g., Adafruit_SHT4x).
 *
 * © 2025 Regents of the University of Minnesota. All rights reserved.
 */

 #ifndef I_HUMIDITY_TEMPERATURE_H
 #define I_HUMIDITY_TEMPERATURE_H
 
 #include <stdint.h>
 
 typedef struct {
    float temperature; /**< temperature is in degrees centigrade (Celsius) */
    float relative_humidity; /**< relative humidity in percent */
  } Isensors_event_t;
 
 /**
  * @brief Precision levels for humidity/temperature measurements
  */
 typedef enum {
     HT_HIGH_PRECISION,
     HT_MED_PRECISION,
     HT_LOW_PRECISION,
 } Iht_precision_t;
 
 /**
  * @brief Abstract interface for humidity and temperature sensors
  */
 class IHumidityTemperature {
 public:
     virtual ~IHumidityTemperature() = default;
 
     /**
      * @brief Initialize the sensor
      * @param wire Optional I2C interface pointer
      * @return true on success, false on failure
      */
     virtual bool begin() = 0;
 
     /**
      * @brief Sets the precision level for measurements
      * @param prec The desired precision setting
      */
     virtual void setPrecision(Iht_precision_t prec) = 0;
 
     /**
      * @brief Gets the current precision setting
      * @return Current precision setting
      */
     virtual Iht_precision_t getPrecision() = 0;
 
     /**
      * @brief Get humidity and temperature values as sensor events
      * @param humidity Event object to be populated with humidity data (can be NULL)
      * @param temp Event object to be populated with temperature data (can be NULL)
      * @return true if read was successful
      */
     virtual bool getEvent(Isensors_event_t *humidity, Isensors_event_t *temp) = 0;
 };
 
 #endif // I_HUMIDITY_TEMPERATURE_H