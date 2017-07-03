#include <Arduino.h>

/* Red led for error indication
 * Check value for batt low
 *
 *
 */


//#include <Thread.h>   // Timing functions
//Thread battThread = Thread();
//#include <Time.h>

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

const char compile_date[] = __DATE__ " " __TIME__;

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
int driveSpeed = 120;

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
int randNumber;

int LEDPin = 13; // Onboard LED
int greenLed = 2;
int redLed = 4;

String instructions="1-forward, 2-back, 3-stop, 4 - N/A, 5 -cutter on, 6 - cutter off, 7 - distSensorEn toggle, 8 - left, 9 - right, I - Faster, D - Slower";

void setup() {
  // Setup pins for motor drivers
  // set all the motor control pins to outputs
  pinMode(dc, OUTPUT);
  // Cutter motor off
  cutterOff();

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  delay(100);
  // Drive motors off
  driveStop();

  // Distance sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  digitalWrite(greenLed, HIGH); // Power on
  digitalWrite(redLed, HIGH);   // Test red led, off at end of setup
  // Set drive motor speed
  analogWrite(enA, driveSpeed);
  analogWrite(enB, driveSpeed);
  //driveForward();
  //delay(2000);
  //driveStop();

  randomSeed(analogRead(5));

  Serial.begin (115200);
  Serial.println("Welcome to Arduclip 2017 v0.2");
  Serial.println(compile_date);
  Serial.println(instructions);

  // Battery voltage
  pinMode(voltsens, INPUT);
  battv = batt();       // Check
  Serial.print ("B: ");
  Serial.print(battv/10);
  Serial.println("V");

  delay(300);
  digitalWrite(redLed, LOW);

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
        digitalWrite(redLed, HIGH);
        driveStop();
        analogWrite(dc, 255);   // Cutter off
        Serial.print ("B: ");
        Serial.print(battv/10);
        Serial.println("V");
        Serial.println("Batt low");
        // Make another measurement with motors off
        delay(300);
        battv = batt();
        if (battv/10 < 23) {
          // Still low
          Serial.println("Batt low, power off");
        }
        else {
          // Move on
          digitalWrite(redLed, LOW);
          driveForward();
        }
      }
      //Serial.println(instructions);
  }
  // Check current
  int currentLM = currentCheckLM();
  int currentRM = currentCheckRM();
  int currentCM = currentCheckCM();

  if (currentLM > 2 || currentRM > 2 || currentCM > 10){
        digitalWrite(redLed, HIGH);
        if (currentLM > 2 || currentRM > 2) {
          Serial.println("Drive motor current high");
          // Wait and see if its temporary
          delay(500);
          // Measure again
          int currentLM = currentCheckLM();
          int currentRM = currentCheckRM();
          if (currentLM > 2 || currentRM > 2) {
            Serial.println("Drive motor current still high");
            driveStop();
            // Turn around and drive on
            randNumber = random(1000, 2500);
            turnAround(randNumber);
            digitalWrite(redLed, LOW);
            driveForward();
          }
          else {
            // It was temporary high load
            digitalWrite(redLed, LOW);
            driveForward();
          }
        }
        else if (currentCM > 10) {
          Serial.println("Cutter motor current high");
          // Wait and see if its temporary
          delay(500);
          int currentCM = currentCheckCM();
          if (currentCM > 10) {
            // Still high
            driveStop();
            // Turn around and drive on
            randNumber = random(1000, 2500);
            turnAround(randNumber);
            digitalWrite(redLed, LOW);
            driveForward();
          }
          else {
            // It was temporary high load
            digitalWrite(redLed, LOW);
            driveForward();
          }
        //driveForward();
      }
  }

  // Are we close to something?
  //Serial.print ("distSensorEn: ");
  //Serial.println (distSensorEn);
  if (distSensorEn) {
    int distance = distanceFront();
    //Serial.print("Distance: ");
    //Serial.println(distance);
    if (distance <= 10){
      digitalWrite(redLed, HIGH);
      randNumber = random(1000, 2500);
      turnAround(randNumber);
      Serial.println("Turning, obstacle");
      digitalWrite(redLed, LOW); 
      driveForward();

    }
  }

  // if there's any serial available, read it:
  while (Serial.available() ) {
      String serInput = Serial.readStringUntil('\n');
      //int serInput = Serial.read();
      serInput.trim();
        // Debug
        Serial.print("Got: -");
        Serial.print(serInput);
        Serial.println("-");

        if (serInput=="1") {
          Serial.println ("Forward");
          driveForward();
        }
        else if (serInput=="2") {
          Serial.println ("Reverse");
          driveBackward();
        }
        else if (serInput=="3") {
          Serial.println ("Stop");
          driveStop();
        }
        else if (serInput=="4") {

        }
        else if (serInput=="5") {
          Serial.print("Cutter on ");
          analogWrite(dc, 0);
        }
        else if (serInput=="6") {
          Serial.println("Cutter off");
          analogWrite(dc, 255);
        }
        else if (serInput=="7") {
          Serial.println("Distance sensor toggle");
          distSensorEn = !distSensorEn;
        }
        else if (serInput=="8") {
          left();
        }
        else if (serInput=="9") {
          right();
        }
        else if (serInput=="I") {
          driveSpeed=driveSpeed+10;
          if (driveSpeed>=250) {
            driveSpeed=250;
          }
          Serial.print("New drive speed is: ");
          Serial.println(driveSpeed);
        }
        else if (serInput=="D") {
          driveSpeed=driveSpeed-10;
          if (driveSpeed<=80) {
            driveSpeed=80;
          }
          Serial.print("New drive speed is: ");
          Serial.println(driveSpeed);
        }

  }
  delay(1000);
            //Serial.println("Loop");

}
