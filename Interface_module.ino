#include <Keypad.h>
#include <Wire.h>
 
#include <LiquidCrystal_I2C.h>
#define STEPPIN 11
#define DIRPIN 10
#define ENAPIN 9

const int STEPTIME = 5;

LiquidCrystal_I2C lcd(0x27,20,4);  

const uint8_t ROWS = 4;
const uint8_t COLS = 3;
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6'},
  { '7', '8', '9' },
  { '*', '0', '#'}
};




uint8_t colPins[COLS] = { 45, 47, 49 }; // Pins connected to C1, C2, C3, C4
uint8_t rowPins[ROWS] = { 42, 44, 46, 48 }; // Pins connected to R1, R2, R3, R4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  // put your setup code here, to run once:
  pinMode(STEPPIN,OUTPUT);
  pinMode(DIRPIN,OUTPUT);
  pinMode(ENAPIN,OUTPUT);
  
  
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  char key = keypad.getKey();
  int col = 20;
  int row =4;

  
  if (key == '1'){
    forward(400);
    lcd.setCursor(0,0);
    lcd.print(key);
    Serial.println("FORWARD");
    
  }
  else if (key == '2'){
    backward(400);
    lcd.setCursor(0,0);
    lcd.print(key);
    
     Serial.println("BACKWARD");
  }
  
}
void forward(int steps){
  int i;
  digitalWrite(ENAPIN,LOW);//ENABLE IS ACTIVE LOW
  digitalWrite(DIRPIN,HIGH);//SET DIRECTION
   
  for(i=0;i<steps;i++){
    
     Serial.println("FORWARD MOVING");
    digitalWrite(STEPPIN,HIGH);
    delay(STEPTIME);
    digitalWrite(STEPPIN,LOW);
    delay(STEPTIME);
  }
  digitalWrite(ENAPIN,HIGH);//DISABLE STEPPER
}
void backward(int steps){
  int i;
  digitalWrite(ENAPIN,LOW);//ENABLE IS ACTIVE LOW
  digitalWrite(DIRPIN,LOW);//SET DIRECTION 
  for(i=0;i<steps;i++){
    Serial.println("BACKWARD MOVING");
    digitalWrite(STEPPIN,HIGH);
    delay(STEPTIME);
    digitalWrite(STEPPIN,LOW);
    delay(STEPTIME);
  }
  digitalWrite(ENAPIN,HIGH);//DISABLE STEPPER
}
