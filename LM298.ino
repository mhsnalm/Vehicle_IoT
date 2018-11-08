#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// Motor 1
const int dir1PinA = 9;
const int dir2PinA = 8;
const int speedPinA = 10; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
const int dir1PinB = 7;
const int dir2PinB = 6;
const int speedPinB = 5; // Needs to be a PWM pin to be able to control motor speed

int motor_speed_max = 255;
int motor_speed_zero = 0;

// LDR Sensor Pins
const int FrontLDRPin = A2;
const int BackLDRPin = A0;
const int LeftLDRPin  = A1;
const int RightLDRPin = A3;

void setup() 
{
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  display.clearDisplay();

  display.clearDisplay();

  // text display
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("System Initialized.");
  display.display();

  pinMode(dir1PinA,OUTPUT);
  pinMode(dir2PinA,OUTPUT);
  pinMode(speedPinA,OUTPUT);
  pinMode(dir1PinB,OUTPUT);
  pinMode(dir2PinB,OUTPUT);
  pinMode(speedPinB,OUTPUT);

//  forward();
//  delay(2000);
//  reverse();
//  delay(2000);
//  left();
//  delay(2000);
//  right();
}

void loop() 
{
  int LDRFront = analogRead(FrontLDRPin);
  int LDRBack = analogRead(BackLDRPin);
  int LDRLeft = analogRead(LeftLDRPin);
  int LDRRight = analogRead(RightLDRPin);

  String tmp = String(LDRFront) + " - " + String(LDRBack) + " - " + String(LDRLeft) + " - " + String(LDRRight);
  Serial.println(tmp);

  delay(100);

  if( (LDRFront > LDRBack) && (LDRFront > LDRLeft) && (LDRFront > LDRRight) )
  {
    forward();
  }
  else if( (LDRBack > LDRLeft) && (LDRBack > LDRRight) && (LDRBack > LDRFront) )
  {
    reverse();
  }
  else if( (LDRLeft > LDRFront) && (LDRLeft > LDRBack) && (LDRLeft > LDRRight)  )
  {
    left();
  }
  else
  {
    right();
  }

  delay(1000);
}

void left()
{
  analogWrite(speedPinA, motor_speed_max);//Sets speed variable via PWM
  
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);

  delay(500);

  analogWrite(speedPinA, motor_speed_zero);//Sets speed variable via PWM
}

void right() 
{
  analogWrite(speedPinB, motor_speed_max);//Sets speed variable via PWM 
 
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);

  delay(500);
  
  analogWrite(speedPinB, motor_speed_zero);//Sets speed variable via PWM 
}

void reverse() 
{
  analogWrite(speedPinA, motor_speed_max);//Sets speed variable via PWM
  analogWrite(speedPinB, motor_speed_max);//Sets speed variable via PWM 
  
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);

  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);

  delay(1000);

  analogWrite(speedPinA, motor_speed_zero);//Sets speed variable via PWM
  analogWrite(speedPinB, motor_speed_zero);//Sets speed variable via PWM 
}


void forward() 
{
  analogWrite(speedPinA, motor_speed_max);//Sets speed variable via PWM
  analogWrite(speedPinB, motor_speed_max);//Sets speed variable via PWM 
  
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);

  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);

  delay(1000);
  
  analogWrite(speedPinA, motor_speed_zero);//Sets speed variable via PWM
  analogWrite(speedPinB, motor_speed_zero);//Sets speed variable via PWM 
}
