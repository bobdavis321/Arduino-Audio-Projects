//******************************************//
//  Name    : Breadboard 7x10 MSGEQ7        //
//  Author  : Bob Davis                     //
//  Date    : 10 Oct, 2019                  //
//******************************************//
// Pins for the row drivers
int colPin1 = 1;
int colPin2 = 2;
int colPin3 = 3;
int colPin4 = 4;
int colPin5 = 5;
int colPin6 = 6;
int colPin7 = 7;

// Without 74LS138
int rdataPin1 = 8;
int rdataPin2 = 9;
int rdataPin3 = 10;
int rdataPin4 = 11;
int rdataPin5 = 12;
int rdataPin6 = 13;
int rdataPin7 = 14;
int rdataPin8 = 15;

// store MSGEQ7 values here
int left[7]; 
int right[7];
#define PIN_STROBE 16 // Analog 2
#define PIN_RESET 17  // Analog 3
#define APIN0 4 //analog input
#define APIN1 5 //analog input

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

// Set the pins to output to the sign
void setup() {
  pinMode(PIN_STROBE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);

  pinMode(colPin1, OUTPUT);
  pinMode(colPin2, OUTPUT);
  pinMode(colPin3, OUTPUT);
  pinMode(colPin4, OUTPUT);
  pinMode(colPin5, OUTPUT);
  pinMode(colPin6, OUTPUT);
  pinMode(colPin7, OUTPUT);

  pinMode(rdataPin1, OUTPUT);
  pinMode(rdataPin2, OUTPUT);
  pinMode(rdataPin3, OUTPUT);
  pinMode(rdataPin4, OUTPUT);
  pinMode(rdataPin5, OUTPUT);
  pinMode(rdataPin6, OUTPUT);
  pinMode(rdataPin7, OUTPUT);
  pinMode(rdataPin8, OUTPUT);
}

void loop(){
  // select the row 
  readMSGEQ7();
  for (int row = 0; row < 7; row++)  {
    // Turn Display off
    digitalWrite (colPin1, LOW);
    digitalWrite (colPin2, LOW);
    digitalWrite (colPin3, LOW);
    digitalWrite (colPin4, LOW);
    digitalWrite (colPin5, LOW);
    digitalWrite (colPin6, LOW);
    digitalWrite (colPin7, LOW);
    
    digitalWrite(rdataPin1, HIGH);
    digitalWrite(rdataPin2, HIGH);
    digitalWrite(rdataPin3, HIGH);
    digitalWrite(rdataPin4, HIGH);
    digitalWrite(rdataPin5, HIGH);
    digitalWrite(rdataPin6, HIGH);
    digitalWrite(rdataPin7, HIGH);
    digitalWrite(rdataPin8, HIGH);
    
    // Display the data results LOW = "on"
    if (right[row]>1 ) digitalWrite(rdataPin1, LOW); 
    if (right[row]>2 ) digitalWrite(rdataPin2, LOW); 
    if (right[row]>3 ) digitalWrite(rdataPin3, LOW); 
    if (right[row]>4 ) digitalWrite(rdataPin4, LOW); 
    if (right[row]>5 ) digitalWrite(rdataPin5, LOW); 
    if (right[row]>6 ) digitalWrite(rdataPin6, LOW);  
    if (right[row]>7 ) digitalWrite(rdataPin7, LOW);  
    if (right[row]>8 ) digitalWrite(rdataPin8, LOW);  

    // Select row to turn on HIGH = "on"
    if (row==0) digitalWrite (colPin1, HIGH);  
    if (row==1) digitalWrite (colPin2, HIGH);
    if (row==2) digitalWrite (colPin3, HIGH);  
    if (row==3) digitalWrite (colPin4, HIGH);
    if (row==4) digitalWrite (colPin5, HIGH);
    if (row==5) digitalWrite (colPin6, HIGH);
    if (row==6) digitalWrite (colPin7, HIGH);

    // Wait to see what we sent to the display ;
    delay(1); 
  }
}   

