#include <Arduino.h>

int distanceFront() {
 /* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 
 if (distance >= maximumRange || distance <= minimumRange){
   /* Send a negative number to computer and Turn LED ON 
   to indicate "out of range" */
   Serial.println("-1");
   digitalWrite(LEDPin, HIGH); 
 }
 else {
   /* Send the distance to the computer using Serial protocol, and
   turn LED OFF to indicate successful reading. */
   //Serial.print("distance: ");   
   //Serial.println(distance);
   digitalWrite(LEDPin, LOW); 
 }
 
 //Delay 50ms before next reading.
 delay(50);
 return distance;
}

