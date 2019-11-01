// BOB Davis Version for sending data to 14 Parallel WS2812 strings
// Removed Assembler and simplified the code
// Changed to VU meter with dual MSGEQ7's

// PORTD is Digital Pins 0-7 (Uses D0-D7=First 8 lines) 
// POPRB is Digital Pins 8-13 (Uses D8-D13= Next 6 lines)
#define PIXEL_PORT   PORTD  // Port the pixels are connected to
#define PIXEL_DDR    DDRD   // Port the pixels are connected to
#define PIXEL_PORTB  PORTB  // Port the pixels are connected to
#define PIXEL_DDRB   DDRB   // Port the pixels are connected to

// MSGEQ7 pins uses 4 analog pins
#define PIN_STROBE A0
#define PIN_RESET A1
#define PIN_LEFT 4 //analog input
#define PIN_RIGHT 5 //analog input

int textb=128;  // brightness of text
int maxled=64; // Maximum number of LED's
//band arrays
int left[7]; int right[7];
int col=0;
// Set default colors
int red=textb; int green=textb; int blue=textb;

void readMSGEQ7() { //reset the chip
  digitalWrite(PIN_RESET, HIGH);
  digitalWrite(PIN_RESET, LOW);
  for(int band=0; band < 7; band++) {  //loop thru all 7 bands
    digitalWrite(PIN_STROBE,LOW);      // go to the next band 
    delayMicroseconds(30);             // gather data
    left[band] = analogRead(PIN_LEFT); // store left band reading
    right[band] = analogRead(PIN_RIGHT); // store right band reading
    digitalWrite(PIN_STROBE,HIGH);     // reset the strobe pin
  }
}

// Actually send the WS2812B encoded bits to the 14 pins.
// The delay timing is for an Arduino UNO.
void sendBitX8( byte bits, byte bith ) {
  PORTD= 0xFF;  // turn on
  PORTB= 0xFF;  // turn on
  PORTD= 0xFF;  // delay
  PORTD= 0xFF;  // delay
  PORTD= 0xFF;  // delay (add more for faster processors)
  PORTD= bits;  // send data
  PORTB= bith;  // send data
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= 0x00;  // Turn off;
  PORTB= 0x00;  // Turn off;
}

void sendPixelRow( word row ) {
  // separate out upper and lower bytes from word
  byte rowh = row >> 8;
  // Send the bit 8 times down every row, each pixel is 8 bits/color
  int mask = 0x01;  // shifting mask to determine bit status
    for (int bit=8; bit>0; bit--){       
      if (green & (mask<<bit))sendBitX8( row, rowh ); else sendBitX8( 0x0000, 0x0000 ); }
    for (int bit=8; bit>0; bit--){       
      if (red & (mask<<bit))sendBitX8( row, rowh ); else sendBitX8( 0x0000, 0x0000 ); }
    for (int bit=8; bit>0; bit--){       
      if (blue & (mask<<bit))sendBitX8( row, rowh ); else sendBitX8( 0x0000, 0x0000 ); }
 }

void setup() {
  PIXEL_DDR = 0xFF;    // Set all row pins to output
  PIXEL_DDRB = 0xFF;     // Set pins to output 
  pinMode(PIN_RESET, OUTPUT); // reset
  pinMode(PIN_STROBE, OUTPUT); // strobe
}
void loop() {
  red=0; green=textb; blue=0;
  readMSGEQ7();               // collect samples
  cli();                      // No time for interruptions!
    for (int b=1; b<maxled; b++){ //maxled is number of bytes to send
      if (b >maxled*.75) {red=textb; green=0;}
      else {red=0; green=textb;}
      col=0;
      if (left[0]-64 >= b) col=col+0x0001;  // Set Bits
      if (left[1]-64 >= b) col=col+0x0002;  // Set Bits
      if (left[2]-64 >= b) col=col+0x0004;  // Set Bits
      if (left[3]-64 >= b) col=col+0x0008;  // Set Bits
      if (left[4]-64 >= b) col=col+0x0010;  // Set Bits
      if (left[5]-64 >= b) col=col+0x0020;  // Set Bits
      if (left[6]-64 >= b) col=col+0x0040;  // Set Bits
      if (right[0]-64 >= b) col=col+0x0080;  // Set Bits
      if (right[1]-64 >= b) col=col+0x0100;  // Set Bits
      if (right[2]-64 >= b) col=col+0x0200;  // Set Bits
      if (right[3]-64 >= b) col=col+0x0400;  // Set Bits
      if (right[4]-64 >= b) col=col+0x0800;  // Set Bits
      if (right[5]-64 >= b) col=col+0x1000;  // Set Bits
      if (right[6]-64 >= b) col=col+0x2000;  // Set Bits      
      sendPixelRow(col);
      } 
    sei();                  // interrupts back on
    delay (50);
}

