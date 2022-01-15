// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pins 
int servoPin1 = 9; 
int servoPin2=10;
// Create a servo object 
Servo Servo1; 
Servo Servo2;

int val;
int tempPin = A0;
int ir1 =2;
int state=LOW;
int led = 13;

//int ir2=4;
//int ir2state=LOW;


int count=0;
int k=0;

const int xpin = A1; // x-axis of the accelerometer
const int ypin = A2; // y-axis
const int zpin = A3; // z-axis
 

void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin1); 
   Servo2.attach(servoPin2);
   pinMode(ir1,INPUT);
   pinMode(led, OUTPUT);
  // pinMode(ir2,INPUT);
   Serial.begin(9600);
}

void loop(){  
 state = digitalRead(ir1); //state=output of ir sensor
 //Serial.println(state);
 delay(2000);
  if (state == HIGH) //if object detected
  {
   // Make servo go to 0 degrees 
  val = analogRead(tempPin);//gives analog output voltage
  float mv = ( val/1024.0)*5000; //converting to mv; 5000 since 5V and 1024 since ADC has definition of 1024 values(10 bits)
  float cel = mv/10; //converting to celsius from mv
  float farh = (cel*9)/5 + 32; //converting to fahrenheit from celcius
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  delay(2000);
  
  if(cel <37) //if individual doesn't have a fever
  {
    if(count<4) //if there are less than 4 people in the enclosure
    {
   Serial.print("Someone is entering");
   Serial.println();
   Servo1.write(0); 
   delay(2000); 
   // Make servo go to 90 degrees
   Servo1.write(90); 
   delay(2000); 
   // Make servo go to 180 degrees 
   //Servo1.write(-90); 
  // delay(3000); 

   count=count+1; //count number of people who entered enclosure
   Serial.println("Count= ");
   Serial.println(count);
  }
  else
  {
    Serial.print("Too many people!!Access denied");
    Serial.println();
    digitalWrite(led, HIGH);
    delay(3000);
    digitalWrite(led,LOW);
  }
  }
  else 
  {
    Serial.print("Temperature too high!!Access denied");
    Serial.println();
    digitalWrite(led, HIGH);
    delay(3000);
    digitalWrite(led,LOW);
  }
  }
  else //if no movement is there in front of ir sensor
  {
    Serial.print("No object detected");
    Serial.println(" ");
    delay(2000);  
  } 

//accelerometer
int x = analogRead(xpin); //read from xpin
delay(1); //
int y = analogRead(ypin); //read from ypin
delay(1); 
int z = analogRead(zpin); //read from zpin
 
float zero_G = 512.0;
float scale = 102.3;
int x_reading[100];
x_reading[k]=((float)x - 331.5)/65*9.8;
Serial.print(x_reading[k]); //print x value on serial monitor
Serial.print("\t");
int y_reading[100];
y_reading[k]=((float)y - 329.5)/68.5*9.8;
Serial.print(y_reading[k]); //print y value on serial monitor
Serial.print("\t");
int z_reading[100];
z_reading[k]=((float)z - 340)/68*9.8;
Serial.print(z_reading[k]); //print z value on serial monitor
Serial.print("\n");
delay(1000); //wait for 1 second 

 if (abs(x_reading[k]-x_reading[k-1])>2 ||abs(y_reading[k]-y_reading[k-1])>2 ||  abs(z_reading[k]-z_reading[k-1])>2) //if there is a difference between previous and current pos of accelerometer,i.e, movement
 {
  if(count>1)
  {
    Serial.println("Someone is going out");
    Servo2.write(0);
    delay(2000);
    Servo2.write(90);
    delay(2000);
    count=count-1; //decrement number of people inside when someone exits
    Serial.println("Count= ");
    Serial.println(count);
    Serial.println();
 }
 }
 k=k+1;
  
}
