// 64x32 Uno LED panel Analog
// Fast Clock Mod
// 3/7/2019 by Bob Davis

// #define A   A0  // Port D assignments
// #define B   A1
// #define C   A2
// #define D   A3
// #define E   A4
// #define CLK 8 // Port B assignments   
#define OE  9
// #define LAT 10
//#define PIN_4 4 //analog input
//#define PIN_5 5 //analog input

// MSGEQ7 pins REMAPPED
#define PIN_STROBE 11
#define PIN_RESET 12
#define PIN_4 4 //analog input
#define PIN_5 5 //analog input

//band arrays
int left0[7]; 
int right0[7];
//int col=0;

void readMSGEQ7() { //reset the chip
  digitalWrite(OE, HIGH); // Turn off display
  digitalWrite(PIN_RESET, HIGH);
  digitalWrite(PIN_RESET, LOW);
  for(int band=0; band < 7; band++) {  //loop thru all 7 bands
    digitalWrite(PIN_STROBE,LOW);      // go to the next band 
    delayMicroseconds(10); //was30             // gather data
    left0[band] = analogRead(PIN_4)-24;   // store band reading
    right0[band] = analogRead(PIN_5)-24;  // store band reading
    digitalWrite(PIN_STROBE,HIGH);     // reset the strobe pin
  }
  digitalWrite(OE, LOW);
}

int C12[16] = {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int C13[16] = {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0};

#define MaxLed 64
byte BGC1=0x00;  // Background
byte FGC1=0x1C;  // Foreground
byte BGC2=0x00;  // Background
byte FGC2=0xE0;  // Foreground

#define PIXEL_PORT PORTD  // Port the pixels are connected to
#define PIXEL_DDR  DDRD   // D2-D7
#define ROW_PORT   PORTC  // Port the rows are connected to
#define ROW_DDR    DDRC   // A0-A5
#define CLK_PORT   PORTB  // Port the Clock/LE/OE are connected to
#define CLK_DDR    DDRB   // D8-D10

void setup() {
  PIXEL_DDR = 0xFC;  // Set all pixel pins to output
  ROW_DDR = 0x0F;    // Set all row pins to output
  CLK_DDR = 0xFF;    // Set all CLK/LE/OE pins to output

  PORTB=0;
  // Send Data to control register 11
  for (int l=0; l<MaxLed; l++){
    int y=l%16;
    PORTD = 0x00;
    if (C12[y]==1) PORTD=0xFC;
      if (l>MaxLed-12){ PORTB=7; PORTB=6; }
      else{ PORTB=1; PORTB=0; }
    }
  PORTB=0;
  // Send Data to control register 12 
  for (int l=0; l<MaxLed; l++){
    int y=l%16;
    PORTD = 0x00;
    if (C13[y]==1) PORTD=0xFC;
      if (l>MaxLed-13){ PORTB=7; PORTB=6; }
      else{ PORTB=1; PORTB=0; }
    }
  PORTB=0;
}

void loop() {
    readMSGEQ7();
    // Select the Row
    for (int r=0; r<16; r++){
      for (int l=0; l<MaxLed; l++){
        int pd1 = BGC1; int pd2 = BGC2;
        FGC1=0x08; FGC2=0x40;
        if (r < 2){FGC1=0x04; FGC2=0x20; }
        if (l==1 or l==2 ) {
          if (16-r<left0[0]/8-16) pd1=FGC1;
          if (16-r<left0[0]/8) pd2=0x40;}
        if (l==5 or l==6 ) {
          if (16-r<left0[1]/8-16) pd1=FGC1;
          if (16-r<left0[1]/8) pd2=0x40;}
        if (l==9 or l==10 ) {
          if (16-r<left0[2]/8-16) pd1=FGC1;
          if (16-r<left0[2]/8) pd2=0x40;}
        if (l==13 or l==14) {
          if (16-r<left0[3]/8-16) pd1=FGC1;
          if (16-r<left0[3]/8) pd2=0x40;}
        if (l==17 or l==18) {
          if (16-r<left0[4]/8-16) pd1=FGC1;
          if (16-r<left0[4]/8) pd2=0x40;}
        if (l==21 or l==22) {
          if (16-r<left0[5]/8-16) pd1=FGC1;
          if (16-r<left0[5]/8) pd2=0x40;}
        if (l==25 or l==26) {
          if (16-r<left0[6]/8-16) pd1=FGC1;
          if (16-r<left0[6]/8) pd2=0x40;}

        if (l==33 or l==34) {
          if (16-r<right0[0]/8-16) pd1=FGC1;
          if (16-r<right0[0]/8) pd2=0x40;}
        if (l==37 or l==38) {
          if (16-r<right0[1]/8-16) pd1=FGC1;
          if (16-r<right0[1]/8) pd2=0x40;}
        if (l==41 or l==42) {
          if (16-r<right0[2]/8-16) pd1=FGC1;
          if (16-r<right0[2]/8) pd2=0x40;}
        if (l==45 or l==46) {
          if (16-r<right0[3]/8-16) pd1=FGC1;
          if (16-r<right0[3]/8) pd2=0x40;}
        if (l==49 or l==50) {
          if (16-r<right0[4]/8-16) pd1=FGC1;
          if (16-r<right0[4]/8) pd2=0x40;}
        if (l==53 or l==54) {
          if (16-r<right0[5]/8-16) pd1=FGC1;
          if (16-r<right0[5]/8) pd2=0x40;}
        if (l==57 or l==58) {
          if (16-r<right0[6]/8-16) pd1=FGC1;
          if (16-r<right0[6]/8) pd2=0x40;}
        PORTD=pd1+pd2;
        if (l>MaxLed-3){PORTB=7; PORTB=6;}
        else{ PORTB=1; PORTB=0; }
      }
      PORTC=r;  // Update row
      PORTB=0;  // Turn off latch, turn on display 
    }
}
