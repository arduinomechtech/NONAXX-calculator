int num1; // First input number
int num2; // Second input number
int bin1[4]; // Binary representation of num1
int bin2[4]; // Binary representation of num2
int res[4]; // Resultant binary array after bitwise operation
int pin1[4]={2,4,6,8}; // Output pins for first number (num1)
int pin2[4]={3,5,7,9}; // Output pins for second number (num2)
int pin3[4]={10,11,12,13}; // Output pins for result
String ops; // String to hold the chosen bitwise operation

// Converts a decimal number to 4-bit binary and stores in bin[]
void convbin(int num,int bin[]){
  for(int i=3;i>=0;i--){
    bin[i]=num%2;
    num/=2;
  }
}

// Performs bitwise OR operation between bin1 and bin2 and stores result in res[]
void bit_OR(int bin1[],int bin2[], int res[]){
  int j;
  for(int i=0;i<4;i++){
    if((bin1[i]==0 && bin2[i]==0)){j=0;}
    else{j=1;}
    res[i]=j;    
  }
}

// Performs bitwise AND operation between bin1 and bin2 and stores result in res[]
void bit_AND(int bin1[],int bin2[], int res[]){
  int j;
  for(int i=0;i<4;i++){
    if(bin1[i]==1 && bin2[i]==1){j=1;}
    else{j=0;}
    res[i]=j;
  }
}

// Performs bitwise NOT operation on bin1 and stores result in res[]
void bit_NOT(int bin1[], int res[]){
  int j;
  for(int i=0;i<4;i++){
    if(bin1[i]==1){j=0;}
    else{j=1;}
    res[i]=j;
  }
}

// Performs bitwise NOR operation: OR followed by NOT
void bit_NOR(int bin1[],int bin2[], int res[]){
  bit_OR(bin1,bin2,res);
  bit_NOT(res,res);
}

// Performs bitwise NAND operation: AND followed by NOT
void bit_NAND(int bin1[],int bin2[], int res[]){
  bit_AND(bin1,bin2,res);
  bit_NOT(res, res);
}

// Performs bitwise XOR operation using OR, NAND and AND
void bit_XOR(int bin1[],int bin2[], int res[]){
  int res1[4];
  bit_OR(bin1,bin2,res1);
  int res2[4];
  bit_NAND(bin1,bin2,res2);
  bit_AND(res1,res2,res);
}

// Performs bitwise XNOR operation: XOR followed by NOT
void bit_XNOR(int bin1[],int bin2[], int res[]){
  bit_XOR(bin1,bin2,res);
  bit_NOT(res,res);
} 

// Sets digital output pins based on binary array
void lightpin(int pin[],int bin[]){
  for(int i=0;i<4;i++){
    digitalWrite(pin[i],bin[3-i]); // going from left to right
  }
}

// Turns off all LEDs on all pin groups
void clearPins() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pin1[i],0);
    digitalWrite(pin2[i],0);
    digitalWrite(pin3[i],0);
  }
}

// Setup function runs once at the beginning
void setup(){
 for(int i=0;i<4;i++){
  pinMode(pin1[i],OUTPUT);
  pinMode(pin2[i],OUTPUT);
  pinMode(pin3[i],OUTPUT);
 } 
 Serial.begin(9600); // Start serial communication
 } 

// Main loop function runs repeatedly
void loop(){
  Serial.println("write number");
  while(Serial.available()==0){} // Wait for user input
  num1=Serial.parseInt(); // Read first number
  while(Serial.available()){Serial.read();} // Clear input buffer
  convbin(num1,bin1); // Convert to binary
  lightpin(pin1,bin1); // Show binary on pin1 LEDs

  Serial.println("write number");
  while(Serial.available()==0){} // Wait for second input
  num2=Serial.parseInt(); // Read second number
  while(Serial.available()){Serial.read();} // Clear input buffer
  convbin(num2,bin2); // Convert to binary
  lightpin(pin2,bin2); // Show binary on pin2 LEDs

  Serial.println("Write the operation out of \n AND \n OR \n NAND \n NOR \n XOR \n XNOR");
  while(Serial.available()==0){} // Wait for operation input
  ops = Serial.readStringUntil('\n'); // Read operation
  ops.trim();         // Remove trailing newline or spaces
  ops.toUpperCase();  // Convert to uppercase to simplify comparison

  // Perform selected bitwise operation
  if(ops=="AND"){bit_AND(bin1,bin2,res);}
  else if(ops=="OR"){bit_OR(bin1,bin2,res);}
  else if(ops=="NAND"){bit_NAND(bin1,bin2,res);}
  else if(ops=="NOR"){bit_NOR(bin1,bin2,res);}
  else if(ops=="XOR"){bit_XOR(bin1,bin2,res);}
  else if(ops=="XNOR"){bit_XNOR(bin1,bin2,res);}
  else{Serial.println("invalid input");} // If operation not recognized

  lightpin(pin3,res); // Show result on pin3 LEDs

  Serial.println("Press ENTER to continue...");
  while (Serial.available() == 0) {} // Wait for user to press Enter
  while (Serial.available()) { Serial.read();clearPins(); } // Clear inputs and turn off LEDs

;}
