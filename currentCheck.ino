int currentCheck(){
 // Left motor
 RawValue = analogRead(analogDrivemotorL);
 Serial.print("Adc analogDrivemotorL: ");
 Serial.println(RawValue);
 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
 AmpsL = ((Voltage - ACSoffset) / mVperAmp);
 delay(100);
 // Right motor
 RawValue = analogRead(analogDrivemotorR);
 Serial.print("Adc analogDrivemotorR: ");
 Serial.println(RawValue);
 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
 AmpsR = ((Voltage - ACSoffset) / mVperAmp);
 delay(100);
 // Cutter motor
 RawValue = analogRead(analogCutmotor);
 Serial.print("Adc analogCutmotor: ");
 Serial.println(RawValue);
 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
 AmpsC = ((Voltage - ACSoffset) / mVperAmp);
 delay(100);

 Serial.print("Amp motor L: ");
 Serial.println(AmpsL,3); // the '3' after voltage allows you to display 3 digits after decimal point
 Serial.print("Amp motor R: ");
 Serial.println(AmpsR,3);
 Serial.print("Amp cutter motor: ");
 Serial.println(AmpsC,3);

}

