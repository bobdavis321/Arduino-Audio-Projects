/********************************************* 
Title:       Nokia 6 Analog Display
Created by:  Bob Davis
Note:        This code uses the Adafruit PDC8544 LCD library  
********************************************/
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

void setup(){
  display.begin();
  display.setContrast(50);
  display.clearDisplay();  
}

void loop(){
 display.clearDisplay();  
 // Set up for text. 
 display.setTextSize(1);
 display.setTextColor(BLACK);
 //display.setCursor(0,0);
 int analog0 = analogRead(A0)/2.05;
 int analog1 = analogRead(A1)/2.05;
 int analog2 = analogRead(A2)/2.05;
 int analog3 = analogRead(A3)/2.05;
 int analog4 = analogRead(A4)/2.05;
 int analog5 = analogRead(A5)/2.05;
 // display text values
 display.setCursor(64,0);
 display.println(analog0);
 display.setCursor(64,8);
 display.println(analog1);
 display.setCursor(64,16);
 display.println(analog2);
 display.setCursor(64,24);
 display.println(analog3);
 display.setCursor(64,32);
 display.println(analog4);
 display.setCursor(64,40);
 display.println(analog5);
 // display lines
 display.drawRect(0, 0, analog0/6, 6, BLACK);
 display.drawRect(0, 8, analog1/6, 6, BLACK);
 display.drawRect(0, 16, analog2/6, 6, BLACK);
 display.drawRect(0, 24, analog3/6, 6, BLACK);
 display.drawRect(0, 32, analog4/6, 6, BLACK);
 display.drawRect(0, 40, analog5/6, 6, BLACK);
 //Now push the buffer to the LCD for display
 display.display(); 
 delay(200);
}

