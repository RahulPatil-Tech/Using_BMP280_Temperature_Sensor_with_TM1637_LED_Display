/*
 * Temperature Sensors
 * BMP280 with TM1637
/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMEP280 Breakout
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/
#include <math.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

// start of settings of TM1637 display
#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 5
#define DIO 6
TM1637Display display(CLK, DIO);
uint8_t blank[] = { 0x0, 0x0, 0x0, 0x0 };// blank value for all digits
 uint8_t allSegment[] = { 0xff, 0xff, 0xff, 0xff };// all segment ON
// start of settings of TM1637 display

void setup() {
  Serial.begin(9600);
  Serial.println("BMP280 demo by Robojax");
   display.setBrightness(0x0f);  
  if (!bmp.begin()) {
      Serial.println("BMP280 Module Error"); 
    while (1);
  }
 }

void loop() {  
  Serial.print(getTemp('C'));// print Temperature in Celsius
        Serial.println(" C");// print C 
  Serial.print(getTemp('F'));// print Temperature in Celsius
        Serial.println(" F");// print F   
  Serial.print(getTemp('K'));// print Temperature in Kelvin
        Serial.println(" K");// print K  
  Serial.println(); 

  display.setSegments(allSegment);
  delay(3000);

  display.setSegments(blank);
  display.showNumberDec(round(getTemp('C')));
  delay(3000);

  display.setSegments(blank);
  display.showNumberDec(round(getTemp('F')));  
  delay(3000);



   display.setSegments(blank);
  display.showNumberDec(round(bmp.readAltitude(1013.25)));  
  delay(3000);   

   
  delay(1000);
}// loop end

/*
 * Written by Rahul Patil 
 * Aug 19, 2022 in Dombivali,Kalyan,Maharashtra
 * getTemp(char type)
 * returns temperature in either C, F or K
 * @param type is character of upper case 
 * C is used to get Celsius
 * F is used to get fahrenheit
 * K is used for Kelvin
 * Written by Ahmad Shamshiri for Robojax.com
 * 
 */
float getTemp(char type) {
    float c = bmp.readTemperature();//get main temperature in C
  float f = c * 9.0 / 5.0 + 32;// convert to fahrenheit
  if(type =='F')
  {
    return f;// fahrenheit
  }else if(type =='K')
  {
    return c + 274.15;// return Kelvin
  }else{
   return c; //return Celsius
  }
  
}//getTemp ends
