/*
 * This program is designed for the robot on Assembly Line 1 using a small Pnuematic
 * This program will determine if the box is white or brown and then sort the white boxes.
 */
#include <Adafruit_TCS34725.h>

#define Forward 12
#define Back 11
Adafruit_TCS34725 ColorSense = Adafruit_TCS34725();

void setup() {
  Serial.begin(9600);   
  Serial.println("Testing");    
  if(ColorSense.begin())//determines if sensor is connected correctly
  {
    Serial.println("Found Sensor");
  }
  else{
    Serial.println("Check Sensor");   
    Serial.println("if connected restart"); 
    while(1);  
  }
  pinMode(Forward,OUTPUT);//used to push arm forward
  pinMode(Back,OUTPUT);//used to push arm back
  digitalWrite(Forward,LOW);//sets to off
  digitalWrite(Back,LOW);//sets to off

  //ColorSense.setGain();//add if needing to change Gain
  //ColorSense.setIntegrationTime();//add if needing  to set integrationTime for higher sampling ie less frequent samples
}

void loop() {
  uint16_t Bread, Gread, Rread, Cread;
  
  ColorSense.getRawData(&Rread,&Gread,&Bread,&Cread);//get RGB data from sensor

  if(Rread>17){//if red is higher then 17 its not reading the wall and the values of brown boxes and white boxes start to differ
    Serial.print("Reading");
    Serial.print(Rread, DEC); Serial.print(",");
    Serial.print(Gread, DEC); Serial.print(",");
    Serial.print(Bread, DEC); Serial.print(",");
    Serial.println(" ");
    if((Rread>Bread)){//brown has higher red then blue values useually
      //Do nothing
      //Serial.println("Brown");
    }
    if(Bread>=20){
      Serial.println("White");
      delay(1000);//delay to reach end of tunnel
      Serial.println(" Forward");
      digitalWrite(Forward,HIGH);//arm forward
      delay(5000);//how long it takes to fully extent
      digitalWrite(Forward,LOW);//turning off selenoid for forward
      delay(1500);
      Serial.println(" Back");
      digitalWrite(Back,HIGH);//start back sequence
      delay(900);//how long it takes to get out of the way
      digitalWrite(Back,LOW);
    }
   }
}

