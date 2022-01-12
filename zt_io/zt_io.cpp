/***********************************************************************
 * IO library functions:
 *    Printf()          - analog of printf() / via SerialPrintf() /
 *                        not workingwith float values!
 *    Debug()           - the same
 * 
 *    getSerialInput()  - reads string of characters fro Serial Port
 *    serial_printf()   - full analog of C prointf() including floats
 *    setOutputMode()   - sets PIN's Mode as OUTPUT
 *    sleep()           - delay in sec
 * 
 * 29.07.2021 ZT
 * 10.09.2021 Last update 
 **********************************************************************/
#include "zt_io.h"

extern "C" {
  int serialputc(char c, FILE *fp) { 
    if(c == '\n')  Serial.write('\r'); 
    Serial.write(c); 
  }
}
  
void _SerialPrintf(const char *fmt, ...) {
  FILE stdiostr;
  va_list ap;

  fdev_setup_stream(&stdiostr, serialputc, NULL, _FDEV_SETUP_WRITE);

  va_start(ap, fmt);
  vfprintf_P(&stdiostr, fmt, ap);
  va_end(ap);
}

const unsigned int MAX_BUFFER_LENGTH = 12;

char *getSerialInput() {
  while (Serial.available() > 0) {
    static char buffer[MAX_BUFFER_LENGTH];  // Buffer for the incoming string
    static unsigned int bufferPosition = 0;
      
    // Read the next available byte in the serial receiver buffer
    char inByte = Serial.read();

    // Message coming in (check not terminating character) and guard for over message size
    if ( inByte != '\n' && (bufferPosition < MAX_BUFFER_LENGTH - 1) ) {
      
      buffer[bufferPosition] = inByte;  // Add the incoming byte to buffer
      bufferPosition++;
      
    } else {        					// buffer is filled

      buffer[bufferPosition] = '\0';
      bufferPosition = 0;           	// reset buffer

      return buffer;
    }
  }
}

/***********************************************************************
 * Simple printf for writing to an Arduino serial port.  Allows specifying Serial..Serial3.
 * 
 * const HardwareSerial&, the serial port to use (Serial..Serial3)
 * const char* fmt, the formatting string followed by the data to be formatted
 * 
 * int d = 65;
 * float f = 123.4567;
 * char* str = "Hello";
 * serial_printf(Serial, "<fmt>", d);
 * 
 * Example:
 *   serial_printf(Serial, "Sensor %d is %o and reads %1f\n", d, d, f) will
 *   output "Sensor 65 is on and reads 123.5" to the serial port.
 * 
 * Formatting strings <fmt>
 *  %B    - binary (d = 0b1000001)
 *  %b    - binary (d = 1000001)  
 *  %c    - character (s = H)
 *  %d|%i - integer (d = 65)\
 *  %f    - float (f = 123.45)
 *  %3f   - float (f = 123.346) three decimal places specified by %3.
 *  %o    - boolean on/off (d = On)
 *  %s    - char* string (s = Hello)
 *  %X    - hexidecimal (d = 0x41)
 *  %x    - hexidecimal (d = 41)
 *  %%    - escaped percent ("%")
 * 
 *  Thanks goes to @alw1746 for his %.4f precision enhancement 
 * 
 * https://gist.github.com/ridencww/4e5d10097fee0b0f7f6b
 ***********************************************************************/
void serial_printf(HardwareSerial& serial, const char* fmt, ...) { 
  va_list argv;
  va_start(argv, fmt);

  for (int i = 0; fmt[i] != '\0'; i++) {
    if (fmt[i] == '%') {
      // Look for specification of number of decimal places
      int places = 2;
      if (fmt[i+1] == '.') i++;  // alw1746: Allows %.4f precision like in stdio printf (%4f will still work).
      if (fmt[i+1] >= '0' && fmt[i+1] <= '9') {
        places = fmt[i+1] - '0';
        i++;
      }
      
      switch (fmt[++i]) {
        case 'B':
          serial.print("0b"); // Fall through intended
        case 'b':
          serial.print(va_arg(argv, int), BIN);
          break;
        case 'c': 
          serial.print((char) va_arg(argv, int));
          break;
        case 'd': 
        case 'i':
          serial.print(va_arg(argv, int), DEC);
          break;
        case 'f': 
          serial.print(va_arg(argv, double), places);
          break;
        case 'l': 
          serial.print(va_arg(argv, long), DEC);
          break;
        case 'o':
          serial.print(va_arg(argv, int) == 0 ? "off" : "on");
          break;
        case 's': 
          serial.print(va_arg(argv, const char*));
          break;
        case 'X':
          serial.print("0x"); // Fall through intended
        case 'x':
          serial.print(va_arg(argv, int), HEX);
          break;
        case '%': 
          serial.print(fmt[i]);
          break;
        default:
          serial.print("?");
          break;
      }
    } else {
      serial.print(fmt[i]);
    }
  }
  va_end(argv);
}

void setOutputMode(unsigned int Pin) {
  pinMode(Pin, OUTPUT);  // MUST BE!!! Otherwise 0.15V is at Multimeter...
}


void sleep(unsigned int timeInSeconds)
{
  delay(timeInSeconds * 1000UL); // Milliseconds
}
