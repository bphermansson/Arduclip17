/* Red led for error indication
 * Check value for batt low
 * 
 * 
 */


//#include <Thread.h>   // Timing functions
//Thread battThread = Thread();
#include <Time.h>

// Prototypes
int batt();
int currentCheckLM();
int currentCheckRM();
int currentCheckCM();
int distanceFront();
void turnAround(int ttime);
void driveForward();
void driveBackward();
void driveStop();
void cutterOn();
void cutterOff();

// Connections for wheel motor drivers
// Motor L
int enA = 5;
int in1 = 6;
int in2 = 7;
// Motor R
int enB = 10;// Bytt plats på 9 och 10
int in3 = 8;
int in4 = 9;

// Cutter driver connection
int dc = 3; 
int cutterSpeed = 255;  // This is connected via a inverting transistor, 255 is off

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

// HC-SR04 distance sensor
int echoPin = 11; // Echo Pin     
int trigPin = 12; // Trigger Pin
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
boolean distSensorEn = true;


// Measure battery voltage
int battv;  // Holds battery voltage value
int batteryVoltage;
// Input to pin A3
int voltsens = 3;
//float vPow = 5.02; // Voltage at the Arduinos Vcc and Vref. 
//int r1 = 11000;  // "Top" resistor, 11k (10+1)
//int r2 = 2200;   // "Bottom" resistor (to ground), 2.2 kohm. 

long lastMsg = 0;

int LEDPin = 13; // Onboard LED
int redLed = 0; // CHECK THIS

String instructions="1-forward, 2-back, 3-stop, 4nnn-Set speed to nnn, 5 -cutter on, 6 - cutter off, 7 - distSensorEn toggle";

void setup() {
  // Setup pins for motor drivers
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(dc, OUTPUT);

  delay(300);
  
  // Cutter motor off
  cutterOff();
  // Drive motors off
  driveStop();

  // Distance sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Battery voltage
  pinMode(voltsens, INPUT);
  battv = batt();       // Check
  Serial.print ("B: ");
  Serial.print(battv/10);
  Serial.println("V");
  // Set drive motor speed
  analogWrite(enA, driveSpeed);
  analogWrite(enB, driveSpeed);
  //driveForward();
  //delay(2000);
  //driveStop();


  Serial.begin (9600);
  Serial.println("Welcome to Arduclip 2017 v0.2"); 
  Serial.println(instructions);

}

void loop() {
  long now = millis();
  if (now - lastMsg > 1000) {
      lastMsg = now;
      
      battv = batt(); 
      //Serial.print ("B: ");
      //Serial.print(battv/10);
      //Serial.println("V (in main)");
  
      if (battv/10 < 23) {
        driveStop();
        analogWrite(dc, 255);   // Cutter off
        Serial.println("Batt low, power off");
        
      }
      //Serial.println(instructions);
  }
  // Check current
  int currentLM = currentCheckLM();
  int currentRM = currentCheckRM();
  int currentCM = currentCheckCM();

  if (currentLM > 2 || currentRM > 2 || currentCM > 5){
        driveStop();
        analogWrite(dc, 255);   // Cutter off      
        if (currentLM > 2 || currentRM > 2) {
          Serial.println("Drive motor current high");
        }
        else if (currentCM > 5) {
          Serial.println("Cutter motor current high");
        }
        turnAround(1000);
  }

  // Are we close to something?
  //Serial.print ("distSensorEn: ");
  //Serial.println (distSensorEn);
  if (distSensorEn) {
    int distance = distanceFront();
    //Serial.print("Distance: ");
    //Serial.println(distance);
    if (distance <= 10){
      turnAround(1000);
      Serial.println("Turning, obstacle");
    }
  }

  // if there's any serial available, read it:
  while (Serial.available() > 0) {
      String serInput = Serial.readStringUntil('\n');
        //Serial.print("Got: ");
        //Serial.println(serInput);
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
          Serial.println(driveSpeed);  
          analogWrite(enA, driveSpeed);
          analogWrite(enB, driveSpeed);
        }  
        else if (command=="5") {
          Serial.print("Cutter on ");
          analogWrite(dc, 0);
        }
        else if (command=="6") {
          Serial.println("Cutter off");
          analogWrite(dc, 255);
        }
        else if (command=="7") {
          Serial.println("Distance sensor toggle");
          distSensorEn = !distSensorEn;
        }
  }
  delay(1000);
}
