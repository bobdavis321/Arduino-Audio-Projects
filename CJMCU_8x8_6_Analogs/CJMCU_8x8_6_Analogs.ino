// Program for sending 6 Analogs to one WS2812 string 8x8
// By Robert Davis II
// Uses Digital Pin 6 change for other pins. 
int LEDpin=6;
int MaxLed=64;
int DotBright=64; // sets your brightness
int led=8;  // Number of LED's per row

// The delay timing is for an Arduino UNO.
// Sorry digitalWrite is too slow to use.
void sendBit( uint8_t bits ) {
  PORTD= 0xF0;  // turn on
  PORTD= 0xF0;  // delay
  PORTD= 0xF0;  // delay
  PORTD= 0xF0;  // delay
  PORTD= 0xF0;  // delay (Add more for faster processors)
  PORTD= bits;  // send data
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= 0x00;  // Turn off;
}

void sendColor( int red, int green, int blue ) {
 // Send the bit 8 times down the row, each pixel is 8 bits each for R,G,B
  int mask = 0x01;  // shifting mask to determine bit status
    for (int bit=8; bit>0; bit--){       
      if (green & (mask<<bit))sendBit( 0xF0 ); else sendBit( 0x00 ); }
    for (int bit=8; bit>0; bit--){       
       if (red & (mask<<bit))sendBit( 0xF0 ); else sendBit( 0x00 ); }
    for (int bit=8; bit>0; bit--){       
       if (blue & (mask<<bit))sendBit( 0xF0 ); else sendBit( 0x00 ); }
 }
 
void setup() {
  pinMode (LEDpin, OUTPUT);
  }
  
void loop() {
  // Read Analog Inputs
  int analog0 = analogRead(A0)/20.5;
  int analog1 = analogRead(A1)/20.5;
  int analog2 = analogRead(A2)/20.5;
  int analog3 = analogRead(A3)/20.5;
  int analog4 = analogRead(A4)/20.5;
  int analog5 = analogRead(A5)/20.5;
  cli();                        // No time for interruptions!
  for (int row=0; row<8; row++){  // Number of rows
    for (int l=0; l<led; l++){      // Number of LED's per row
      if (row==0){
        sendColor(0,0,0);
      }
      if (row==1){
        if (l<analog0) sendColor(0, DotBright, 0); // green
        if (l==analog0) sendColor(DotBright, 0, 0); // green
        if (l>analog0) sendColor(0,0,0);
      }
      if (row==2){
        if (l<analog1) sendColor(0, DotBright, 0); // green
        if (l==analog1) sendColor(DotBright, 0, 0); // green
        if (l>analog1) sendColor(0,0,0);
      }
      if (row==3){
        if (l<analog2) sendColor(0, DotBright, 0); // green
        if (l==analog2) sendColor(DotBright, 0, 0); // green
        if (l>analog2) sendColor(0,0,0);
      }  
      if (row==4){
        if (l<analog3) sendColor(0, DotBright, 0); // green
        if (l==analog3) sendColor(DotBright, 0, 0); // green
        if (l>analog3) sendColor(0,0,0);
      }
      if (row==5){
        if (l<analog4) sendColor(0, DotBright, 0); // green
        if (l==analog4) sendColor(DotBright, 0, 0); // green
        if (l>analog4) sendColor(0,0,0);
      }
      if (row==6){
        if (l<analog5) sendColor(0, DotBright, 0); // green
        if (l==analog5) sendColor(DotBright, 0, 0); // green
        if (l>analog5) sendColor(0,0,0);
      }
      if (row==7){
        sendColor(0,0,0);
      }
    }
  }
  sei();
  delay(1000);  // Turn on display
}


