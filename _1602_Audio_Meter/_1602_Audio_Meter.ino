//*****************************************
// 1602 Audio Meter
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
byte line1[8]= {
B10000,B10000,B10000,B10000,B10000,B10000,B10000,B10000
};
byte line2[8]= {
B11000,B11000,B11000,B11000,B11000,B11000,B11000,B11000
};
byte line3[8]= {
B11100,B11100,B11100,B11100,B11100,B11100,B11100,B11100
};
byte line4[8]= {
B11110,B11110,B11110,B11110,B11110,B11110,B11110,B11110
};
byte line5[8]= {
B11111,B11111,B11111,B11111,B11111,B11111,B11111,B11111
};
  
void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Send the new characters to the LCD.
  lcd.createChar(1, line1);
  lcd.createChar(2, line2);
  lcd.createChar(3, line3);
  lcd.createChar(4, line4);
  lcd.createChar(5, line5);
}

void loop() {
  lcd.clear();
  int Voltage0=analogRead(A0)/.205;
  int Voltage1=analogRead(A1)/.205;
  // Optionally print the voltage:
  lcd.setCursor(12, 0);
  lcd.print(Voltage0);
  lcd.setCursor(12, 1);
  lcd.print(Voltage1);
 
  int metervolts=Voltage0/25;
  for(int pos=0; pos<metervolts/10; pos++){
     lcd.setCursor(pos, 0);
     lcd.write(255);
      }
  lcd.setCursor(metervolts/10, 0);
  if (metervolts%10/2 == 0) lcd.write(1);
  if (metervolts%10/2 == 1) lcd.write(2);
  if (metervolts%10/2 == 2) lcd.write(3);
  if (metervolts%10/2 == 3) lcd.write(4);
  if (metervolts%10/2 == 4) lcd.write(5);
  metervolts=Voltage1/25;
  for(int pos=0; pos<metervolts/10; pos++){
     lcd.setCursor(pos, 1);
     lcd.write(255);
      }
  lcd.setCursor(metervolts/10, 1);
  if (metervolts%10/2 == 0) lcd.write(1);
  if (metervolts%10/2 == 1) lcd.write(2);
  if (metervolts%10/2 == 2) lcd.write(3);
  if (metervolts%10/2 == 3) lcd.write(4);
  if (metervolts%10/2 == 4) lcd.write(5);
  delay(200);
}

