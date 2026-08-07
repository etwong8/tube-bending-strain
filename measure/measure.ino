#include "HX711.h"
#include <StrainConfig.h>

HX711 scale;
long zero_offset;
bool tared = false;
long n_samples = 20;
long tare_sum = 0;

void setup() {
  Serial.begin(115200);
  scale.begin(DOUT, SCK);

  Serial.print("\n---startup measurements---\n");
  unsigned long t0 = millis();

  for (int i = 0; i < 50; i++) {
    long raw = scale.read();

    Serial.print(millis() - t0);
    Serial.print(" ms -> raw: ");
    Serial.println(raw);
  }
}

void loop() {
  if (tared == false) {
    Serial.print("\n---tare measurements---\n");
    for (int i = 0; i < n_samples; i++) {
      long reading = scale.read();
      tare_sum += reading;
      Serial.print("sample "); Serial.print(i + 1); // offset index number +1
      Serial.print(" -> raw: "); Serial.println(reading);
    }
    zero_offset = tare_sum / n_samples; // average of n_samples

    Serial.print("\nzero_offset: "); Serial.println(zero_offset);
    Serial.print("raw sample: "); Serial.println(scale.read());

    Serial.println("\n---tared, streaming live strain measurements---");
    tared = true;
  }
  
  // long counts = scale.read_average(10);
  long counts = scale.read() - zero_offset;
  float strain_ue = counts / COUNTS_PER_MICROSTRAIN;
  float weight_lb = counts / COUNTS_PER_LB;

  Serial.print("counts: "); Serial.print(counts);
  Serial.print("  microstrain (µε): "); Serial.print(strain_ue); 
  Serial.print("  weight (lb): "); Serial.println(weight_lb);
  delay(1000);
}
