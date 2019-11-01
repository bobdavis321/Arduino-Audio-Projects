// OPEN SMART DUAL METER
// By Bob Davis
// Adafruit_TFTLCD LIBRARY MUST BE CONFIGURED.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h.
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
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// OPENSMART DRIVERS
//#include <MCUFRIEND_kbv.h>
//MCUFRIEND_kbv tft;
int width=480;  // scales to 320
int height=320;
uint16_t g_identifier;

int lnx0, lny0, lnx1, lny1;
int rnx0, rny0, rnx1, rny1;

//*********************************************//
// Pin assignments for the LCD 
// GND           -- GND
// 3V3           -- 3.3V
// CS            -- A3
// RS            -- A2
// WR            -- A1
// RD            -- A0
// RST           -- RESET
// LED           -- GND
// DB0-DB7       -- 8, 9, 10, 11, 4, 13, 6, 7

// Assign names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup(void) {
  uint16_t identifier = 0x9341;
  tft.reset();
  tft.begin(identifier);
  tft.setRotation(1);
  tft.setCursor(0, 0);
  tft.fillRect(0, 0, width, height, BLACK);
}

void loop(void) {
  int rval=analogRead(A4)/2.05;
  int lval=analogRead(A5)/2.05;
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(20,height/3.5);

  //Meter code Based on Sketch From Instructables by Bodmer    
  // Draw ticks every 5 degrees from -50 to +50
  for (int i = -50; i < 50; i += 5) {
    // Long scale length
    int tl = 15;
    int w2 = width/2;
    
    // Start Coodinates of section to draw
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (100 + tl) + width/4;
    uint16_t y0 = sy * (100 + tl) + height/2;
    uint16_t x1 = sx * 100 + width/4;
    uint16_t y1 = sy * 100 + height/2;
    
    // Stop Coordinates of section to fill
    float sx2 = cos((i + 5 - 90) * 0.0174532925);
    float sy2 = sin((i + 5 - 90) * 0.0174532925);
    int x2 = sx2 * (100 + tl) + width/4;
    int y2 = sy2 * (100 + tl) + height/2;
    int x3 = sx2 * 100 + width/4;
    int y3 = sy2 * 100 + height/2;

    // Green Section 
    if (i >= -50 && i < 25) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, GREEN);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, GREEN);
      tft.fillTriangle(x0+w2, y0, x1+w2, y1, x2+w2, y2, GREEN);
      tft.fillTriangle(x1+w2, y1, x2+w2, y2, x3+w2, y3, GREEN);
    } 
    // Yellow Section
    if (i >= 25 && i < 40) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, YELLOW);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, YELLOW);
      tft.fillTriangle(x0+w2, y0, x1+w2, y1, x2+w2, y2, YELLOW);
      tft.fillTriangle(x1+w2, y1, x2+w2, y2, x3+w2, y3, YELLOW);
    }
    // Red Section
    if (i >= 40 && i < 55) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, RED);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, RED);
      tft.fillTriangle(x0+w2, y0, x1+w2, y1, x2+w2, y2, RED);
      tft.fillTriangle(x1+w2, y1, x2+w2, y2, x3+w2, y3, RED);
    }
    
    // Short left scale tick length
    if (i % 25 != 0) tl = 8;
    // Calculate coords for short tick length
    x0 = sx * (100 + tl) + width/4;
    y0 = sy * (100 + tl) + height/2;
    x1 = sx * 100 + width/4;
    y1 = sy * 100 + height/2;
    // Draw tick
    tft.drawLine(x0, y0, x1, y1, BLACK);

    // Short right scale tick length
    if (i % 25 != 0) tl = 8;
    // Calculate coords for short tick length
    x0 = sx * (100 + tl) + width*.75;
    y0 = sy * (100 + tl) + height/2;
    x1 = sx * 100 + width*.75;
    y1 = sy * 100 + height/2;
    // Draw tick
    tft.drawLine(x0, y0, x1, y1, BLACK);

    // Draw needle
    if (i==40){
      tft.drawLine(lnx0, lny0, lnx1, lny1, BLACK);
      float nsx = cos((lval/5 - 140) * 0.0174532925);
      float nsy = sin((lval/5 - 140) * 0.0174532925);
      uint16_t nx0 = nsx * (100 + tl) + width/4;
      uint16_t ny0 = nsy * (100 + tl) + height/2;
      uint16_t nx1 = nsx * 100 + width/4;
      uint16_t ny1 = nsy * 100 + height/2;
      tl=20;  // line length
      lnx0 = nsx * (1 + tl) + width/4;
      lny0 = nsy * (1 + tl) + height/2;
      lnx1 = nsx * 100 + width/4;
      lny1 = nsy * 100 + height/2;
      tft.drawLine(lnx0, lny0, lnx1, lny1, WHITE);
    // Right Needle
      tft.drawLine(rnx0+w2, rny0, rnx1+w2, rny1, BLACK);
      nsx = cos((rval/5 - 140) * 0.0174532925);
      nsy = sin((rval/5 - 140) * 0.0174532925);
      nx0 = nsx * (100 + tl) + width/4;
      ny0 = nsy * (100 + tl) + height/2;
      nx1 = nsx * 100 + width/4;
      ny1 = nsy * 100 + height/2;
      rnx0 = nsx * (1 + tl) + width/4;
      rny0 = nsy * (1 + tl) + height/2;
      rnx1 = nsx * 100 + width/4;
      rny1 = nsy * 100 + height/2;
      tft.drawLine(rnx0+w2, rny0, rnx1+w2, rny1, WHITE);
    }
  }
    // Optional Text display of results
    tft.fillRect(0, height-40, width, 40, WHITE);
    tft.setTextColor(RED);
    tft.setCursor(10, height-30);
    tft.println(lval);
    tft.setCursor(width/2, height-30);
    tft.println(rval);
    delay(300);
}


