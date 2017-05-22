int batt() {
  // https://startingelectronics.org/articles/arduino/measuring-voltage-with-arduino/
  
  int adcvalue = analogRead(voltsens);
  
  //Serial.print("Batt adc: ");
  //Serial.println(adcvalue);   // 143
    
  float voltage= adcvalue * (5.0 / 1023.0); 
  
  //Serial.println(voltage);
  
  /* Volt meter reads 27,72
     Code says 4,48
     27,72/4,48 = 6,1875 
  */
  battv = voltage * 6.1875 * 10;  // Preserve one decimal with battv (is a Int)
  
  /*
  Serial.print("battv: ");
  Serial.print(battv);
  Serial.println("V");
  */
  
  return battv;
}
