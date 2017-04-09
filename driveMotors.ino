 void driveForward() {

  // turn on motor A
  /*
  // set speed to 150 out of possible range 0~255
  // Note: 80 is about the lowest possible speed!
  analogWrite(enA, 80);
  // now change motor directions
  //digitalWrite(in1, LOW);
  //digitalWrite(in2, HIGH);  
  //digitalWrite(in3, LOW);
  //digitalWrite(in4, HIGH); 
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  */

  // L motor fwd
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // R motor fwd
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void driveBackward() {
  // L motor rew
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // R motor rew
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void driveStop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

