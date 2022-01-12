/***********************************************************************
 * zt_io.h
 * 
 * Header file for IO library functions:
 *    Printf()          - analog of printf() / via SerialPrintf() /
 *                        ! not working with float values!
 * 
 *    getSerialInput()  - reads string of characters from Serial Port
 *    serial_printf()   - full analog of C printf() including floats
 *    setOutputMode()   - sets PIN's Mode as OUTPUT
 *    sleep()           - delay in sec
 * 
 * 29.07.2021 ZT
 * 01.08.2021 Last update
 **********************************************************************/
#ifndef ZT_IO_H
  #define ZT_IO_H

  #include <Arduino.h>
  #include <avr/pgmspace.h>

  #define SerialPrintf(fmt, ...) _SerialPrintf(PSTR(fmt), ##__VA_ARGS__)
  #define NullPrintf(fmt, ...) 

  void _SerialPrintf(const char *fmt, ...);

  #define Printf SerialPrintf   // Map Printf() to SerialPrintf() 
  
  char* getSerialInput();
  void serial_printf(HardwareSerial& serial, const char* fmt, ...);
  void setOutputMode(unsigned int Pin);
  void sleep(unsigned int timeInSeconds);
#endif
