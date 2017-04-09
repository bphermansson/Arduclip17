#include <Thread.h>   // Timing functions
Thread battThread = Thread();

// Connections for wheel motor drivers
// Motor L
int enA = 5;
int in1 = 6;
int in2 = 7;
// Motor R
int enB = 9;
int in3 = 8;
int in4 = 10;

int speed = 150;

// Motor driver current sensor, used to determin load on drive wheels
int loadL;
int loadR;
// A0 and A1 reads the values
#define loadPinL 0
#define loadPinR 1

// Measure battery voltage
int battv;  // Holds battery voltage value
int batteryVoltage;
// Input to pin A3
#define voltsens 3
float vPow = 5.02; // Voltage at the Arduinos Vcc and Vref. 
float r1 = 11000;  // "Top" resistor, 11k (10+1)
float r2 = 2200;   // "Bottom" resistor (to ground), 2.2 kohm. 

void setup() {
  Serial.begin (9600);
  Serial.println("Welcome to Arduclip 2017 v0.1"); 
  Serial.println("1-forward, 2-back, 3-stop, 4nnn-Set speed to nnn");
  // Setup pins for motor drivers
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Drive motors off
  driveStop();

  // Battery voltage
  pinMode(voltsens, INPUT);
  //battv = batt();       // Check

  battThread.onRun(batt);
  battThread.setInterval(5000);  
  
  // Initial motor test
  // Set drive motor speed
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  //driveMotors();
}

void loop() {
  // checks if thread should run
  if(battThread.shouldRun())
    battThread.run();
  // if there's any serial available, read it:
  while (Serial.available() > 0) {
      String serInput = Serial.readStringUntil("\n");
      Serial.println("Got serial data");
      // look for the newline. That's the end of your sentence:
      //if (Serial.read() == '\n') {
        Serial.print("Got: ");
        Serial.println(serInput);
        // The first char is the command. This can be followed by a value
        String command = serInput.substring(0,1);
        //Serial.println(command);
        
        if (command=="1") {
          Serial.print ("Forward");
          driveForward();
        }
        else if (command=="2") {
          Serial.print ("Reverse");
          driveBackward();
        }
        else if (command=="3") {
          Serial.print ("Stop");
          driveStop();
        }
        else if (command=="4") {
          Serial.print ("Set speed!");  
          speed = serInput.substring(1).toInt();
          Serial.print("New speed: ");
          Serial.print(speed);  
        }
        
      //}
  }
}
