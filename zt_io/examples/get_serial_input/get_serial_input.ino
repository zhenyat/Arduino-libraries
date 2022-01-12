/*********************************************************
 * get_serial_input
 *
 * Sample to get a string of characters from Serial Port
 * 
 * 26.07.2021 ZT
 * 10.08.2021 Last update
 *********************************************************/
#include <zt_io.h>

void setup() {
  Serial.begin(9600);
  sleep(2);
  Serial.println("===== Starting: enter float numbers...");
//  Serial.println("===== Starting: enter strings...");
}

void loop() {
  float value = atof(getSerialInput());
  Serial.println(value, 4);

//  String value = getSerialInput();
//  Serial.println(value);
  
  sleep(4);
}
