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

// Initial drive motor speed
int driveSpeed = 150;

// ACS712 for measuring motor current
const int analogCutmotor = A0;
const int analogDrivemotorL = A1; // Check this!!!
const int analogDrivemotorR = A2;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500; 
double Voltage = 0;
double AmpsL = 0;
double AmpsR = 0;
double AmpsC = 0;

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
  analogWrite(enA, driveSpeed);
  analogWrite(enB, driveSpeed);
  //driveMotors();
}

void loop() {
  // checks if thread should run
  if(battThread.shouldRun())
    battThread.run();

  // Check current
  currentCheck();

  // Are we close to something?
  distanceFront();
   
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
          Serial.println ("Forward");
          driveForward();
        }
        else if (command=="2") {
          Serial.println ("Reverse");
          driveBackward();
        }
        else if (command=="3") {
          Serial.println ("Stop");
          driveStop();
        }
        else if (command=="4") {
          Serial.println ("Set drive speed!");  
          driveSpeed = serInput.substring(1).toInt();
          Serial.print("New drive speed: ");
          Serial.print(driveSpeed);  
          analogWrite(enA, driveSpeed);
          analogWrite(enB, driveSpeed);
        }
        
      
  }
}
