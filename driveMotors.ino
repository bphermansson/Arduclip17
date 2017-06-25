 void driveForward() {
  Serial.println("Drive forward");

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
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  // R motor fwd
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(300);

  // Cutter on
  Serial.println("Cutter on");
  analogWrite(dc, 0);

}
void driveBackward() {
  Serial.println("Drive backward");

  // Cutter off
  Serial.println("Cutter off");
  analogWrite(dc, 255);
  
  // L motor rew
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // R motor rew
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void driveStop() {
  Serial.println("Stop");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  // Cutter off
  analogWrite(dc, 255);
  Serial.println("Cutter off");
}

void left() {
  Serial.println("Left");
   // Cutter off
  analogWrite(dc, 255);
  Serial.println("Cutter off");
 
  // L motor rew
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  // R motor fwd
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void right() {
  Serial.println("Right");
  // Cutter off
  analogWrite(dc, 255);
  Serial.println("Cutter off");

  // L motor fwd
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  // R motor rew
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void cutterOn(){
  // Cutter on
  pinMode(dc, OUTPUT);
  analogWrite(dc, 0);
  Serial.println("Cutter on");
}
void cutterOff(){
  // Cutter off
  // pinMode(dc, INPUT);
  analogWrite(dc, 255);
  Serial.println("Cutter off");
}

