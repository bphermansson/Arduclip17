#include <Arduino.h>

void turnAround(int ttime) {
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

  // Turn left or right?
  randNumber = random(1, 10);
  if (randNumber<5) {
    Serial.println("Turn left");

    // L motor fwd
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    
    // R motor rew
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

  }
  else {
    Serial.println("Turn right");

    // L motor fwd
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    // R motor rew
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

  }

  delay(ttime);
  driveStop();

  analogWrite(enA, driveSpeed);
  analogWrite(enB, driveSpeed);
}
