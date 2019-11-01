// Program for sending MSGEQ7 to one 8x8 WS2812 string
// By Robert Davis II
// Uses Digital Pin 6 change for other pins. 
int LEDpin=6;
int MaxLed=64;
int DotBright=64; // sets your brightness
int led=8;  // Number of LED's per row
// MSGEQ7 stuff
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
    left[band] = analogRead(APIN0)/20;
    // Store right band reading   
    right[band] = analogRead(APIN1)/20;
    // Reset the strobe pin
    digitalWrite(PIN_STROBE,HIGH);     
    }     
}

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
  pinMode(PIN_STROBE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode (LEDpin, OUTPUT);
  }
  
void loop() {
  // Read Analog Inputs
  readMSGEQ7();
  cli();                        // No time for interruptions!
  for (int row=0; row<8; row++){  // Number of rows
    for (int l=0; l<led; l++){      // Number of LED's per row
      if (row==0){
        sendColor(0,0,0);
      }
      if (row==1){
        if (l<right[0]) sendColor(0, DotBright, 0); // green
        if (l==right[0]) sendColor(DotBright, 0, 0); // green
        if (l>right[0]) sendColor(0,0,0);
      }
      if (row==2){
        if (l<right[1]) sendColor(0, DotBright, 0); // green
        if (l==right[1]) sendColor(DotBright, 0, 0); // green
        if (l>right[1]) sendColor(0,0,0);
      }
      if (row==3){
        if (l<right[2]) sendColor(0, DotBright, 0); // green
        if (l==right[2]) sendColor(DotBright, 0, 0); // green
        if (l>right[2]) sendColor(0,0,0);
      }  
      if (row==4){
        if (l<right[3]) sendColor(0, DotBright, 0); // green
        if (l==right[3]) sendColor(DotBright, 0, 0); // green
        if (l>right[3]) sendColor(0,0,0);
      }
      if (row==5){
        if (l<right[4]) sendColor(0, DotBright, 0); // green
        if (l==right[4]) sendColor(DotBright, 0, 0); // green
        if (l>right[4]) sendColor(0,0,0);
      }
      if (row==6){
        if (l<right[5]) sendColor(0, DotBright, 0); // green
        if (l==right[5]) sendColor(DotBright, 0, 0); // green
        if (l>right[5]) sendColor(0,0,0);
      }
      if (row==7){
        if (l<right[6]) sendColor(0, DotBright, 0); // green
        if (l==right[6]) sendColor(DotBright, 0, 0); // green
        if (l>right[6]) sendColor(0,0,0);
      }
    }
  }
  sei();
  delay(200);  // Turn on display
}


