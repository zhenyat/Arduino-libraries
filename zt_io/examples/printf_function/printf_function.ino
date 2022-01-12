/****************************************************
 * Usage of ZT Library functions:
 *  - Printf()
 *  - serial_printf()
 * 
 * 25.07.2021 ZT
 * 12.08.2021 Last Update
 ****************************************************/
#include <zt_io.h>

void setup() {
  Serial.begin(9600);
  sleep(2);
  
  bool status   = 1;
  int pwmPin    = 3;
  float voltage = 3.125;
  char* device  = "Conditioner";
  
  int arr[] = {1, 10, 100, 999};
  char printIntValue[4];       // to print integer values with '%4d' format

//  float volts[] = {0., 1.2, 12.34, 220.};
//  char printFloatValue[10];                 // not working...
//  
  for (int i=0; i<4; i++) {
   serial_printf(Serial, "%3i\n", arr[i]);
  }
  
  for (int i=0; i<4; i++) {
   sprintf(printIntValue, "%4d", arr[i]);
   serial_printf(Serial, "%s\n", printIntValue);
  }
  
//  for (int i=0; i<4; i++) {
//   sprintf(printFloatValue, "%.2f", volts[i]);
//   serial_printf(Serial, "%s\n", printFloatValue);
//  }

  serial_printf(Serial, "Testing serial_printf():: %s is %o; PWM Pin is %d and Voltage is %4f V\n\n", device, status, pwmPin, voltage);
  Printf("Testing Printf() function...\n");
}

void loop() {
  static int loop;
  String names[] = {"Zhenya", "Julia", "Dasha", "Rada"};
  if (loop == 0) {
    Printf("Hello World!\n");
  } else {
    Printf("loop: %d; name: %s\n", loop, names[loop-1].c_str());
  }
  loop++;
  sleep(1);
  if (loop > 4) {
    Printf("Stop example\n");
    sleep(1);
    exit(0);
  }
}
