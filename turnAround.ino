void turnAround() {
  int oldSpeed = driveSpeed;
  
  // Set speed
  analogWrite(enA, 120);
  analogWrite(enB, 120);

  // First back
  // L motor rew
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // R motor rew
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(1500);

  driveStop();
  delay(1000);

  // L motor fwd
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  // R motor rew
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(2500);
  driveStop();

  analogWrite(enA, driveSpeed);
  analogWrite(enB, driveSpeed);
}

