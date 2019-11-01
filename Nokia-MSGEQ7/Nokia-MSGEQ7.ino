/********************************************* 
Title:  Nokia MSGEQ7 Display
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
    // Store left band reading
    left[band] = analogRead(APIN0)/5.2;
    // Store right band reading   
    right[band] = analogRead(APIN1)/5.2;
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
 int analog0 = right[0]/2.05;
 int analog1 = right[1]/2.05;
 int analog2 = right[2]/2.05;
 int analog3 = right[3]/2.05;
 int analog4 = right[4]/2.05;
 int analog5 = right[5]/2.05;
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
 display.drawRect(0, 0, analog0, 6, BLACK);
 display.drawRect(0, 8, analog1, 6, BLACK);
 display.drawRect(0, 16, analog2, 6, BLACK);
 display.drawRect(0, 24, analog3, 6, BLACK);
 display.drawRect(0, 32, analog4, 6, BLACK);
 display.drawRect(0, 40, analog5, 6, BLACK);
 //Now push the buffer to the LCD for display
 display.display(); 
 delay(200);
}

