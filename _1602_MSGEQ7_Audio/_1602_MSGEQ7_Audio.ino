//*****************************************
// 1602 MSGEQ7 Audio Meter
// 8-19-2019 By Bob Davis
// Wiring:
// * LCD RS pin to digital pin 8
// * LCD En pin to digital pin 9
// * LCD D4 pin to digital pin 4
// * LCD D5 pin to digital pin 5
// * LCD D6 pin to digital pin 6
// * LCD D7 pin to digital pin 7
// * LCD R/W pin to ground
// * Variable resistor wiper to LCD VO pin (pin 3)
// 

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with interface pin #'s
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Create Special characters:
byte line1[8] = {
  B00000,B00000,B00000,B00000,B00000,B00000,B00000,B11111
};
byte line2[8] = {
  B00000,B00000,B00000,B00000,B00000,B00000,B11111,B11111
};
byte line3[8] = {
  B00000,B00000,B00000,B00000,B00000,B11111,B11111,B11111
};
byte line4[8] = {
  B00000,B00000,B00000,B00000,B11111,B11111,B11111,B11111
};
byte line5[8] = {
  B00000,B00000,B00000,B11111,B11111,B11111,B11111,B11111
};
byte line6[8] = {
  B00000,B00000,B11111,B11111,B11111,B11111,B11111,B11111
};
byte line7[8] = {
  B00000,B11111,B11111,B11111,B11111,B11111,B11111,B11111
};
byte line8[8] = {
  B11111,B11111,B11111,B11111,B11111,B11111,B11111,B11111
};
// store MSGEQ7 values here
int left[7]; 
int right[7];
#define PIN_STROBE 10
#define PIN_RESET 11
#define APIN0 0 //analog input
#define APIN1 1 //analog input

void readMSGEQ7() { //reset the chip
  digitalWrite(PIN_RESET, HIGH);
  digitalWrite(PIN_RESET, LOW);
  for(int band=0; band < 7; band++) {  // loop thru all 7 bands
    digitalWrite(PIN_STROBE,LOW);      // go to the next band 
    delayMicroseconds(30);             // gather data
    left[band] = analogRead(APIN0)/32;   // store band reading
    right[band] = analogRead(APIN1)/32;  // store band reading
    digitalWrite(PIN_STROBE,HIGH);     // reset the strobe pin
    }     
}
  
void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Send the new characters to the LCD.
  lcd.createChar(1, line1);
  lcd.createChar(2, line2);
  lcd.createChar(3, line3);
  lcd.createChar(4, line4);
  lcd.createChar(5, line5);
  lcd.createChar(6, line6);
  lcd.createChar(7, line7);
  lcd.createChar(8, line8);
  pinMode(PIN_STROBE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
}

void loop() {
  lcd.clear();
  readMSGEQ7();
//  lcd.write("L       R");
  lcd.setCursor(1, 0);    
  for(int pos=0; pos<7; pos++){
    if (left[pos]>8) lcd.write(left[pos]-8);      
    }
  lcd.setCursor(9, 0);    
  for(int pos=0; pos<7; pos++){
    if (right[pos]>8) lcd.write(right[pos]-8);  
    }
  lcd.setCursor(1, 1);        
  for(int pos=0; pos<7; pos++){
    if (left[pos]<8){
      lcd.write(left[pos]+1);
    }
    else lcd.write(255);
  }
  lcd.setCursor(9, 1);    
  for(int pos=0; pos<7; pos++){
    if (right[pos]<8){ 
      lcd.write(right[pos]+1);
    }
    else lcd.write(255);
  }
  delay(300);
}

