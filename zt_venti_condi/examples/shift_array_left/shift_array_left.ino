/************************************************************************
 * shift_array_left 
 * 
 * Example for VentiCondi Project:
 *    shifts an array left with new value added right and evaluates a trend
 * 
 * 29.07.2021 ZT
 * 02.08.2021 Last update
 ************************************************************************/
#include <zt_venti_condi.h>

const unsigned int ARRAY_SIZE = 4;
unsigned int pwms[ARRAY_SIZE] = {0};
int count = 0;

void setup() {
  Serial.begin(9600);
  slepp(2);  // MUST BE!
  Printf("===== Starting Shift Array Left test for VentiCondi Project...\n");
}

void loop() {
  String trend;
  unsigned int last = pwms[ARRAY_SIZE-1];

  if (count < 10) {
    shiftArrayLeft(pwms, ARRAY_SIZE, ++last);  // Up
  } else {
    shiftArrayLeft(pwms, ARRAY_SIZE, --last);  // Down
  }
  
  trend = getTrend(pwms, ARRAY_SIZE);
  
  for (int i = 0; i < ARRAY_SIZE; i++) {
    Printf("%d; %s\n", pwms[i], trend.c_str());
  }

  if (last == 0) {
    count = 0;
  } else {
    count++;
  }
  
  slepp(1);
}
