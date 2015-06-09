// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Define constants and variables
const int inputPin = A0;  // buttons array analog input 
uint16_t inputValue = 0;   // value read from buttons array
//
const int ledPin = 13; // the pin that the LED is attached to
int incomingByte;      // a variable to read incoming serial data into

// initialize internal variables
unsigned int l;             // current line number displayed on the first row
// Initialization
void setup() 
{
  //----------------
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  //--------------
  lcd.begin(16, 2);              // set up the LCD's number of columns and rows
  lcd.write("  Bienvenidos");  // Print a message on the LCD
  lcd.setCursor(0, 1);           // set the cursor to column 0, line 1
  lcd.write("Responde y Gana!");
}

int i = 0,x=0,cursore,pr=0;
// main loop
void loop() 
{
  // check buttons status------------------------------------------------
  inputValue = analogRead(inputPin);
  if(inputValue < 100 && inputValue >= 0) inputValue = 1;
  else if(inputValue < 250 && inputValue > 150) inputValue = 2;
  else if(inputValue < 470 && inputValue > 370) inputValue = 3;
  else if(inputValue < 670 && inputValue > 570) inputValue = 4;
  else if(inputValue < 870 && inputValue > 770) inputValue = 5;
  else if(inputValue <= 1023 && inputValue > 950) inputValue = 0;
  //---------------------------
  // Send answer
  if((inputValue == 1 || inputValue == 2 || inputValue == 3 || inputValue == 4 || inputValue == 5)&& pr>=0)
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    if (pr==0)
    lcd.print("Iniciando juego ");
    else
    lcd.print("Su respuesta:");
    lcd.print(inputValue);
    Serial.write(inputValue);
    delay(3000);
  }
 //-----------------------------------------------------------------
 //while (Serial.available() > 0) {
 if (Serial.available() > 0){ 
   if(x==0)
     lcd.clear();
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    //------
    if(incomingByte=='^'){
      i=0;
      cursore = 0;
    }
    if(incomingByte=='@'){
      cursore = 1;
      i=0;
    }
    if(incomingByte=='*'){
      x=0;
      pr++;
    }
    if(incomingByte=='$'){
      x=0;
      i=0;
      pr=0;
      
      
    }
    if(incomingByte=='#'){
      lcd.setCursor(0,0);
      lcd.write("opcion no valida");
      lcd.setCursor(0,1);
      lcd.write("intente de nuevo");
      delay(2000);
      
    }
    //--------------------------
    //lcd.setCursor(0, cursore);
    lcd.setCursor(i,cursore);
    if(incomingByte!='^' && incomingByte!='@' && incomingByte!='*' && incomingByte!='#' && incomingByte!='$'){
      if(cursore == 0){
        lcd.write(incomingByte);
        i++;
      }
      if(cursore == 1){
       lcd.write(incomingByte);
       i++; 
      }
      // print the number of seconds since reset:
      //lcd.println(message);
      x++;
    }
    
  }
}





