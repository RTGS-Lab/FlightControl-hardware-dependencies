# FlightControl-hardware-dependencies

Hardware dependencies aims to be a library that abstracts specific pieces of hardware within the project. It provides interfaces to interact with the hardware drivers. This allows for testing through dependency injection by creating mocks that match the interface.

## Included Hardware Dependencies
- Accelerometer
- Ambient Light
- Current Sense Amplifier (CSA)
- GPS
- Humidity and Temperature Sensor
- IO Expander
- Led (Driver)
- RTC
- SDI12 Talon

## Interfaces
These are interfaces that can be used with a mock or a real implementation, and should allow for simpler driver development in the future.