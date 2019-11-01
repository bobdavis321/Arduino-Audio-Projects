// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.
//Some code by Open-Smart Team and Catalex Team
//
//Arduino IDE: 1.8.1
//Board: Arduino UNO R3 or Arduino Mega2560

// MSGEQ7 pins REMAPPED
#define PIN_STROBE 2
#define PIN_RESET 3
//#define D0 0
//#define D1 1
#define PIN_4 4 //analog input
#define PIN_5 5 //analog input
// band arrays
int left0[8]; 
int right0[8];
int left1[8]; 
int right1[8];
int left2[8]; 
int right2[8];
int left3[8]; 
int right3[8];

#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
int width=400;
int height=240;

//***********************************************//
// The control pins for the LCD can be assigned to any pins
//
// TFT Breakout  -- Arduino UNO / Mega2560 
// GND           -- GND
// 3V3           -- 3.3V
// CS            -- A3
// RS            -- A2
// WR            -- A1
// RD            -- A0
// RST           -- RESET
// LED           -- GND
// DB0           -- 8
// DB1           -- 9
// DB2           -- 10
// DB3           -- 11
// DB4           -- 4
// DB5           -- 13
// DB6           -- 6
// DB7           -- 7

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void readMSGEQ7() { //reset the chip
  digitalWrite(PIN_RESET, HIGH);
  delay (1);
  digitalWrite(PIN_RESET, LOW);
  digitalWrite (PIN_STROBE, HIGH); 
  delay (1);
  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);
  for(int band=0; band < 7; band++) {  //loop thru all 7 bands
    digitalWrite(PIN_STROBE,LOW);      // go to the next band 
    delayMicroseconds(100);             // gather data
    left0[band] = analogRead(PIN_4)/4.3;   // store band reading
    right0[band] = analogRead(PIN_5)/4.3;  // store band reading
    digitalWrite(PIN_STROBE,HIGH);     // reset the strobe pin
    }     // Second set of samples 
  digitalWrite(D0, LOW);
  digitalWrite(D1, HIGH);
  for(int band=0; band < 7; band++) {  //loop thru all 7 bands
    digitalWrite(PIN_STROBE,LOW);      // go to the next band 
    delayMicroseconds(100);             // gather data
    left1[band] = analogRead(PIN_4)/4.3;   // store band reading
    right1[band] = analogRead(PIN_5)/4.3;  // store band reading
    digitalWrite(PIN_STROBE,HIGH);     // reset the strobe pin
    } // Third set of samples
  digitalWrite(D0, HIGH);
  digitalWrite(D1, LOW);
  for(int band=0; band < 7; band++) {  //loop thru all 7 bands
    digitalWrite(PIN_STROBE,LOW);      // go to the next band 
    delayMicroseconds(100);             // gather data
    left2[band] = analogRead(PIN_4)/4.3;   // store band reading
    right2[band] = analogRead(PIN_5)/4.3;  // store band reading
    digitalWrite(PIN_STROBE,HIGH);     // reset the strobe pin
    } // Fourth set of samples
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  for(int band=0; band < 7; band++) {  //loop thru all 7 bands
    digitalWrite(PIN_STROBE,LOW);      // go to the next band 
    delayMicroseconds(100);             // gather data
    left3[band] = analogRead(PIN_4)/4.3;   // store band reading
    right3[band] = analogRead(PIN_5)/4.3;  // store band reading
    digitalWrite(PIN_STROBE,HIGH);     // reset the strobe pin
    }
}

uint16_t g_identifier;

void setup(void) {
    pinMode(PIN_STROBE, OUTPUT);
    pinMode(PIN_RESET, OUTPUT);
//    pinMode (D0, OUTPUT);
//    pinMode (D1, OUTPUT);
    
    g_identifier = tft.readID(); //
    if (g_identifier == 0x00D3 || g_identifier == 0xD3D3) g_identifier = 0x9481; // write-only shield
    if (g_identifier == 0xFFFF) g_identifier = 0x9341; // serial
    tft.begin(g_identifier);
    tft.setRotation(1);
    tft.setCursor(0, 0);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.fillRect(0, 0, width, height, BLACK);
}

void loop(void) {
    readMSGEQ7();

//    tft.fillRect(0, 0, width, height, BLACK);
//    tft.setCursor(0, 0);
//    tft.println("DUAL MSGEQ7 ON A LCD SCREEN");
  int tred=height*3/4;
  for (int b=0; b<7; b++){
    tft.fillRect(b*20, 0, 4, height, BLACK);
    tft.fillRect(b*20, height-left0[b], 4, height, GREEN);
    if (left0[b]>tred) {
      tft.fillRect(b*20, height-left0[b], 4, left1[b]-tred, RED);
    }
  } 
  for (int b=0; b<7; b++){
    tft.fillRect(b*20+5, 0, 4, height, BLACK);
    tft.fillRect(b*20+5, height-left1[b], 4, height, GREEN);
    if (left1[b]>tred) {
      tft.fillRect(b*20+5, height-left1[b], 4, left0[b]-tred, RED);
    }
  } 
  for (int b=0; b<7; b++){
    tft.fillRect(b*20+10, 0, 4, height, BLACK);
    tft.fillRect(b*20+10, height-left2[b], 4, height, GREEN);
    if (left2[b]>tred) {
      tft.fillRect(b*20+10, height-left2[b], 4, left0[b]-tred, RED);
    }
  }
  for (int b=0; b<7; b++){
    tft.fillRect(b*20+15, 0, 4, height, BLACK);
    tft.fillRect(b*20+15, height-left3[b], 4, height, GREEN);
    if (left3[b]>tred) {
      tft.fillRect(b*20+15, height-left3[b], 4, left0[b]-tred, RED);
    }
  }
  for (int b=0; b<7; b++){
    tft.fillRect(b*20+170, 0, 4, height, BLACK);
    tft.fillRect(b*20+170, height-right0[b], 4, height, GREEN);
    if (right0[b]>tred) {
      tft.fillRect(b*20+170, height-right0[b], 4, right1[b]-tred, RED);
    }
  }  
  for (int b=0; b<7; b++){
    tft.fillRect(b*20+175, 0, 4, height, BLACK);
    tft.fillRect(b*20+175, height-right1[b], 4, height, GREEN);
    if (right1[b]>tred) {
      tft.fillRect(b*20+175, height-right1[b], 4, right0[b]-tred, RED);
    }
  }  
  for (int b=0; b<7; b++){
    tft.fillRect(b*20+180, 0, 4, height, BLACK);
    tft.fillRect(b*20+180, height-right2[b], 4, height, GREEN);
    if (right2[b]>tred) {
      tft.fillRect(b*20+180, height-right2[b], 4, right0[b]-tred, RED);
    }
  }  
  for (int b=0; b<7; b++){
    tft.fillRect(b*20+185, 0, 4, height, BLACK);
    tft.fillRect(b*20+185, height-right3[b], 4, height, GREEN);
    if (right3[b]>tred) {
      tft.fillRect(b*20+185, height-right3[b], 4, right0[b]-tred, RED);
    }
  }  

  delay(100);
}


