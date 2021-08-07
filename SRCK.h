// This the header file of the Smart Robot Car Kit
// About... 1,Motor... 2,Ultrasonic... 3,LightSensor
//  #include <SRCK.h>
// plz remember to put this file in /Arduino/libaries/SRCK

#define pin_L A2    //the port of left light sensor
#define pin_M A1    //the port of middle light sensor
#define pin_R A0    //the port of right light sensor
#define TRIG_PIN 13     //trig_pin for ultrasonic
#define ECHO_PIN 12     //echo_pin for ultrasonic
int Port[4]= {5, 8, 6, 7};	//the four ports that connect to Arduino for DRV8835
#include <Arduino.h>

//Motor Control
void initMotor()    //set the pinModes of motor control shield
{
  for(int e=0; e<4 ;e++){
	pinMode(Port[e], OUTPUT);
  }
}

void setMotor(int port, int speed)  //set the port(0,1) and speed(-255~255) to the motor
{
  int a = Port[port * 2], b = Port[port*2 + 1];
  if(port==0)
	  speed *= -1;
  if(speed > 0){
    analogWrite(a, abs(speed));
    digitalWrite(b, HIGH);
  } else if(speed < 0){
    analogWrite(a, abs(speed));
    digitalWrite(b, LOW);
  } else {
    analogWrite(a, 0);
  }
}

//Light Sensor
void initITR20001()	    //set the pinModes of ITR20001-Light Sensor
{
  pinMode(pin_L, INPUT);
  pinMode(pin_M, INPUT);
  pinMode(pin_R, INPUT);
}

float getLight_L()	//return left light sensor value
{
	return analogRead(pin_L);
}

float getLight_M()	//return middle light sensor value
{
	return analogRead(pin_M);
}

float getLight_R()	//return right light sensor value
{
	return analogRead(pin_R);
}

//Ultrasonic Sensor
void initUltrasonic()	//set the pinModes of Ultrasonic Sensor
{
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
}

int getUltrasonic()		//return the ultrasonic sensor value by cm
{
  unsigned int tempda = 0;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  tempda = ((unsigned int)pulseIn(ECHO_PIN, HIGH) / 58);
  return tempda;
}