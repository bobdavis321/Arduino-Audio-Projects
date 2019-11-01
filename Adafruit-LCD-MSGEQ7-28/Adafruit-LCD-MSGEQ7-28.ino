// Open-Smart-MSGEQ7-2
// By Bob Davis
//
// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.
// Some code by Open-Smart Team and Catalex Team
//
// Arduino IDE: 1.8.1
// Board: Arduino UNO R3 or Arduino Mega2560

// ADAFRUIT DRIVERS
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
// Fictional A6 to release A4 to be used by MSGEQ7
#define LCD_RESET A6 // Can alternately just connect to 3.3V
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
uint16_t g_identifier = 0x9341;

// MSGEQ7 pins REMAPPED
#define PIN_STROBE 0
#define PIN_RESET 1
#define PIN_4 4 //analog input
#define PIN_5 5 //analog input
// band arrays
int left0[8]; 
int right0[8];
int left1[8]; 
int right1[8];

//#include <MCUFRIEND_kbv.h>
//MCUFRIEND_kbv tft;
//int width=400;
//int height=240;
int width=480;  // scales to 320
int height=320;
//uint16_t g_identifier;

//***********************************************//
// The control pins for the LCD can be assigned to any pins
// ADAFRUIT Pin arrangement:
// TFT Breakout  -- Arduino UNO / Mega2560 
// GND           -- GND
// 3V3           -- 3.3V
// CS            -- A3
// RS            -- A2
// WR            -- A1
// RD            -- A0
// RST           -- RESET
// LED           -- GND
// DB0-DB7       -- 8, 9, 2, 3, 4, 5, 6, 7

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
  digitalWrite(PIN_RESET, LOW);
  for(int band=0; band < 7; band++) {  //loop thru all 7 bands
    digitalWrite(PIN_STROBE,LOW);      // go to the next band 
    delayMicroseconds(30);             // gather data
    left0[band] = analogRead(PIN_4)/3;   // store band reading
    right0[band] = analogRead(PIN_5)/3;  // store band reading
    digitalWrite(PIN_STROBE,HIGH);     // reset the strobe pin
    }     // Second set of samples 200ms later
  for(int band=0; band < 7; band++) {  //loop thru all 7 bands
    digitalWrite(PIN_STROBE,LOW);      // go to the next band 
    delayMicroseconds(30);             // gather data
    left1[band] = analogRead(PIN_4)/3;   // store band reading
    right1[band] = analogRead(PIN_5)/3;  // store band reading
    digitalWrite(PIN_STROBE,HIGH);     // reset the strobe pin
    }
}

void setup(void) {
    pinMode(PIN_STROBE, OUTPUT);
    pinMode(PIN_RESET, OUTPUT);
 //   g_identifier = tft.readID(); //
 //   if (g_identifier == 0x00D3 || g_identifier == 0xD3D3) g_identifier = 0x9481; // write-only shield
 //   if (g_identifier == 0xFFFF) g_identifier = 0x9341; // serial
    tft.begin(g_identifier);
    tft.setRotation(1);
    tft.setCursor(0, 0);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    // Clear screen
    tft.fillRect(0, 0, width, height, BLACK);
}

void loop(void) {
    readMSGEQ7();
//  tft.println("DUAL MSGEQ7 ON A LCD SCREEN");
  int tred=height*2/3;
  int wstep=width/20;
  for (int b=0; b<8; b++){
    tft.fillRect(b*wstep, 0, 6, height, BLACK);
    tft.fillRect(b*wstep, height-left1[b], 6, height, GREEN);
    if (left1[b]>tred) {
      tft.fillRect(b*wstep, height-left1[b], 6, left1[b]-tred, RED);
    }
  } 
    for (int b=0; b<8; b++){
    tft.fillRect(b*wstep+wstep/2, 0, 6, height, BLACK);
    tft.fillRect(b*wstep+wstep/2, height-left0[b], 6, height, GREEN);
    if (left0[b]>tred) {
      tft.fillRect(b*wstep+wstep/2, height-left0[b], 6, left0[b]-tred, RED);
    }
  } 
  for (int b=0; b<8; b++){
    tft.fillRect(b*wstep+width/2, 0, 6, height, BLACK);
    tft.fillRect(b*wstep+width/2, height-right1[b], 6, height, GREEN);
    if (right1[b]>tred) {
      tft.fillRect(b*wstep+width/2, height-right1[b], 6, right1[b]-tred, RED);
    }
  }  
    for (int b=0; b<8; b++){
    tft.fillRect(b*wstep+width/2+wstep/2, 0, 6, height, BLACK);
    tft.fillRect(b*wstep+width/2+wstep/2, height-right0[b], 6, height, GREEN);
    if (right0[b]>tred) {
      tft.fillRect(b*wstep+width/2+wstep/2, height-right0[b], 6, right0[b]-tred, RED);
    }
  }  

  delay(100);
}


