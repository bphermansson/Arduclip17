int currentCheckLM(){
 // Left motor
 RawValue = analogRead(analogDrivemotorL);
 Serial.print("Adc analogDrivemotorL: ");
 Serial.println(RawValue);
 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
 AmpsL = ((Voltage - ACSoffset) / mVperAmp);
 Serial.print("Amp motor L: ");
 Serial.println(AmpsL,3); // the '3' after voltage allows you to display 3 digits after decimal point
 return AmpsL;
 delay(100);
} 
 
int currentCheckRM(){
 // Right motor
 RawValue = analogRead(analogDrivemotorR);
 Serial.print("Adc analogDrivemotorR: ");
 Serial.println(RawValue);
 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
 AmpsR = ((Voltage - ACSoffset) / mVperAmp);
 Serial.print("Amp motor R: ");
 Serial.println(AmpsR,3);
 return AmpsR;
 delay(100);
}
int currentCheckCM(){
 // Cutter motor
 RawValue = analogRead(analogCutmotor);
 Serial.print("Adc analogCutmotor: ");
 Serial.println(RawValue);
 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
 AmpsC = ((Voltage - ACSoffset) / mVperAmp);
 Serial.print("Amp cutter motor: ");
 Serial.println(AmpsC,3);
 return AmpsC;
 delay(100);
}

