/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/arduino-load-cell-hx711/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

// Calibrating the load cell
#include "HX711.h"
#include <StrainConfig.h>

HX711 scale;

void setup() {
  Serial.begin(115200);
  scale.begin(DOUT, SCK);
}

void loop() {

  if (scale.is_ready()) {
    scale.set_scale();    
    Serial.println("Tare... remove any weights from the scale.");
    delay(10000);           
    scale.tare();
    Serial.println("Tare done...");
    Serial.print("Place a known weight on the scale...");
    delay(20000);
    long reading = scale.get_units(10);
    Serial.print("Result: ");
    Serial.println(reading);
  } 
  else {
    Serial.println("HX711 not found.");
  }
  delay(1000);
}
