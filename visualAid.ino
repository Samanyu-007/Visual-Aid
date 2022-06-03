#include <Servo.h> //call servo library

//initialize servo variables for each prosthetic finger
Servo servoThumb;
//flex sensor pins assigned here-
const int thumbPin = A0;

//servo pins assigned here
int thumbServo = 10;
//====for ultrasonic sensor:
const int trigPin = 9;   // HC-SR04 trigger pin is connected to digital 9
const int echoPin = 8;   // HC-SR04 echo pin is connected to digital 8
long duration;
int cm;

void setup()
{
  Serial.begin(9600); //set baud rate for tranfer of information to UNO (9600baud) 
  //use the servo.attach function to link the servo with the UNO digital pins
  servoThumb.attach(10);
    
  //HC-SR04
  pinMode (trigPin, OUTPUT); // trigger Pin is set as output to send ultrasonic waves
  pinMode (echoPin, INPUT); // echo Pin is set as input to receive ultrasonic waves
  
  //Piezoelectric buzzer
  pinMode(5, OUTPUT); //setting signal pin of piezo buzzer for output
  delay(20); 
}
void loop()
{
  //thumb finger (Thu)
  int flexThuValue; //initialize glove flex thumb value as integer
  int servoThuPosition; //initialize prosthetic servo thumb position
  
  //since flex sensor is an analog sensor, analog read is used
  flexThuValue = analogRead(thumbPin); 
  //print the flex value read by the associated finger only if thumb is flexed for flex
  //reading above minimum  (here 953)
  if (flexThuValue > 953) 
  {
    Serial.print("Thumb: ");
    Serial.println(flexThuValue);
  }
  
  //map out the flex sensor minimum and maximum to corresponding 0 and 180deg in servo
  servoThuPosition = map(flexThuValue, 953, 1007, 0, 180);
  //since the mounted HC-SR04 only has to sweep from left to right, it is constrained to 180deg
  servoThuPosition = constrain(servoThuPosition, 0, 180); 
  //the flex sensor value read from finger flexion is mapped and written to rotate the servo appropriately
  servoThumb.write(servoThuPosition);
  
  //trigger a LOW-HIGH-LOW in the sensor to initiate its functioning
  digitalWrite(trigPin, LOW);  
  delay(500);
  digitalWrite(trigPin, HIGH);
  delay(1000);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);   // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343 for distance in cm
  
  if (cm < 50)
  {
    tone(5, 523, 1000); // play tone at 523Hz for 1000ms (1sec)
  }
  Serial.print("Distance of object= ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println(); //serial.println prints the command after it in the next line
  delay(2000);
}
