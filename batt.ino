void batt() {
  int adcvalue = analogRead(voltsens);
  //Serial.print("Batt adc: ");
  //Serial.println(adcvalue);
  int volt = (adcvalue * vPow*10) / 1024.0;   // Multiply by ten -> gives a 'decimal' with an int
  int battv = volt / (r2 / (r1 + r2));
  //Serial.print("Battery: ");
  //Serial.print(volt2);
  //Serial.println("V");

  //Serial.print("COOL! I'm running on: ");
  //Serial.println(millis());

  Serial.print ("B: ");
  Serial.print(battv);
  Serial.println("V");

  //return volt2;
}
