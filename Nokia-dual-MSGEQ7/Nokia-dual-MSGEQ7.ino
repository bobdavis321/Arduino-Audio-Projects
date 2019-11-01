/********************************************* 
Title:  Nokia Dual MSGEQ7 Display
By:     Bob Davis
Note:   This code uses the Adafruit PDC8544 LCD library  
********************************************/
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
int left[7];
int right[7];
#define PIN_STROBE 9 
#define PIN_RESET 10  
#define APIN0 4 //analog input
#define APIN1 5 //analog input

void readMSGEQ7() { 
   //reset the chip
  digitalWrite(PIN_RESET, HIGH);
  digitalWrite(PIN_RESET, LOW);
  // Loop thru all 7 bands
  for(int band=0; band < 7; band++) {  
     // Go to the next band
    digitalWrite(PIN_STROBE,LOW);
    // Delay for data to stabilize
    delayMicroseconds(30);                   
    // Store left band reading 10 sets 84 as full scale
    left[band] = analogRead(APIN0)/10;
    // Store right band reading   
    right[band] = analogRead(APIN1)/10;
    // Reset the strobe pin
    digitalWrite(PIN_STROBE,HIGH);     
    }     
}

void setup(){
  pinMode(PIN_STROBE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
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
 readMSGEQ7();
 // display lines
 display.drawRect(0, 0, right[0], 2, BLACK);
 display.drawRect(0, 3, right[1], 2, BLACK);
 display.drawRect(0, 6, right[2], 2, BLACK);
 display.drawRect(0, 9, right[3], 2, BLACK);
 display.drawRect(0, 12, right[4], 2, BLACK);
 display.drawRect(0, 15, right[5], 2, BLACK);
 display.drawRect(0, 18, right[6], 2, BLACK);

 display.drawRect(0, 24, left[0], 2, BLACK);
 display.drawRect(0, 27, left[1], 2, BLACK);
 display.drawRect(0, 30, left[2], 2, BLACK);
 display.drawRect(0, 33, left[3], 2, BLACK);
 display.drawRect(0, 36, left[4], 2, BLACK);
 display.drawRect(0, 39, left[5], 2, BLACK);
 display.drawRect(0, 42, left[6], 2, BLACK);
//Now push the buffer to the LCD for display
 display.display(); 
 delay(200);
}

