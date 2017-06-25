#include <Arduino.h>

void turnAround(int ttime) {
  Serial.println("Turn around");
  int oldSpeed = driveSpeed;
  
  // Set speed
  analogWrite(enA, 120);
  analogWrite(enB, 120);

  // First back
  // L motor rew
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // R motor rew
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(1500);

  driveStop();
  delay(500);

  // L motor fwd
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  // R motor rew
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(ttime);
  driveStop();

  analogWrite(enA, driveSpeed);
  analogWrite(enB, driveSpeed);
}
