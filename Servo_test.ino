/* Sweep
 * by BARRAGAN <http://barraganstudio.com>
 * This example code is in the public domain.
 */

/*I also refer to   
  http://yehnan.blogspot.tw/2013/09/arduinotower-pro-sg90.html
  and 
  http://magnusglad.wordpress.com/2013/03/13/tested-my-sg90-servo-today/
 */

#include <Servo.h> 


Servo myservo;
int pos = 0;    // variable to store the servo position

void setup() 
{ 
  // initialize serial:
  Serial.begin(9600);
  myservo.write(90); // init the Servo
  delay(3000);
} 

void loop() 
{
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees
  {                                  // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees
  {
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }  
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    /*control servo from user's uart*/
    myservo.write(inChar);
   
  }
}
