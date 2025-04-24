/**
 * @file IRtc.h
 * @brief Interface for abstracting real-time clock functionality.
 *
 * Defines a contract for interacting with real-time clock hardware
 * independent of the underlying implementation (e.g., MCP79412).
 *
 * © 2025 Regents of the University of Minnesota. All rights reserved.
 */

 #ifndef I_RTC_H
 #define I_RTC_H
 
 #include <stdint.h>
 #include <time.h>
 #include "Particle.h"
 
 /**
  * @brief Abstract interface for real-time clock functionality.
  */
 class IRtc {
 public:
    // Maximum number of errors to track
    static constexpr int MAX_NUM_ERRORS = 10;
    
    // Public error tracking members that all implementations maintain
    uint32_t errors[MAX_NUM_ERRORS] = {0};
    uint8_t numErrors = 0;
     /**
      * @brief Virtual destructor for proper cleanup of derived classes.
      */
     virtual ~IRtc() = default;
 
     /**
      * @brief Enumeration for different RTC modes.
      */
     enum class Mode {
         Normal = 0,
         Inverted = 1
     };
 
     /**
      * @brief Structure for timestamp representation.
      */
     struct Timestamp {
         uint16_t year;  // e.g. 2020
         uint8_t  month; // 1-12
         uint8_t  mday;  // Day of the month, 1-31
         uint8_t  wday;  // Day of the week, 1-7
         uint8_t  hour;  // 0-23
         uint8_t  min;   // 0-59
         uint8_t  sec;   // 0-59
     };
 
     /**
      * @brief Initialize the RTC.
      * 
      * @param UseExtOsc Whether to use an external oscillator.
      * @return int Return status (0 for success, non-zero for error).
      */
     virtual int begin(bool UseExtOsc = false) = 0;
 
     /**
      * @brief Set the time on the RTC.
      * 
      * @param Year Year (2 or 4 digits)
      * @param Month Month (1-12)
      * @param Day Day of month (1-31)
      * @param DoW Day of week (1-7)
      * @param Hour Hour (0-23)
      * @param Min Minute (0-59)
      * @param Sec Second (0-59)
      * @return int Return status.
      */
     virtual int setTime(int Year, int Month, int Day, int DoW, int Hour, int Min, int Sec) = 0;
 
     /**
      * @brief Set the time on the RTC (no DoW).
      * 
      * @param Year Year (2 or 4 digits)
      * @param Month Month (1-12)
      * @param Day Day of month (1-31)
      * @param Hour Hour (0-23)
      * @param Min Minute (0-59)
      * @param Sec Second (0-59)
      * @return int Return status.
      */
     virtual int setTime(int Year, int Month, int Day, int Hour, int Min, int Sec) = 0;
 
     /**
      * @brief Get raw timestamp from the RTC.
      * 
      * @return Timestamp The current timestamp.
      */
     virtual Timestamp getRawTime() = 0;
 
     /**
      * @brief Get the current time as Unix timestamp.
      * 
      * @return time_t Unix timestamp.
      */
     virtual time_t getTimeUnix() = 0;
 
     /**
      * @brief Set the operating mode of the RTC.
      * 
      * @param Val The desired mode.
      * @return int Return status.
      */
     virtual int setMode(Mode Val) = 0;
 
     /**
      * @brief Set an alarm for a given number of seconds from now.
      * 
      * @param Seconds Seconds from now to trigger the alarm.
      * @param AlarmNum Which alarm to set (0 or 1).
      * @return int Return status.
      */
     virtual int setAlarm(unsigned int Seconds, bool AlarmNum = false) = 0;
 
     /**
      * @brief Set a minute alarm with specific offset.
      * 
      * @param Offset Seconds offset within each minute.
      * @param AlarmNum Which alarm to set (0 or 1).
      * @return int Return status.
      */
     virtual int setMinuteAlarm(unsigned int Offset, bool AlarmNum = false) = 0;
 
     /**
      * @brief Set an hourly alarm with specific offset.
      * 
      * @param Offset Minutes offset within each hour.
      * @param AlarmNum Which alarm to set (0 or 1).
      * @return int Return status.
      */
     virtual int setHourAlarm(unsigned int Offset, bool AlarmNum = false) = 0;
 
     /**
      * @brief Set a daily alarm with specific offset.
      * 
      * @param Offset Hour offset within each day.
      * @param AlarmNum Which alarm to set (0 or 1).
      * @return int Return status.
      */
     virtual int setDayAlarm(unsigned int Offset, bool AlarmNum = false) = 0;
 
     /**
      * @brief Enable or disable an alarm.
      * 
      * @param State Enable (true) or disable (false) the alarm.
      * @param AlarmNum Which alarm to control (0 or 1).
      * @return int Return status.
      */
     virtual int enableAlarm(bool State = true, bool AlarmNum = false) = 0;
 
     /**
      * @brief Clear an alarm's flags.
      * 
      * @param AlarmNum Which alarm to clear (0 or 1).
      * @return int Return status.
      */
     virtual int clearAlarm(bool AlarmNum = false) = 0;
 
     /**
      * @brief Check if an alarm has been triggered.
      * 
      * @param AlarmNum Which alarm to check (0 or 1).
      * @return bool True if alarm has been triggered.
      */
     virtual bool readAlarm(bool AlarmNum = false) = 0;
 
     /**
      * @brief Get the UUID as a string.
      * 
      * @return String UUID in string format.
      */
     virtual String getUUIDString() = 0;
 
     /**
      * @brief Read the value of a specific register.
      * 
      * @param Reg Register address.
      * @return uint8_t Register value.
      */
     virtual uint8_t readByte(int Reg) = 0;
 
     /**
      * @brief Get the errors array.
      * 
      * @param errors Array to populate with error codes.
      * @return uint8_t Number of errors.
      */
     virtual uint8_t getErrorsArray(uint32_t errors[]) = 0;
 
     /**
      * @brief Register a new error.
      * 
      * @param error Error code.
      * @return int Total number of errors.
      */
     virtual int throwError(uint32_t error) = 0;
 };
 
 #endif // I_RTC_H