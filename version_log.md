<h1 align="center">Version Log</h1>

This file contains the versions history of developing this project.

## Version 1.0.0

**Date:** 2022-06-28

**Description:** Initial version.

*Added the following features:*

1. Using FreeRTOS as the kernel.
2. Using ADC to read the temperature and gas level (In Non-blocking mode).

*The system  consists of the following functions:*

1. Gas Sensor to sense the gas level in the house.
2. Temperature Sensor to sense the temperature in the house.
3. Keypad to enter the password to open the door.
4. Motor to open/close the door when the password is correct.
5. Buzzer to alert the user when the system is in alarm mode:
   1. The password is incorrect for 3 times.
   2. The gas level is above the critical level.
6. LCD to display the system's data (temperature, door status, gas level).
