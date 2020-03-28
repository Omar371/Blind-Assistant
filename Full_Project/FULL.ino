#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3);

#define echoPin 13 // Echo Pin
#define trigPin 5  // Trigger Pin
#define echoPin1 8 // Echo Pin
#define trigPin1 6 // Trigger Pin
const int buzzer = 7;
const int buzzer1 = 12;
const int freq = 500;
const int dur = 20;  // constants won't change. They're used here to set pin numbers:
const int SENSOR_PIN = 4; // the Arduino's input pin that connects to the sensor's SIGNAL pin 
const int pResistor = A0;            // Photoresistor at Arduino analog pin A0
const int ledPin=9;                      // Led pin at Arduino pin 9


const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)


// Variables will change:
int lastState = LOW;      // the previous state from the input pin
int currentState;         // the current reading from the input pin
int start=0;
int off=0;
int value; 

long duration, distance;
long duration1, distance1;

void setup() {
   pinMode(buzzer, OUTPUT);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(buzzer1, OUTPUT);
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
  tone(buzzer, freq, duration);
  tone(buzzer1, freq, duration1);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the Arduino's pin as aninput
  pinMode(SENSOR_PIN, INPUT);
  pinMode(11, OUTPUT);
   pinMode(ledPin, OUTPUT);        // Set lepPin - 9 pin as an output
 pinMode(pResistor, INPUT);       // Set pResistor - A0 pin as an input (optional)

 Serial.begin(9600);

  // Provide ground and power by using the analog inputs as normal digital pins.
  // This makes it possible to directly connect the breakout board to the
  // Arduino. If you use the normal 5V and GND pins on the Arduino,
  // you can remove these lines.
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);

  Serial.begin(9600);
    Serial.println("Enter AT commands:");
     
    // HC-06 default serial speed is 9600
    BTserial.begin(9600);
}

void loop() {
     value = analogRead(pResistor);
  

  // read the state of the the input pin:
  currentState = digitalRead(SENSOR_PIN);

  if(lastState == LOW && currentState == HIGH){
    Serial.println("The sensor is touched");
    start=1;
    off++;
    digitalWrite(11, HIGH); 
     Serial.println(start);}

  if(off%2==0){start=0;  digitalWrite(11, LOW); }

  // save the the last state
  lastState = currentState;

if(start == 1){
    //You can change or value "25“ to adjust the operation 
  if (value > 25){
    digitalWrite(ledPin, LOW);          //Turn led off
  }
  else{
    digitalWrite(ledPin, HIGH);          //Turn led on
  }
  
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 


 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);

 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;


 if(distance < 7){
   tone(buzzer, freq, dur);
   delay(5);
 }else if (distance < 15){
   tone(buzzer, freq, dur);
   delay(10);
 }else if (distance < 20){
   tone(buzzer, freq, dur);
   delay(15);
 }else if (distance < 30){
   tone(buzzer, freq, dur);
   delay(25);
 } else if (distance < 40){
   tone(buzzer, freq, dur);
   delay(35);
 } else if (distance < 60){
   tone(buzzer, freq, dur);
   delay(40);
 } else if (distance < 70){
   tone(buzzer, freq, dur);
   delay(45);
 } else if (distance < 80){
   tone(buzzer, freq, dur);
   delay(50);
 } else if (distance < 90){
   tone(buzzer, freq, dur);
   delay(55);
 } else if (distance < 100){
   tone(buzzer, freq, dur);
   delay(60);
 } 

 //Delay 50ms before next reading.
 delay(50);



 digitalWrite(trigPin1, LOW); 
 delayMicroseconds(2); 


 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin1, LOW);
 duration1 = pulseIn(echoPin1, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance1 = duration1/58.2;

 if(distance1 < 7){
   tone(buzzer1, freq, dur);
   delay(5);
 }else if (distance1 < 15){
   tone(buzzer1, freq, dur);
   delay(10);
 }else if (distance1 < 20){
   tone(buzzer1, freq, dur);
   delay(15);
 }else if (distance1 < 30){
   tone(buzzer1, freq, dur);
   delay(25);
 } else if (distance1 < 40){
   tone(buzzer1, freq, dur);
   delay(35);
 } else if (distance1 < 60){
   tone(buzzer1, freq, dur);
   delay(40);
 } else if (distance1 < 70){
   tone(buzzer1, freq, dur);
   delay(45);
 } else if (distance1 < 80){
   tone(buzzer1, freq, dur);
   delay(50);
 } else if (distance1 < 90){
   tone(buzzer1, freq, dur);
   delay(55);
 } else if (distance1 < 100){
   tone(buzzer1, freq, dur);
   delay(60);
 } 

 //Delay 50ms before next reading.
 delay(50);

 Serial.print(analogRead(xpin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(ypin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(zpin));
  Serial.println();
  
  // delay before next reading:
  delay(100);
if(analogRead(xpin)>=600||analogRead(ypin)>=600||analogRead(zpin)>=600){
  Serial.print("FALL DETECTED!!\n");
  BTserial.write("FALL DETECTED!!\n Location:\n Latitude: 43.0013, Longitude: -81.2757\n");
  delay(1000);
}

}
}
