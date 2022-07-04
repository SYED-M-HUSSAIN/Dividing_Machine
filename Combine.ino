#include <Keypad.h>
#include <Wire.h>
 
#include <LiquidCrystal_I2C.h>
#define STEPPIN 11
#define DIRPIN 10
#define ENAPIN 9
# include<AccelStepper.h>
AccelStepper stepper1(1,6,7);
AccelStepper stepper2(1,2,3);
int pos = 200;


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
  // transmitter
  pinMode(24,INPUT);
  // Reciever
  pinMode(26,INPUT);
  pinMode(13,OUTPUT);
  pinMode(STEPPIN,OUTPUT);
  pinMode(DIRPIN,OUTPUT);
  pinMode(ENAPIN,OUTPUT);
  // Stepper Motor 
  stepper1.setMaxSpeed(900);
  stepper1.setAcceleration(900);
  stepper2.setMaxSpeed(700);
  stepper2.setAcceleration(700);
  
  
  
  
}

void loop() {
  // keyboard
  char key = keypad.getKey();
  int col = 20;
  int row =4;
  // put your main code here, to run repeatedly:
  int cond = digitalRead(24);
  int static game =0;
  bool static val = false;
  
 
  int someInt = key - '0';
  if(someInt == -48){
    someInt =0;
  }
  else if (someInt == 0){
    Serial.print("KEY SET = ");
    Serial.println(someInt);
    while(true){
    if(stepper1.distanceToGo()==0){
    pos=-pos;
    stepper1.moveTo(pos);
    break;
    
  }
    stepper1.run();
     
    }}
  else if (someInt == -13){
    Serial.print("KEY SET = ");
    Serial.println(someInt);
    while(true){
    if(stepper2.distanceToGo()==0){
    pos=-pos;
    stepper2.moveTo(pos);
    break;
    
  }
    stepper2.run();
     
    }}
  else{
     Serial.print("KEY SET = ");
     Serial.println(someInt);
  
 
  
  
  while(true){
    int cond = digitalRead(24);
  
  if (cond ==1){
    if (val==true){ game+=1;
    val = false;} 
    digitalWrite(13,HIGH);
  forward(1);
  Serial.println("OBSTACLE");
  
  
  
  }
  else {
    val = true;
    digitalWrite(13,LOW);
    Serial.println("CLEAR");
    Serial.println(game);
    delay(500);
    if ((game)== someInt){
    game=0;
    Serial.println("FINISHED");
    break;}
    forward(100);
    }}}
  
    
 
  
}
void forward(int steps){
  int i;
  digitalWrite(ENAPIN,LOW);//ENABLE IS ACTIVE LOW
  digitalWrite(DIRPIN,HIGH);//SET DIRECTION
   
  for(i=0;i<steps;i++){
    
    
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
   
    digitalWrite(STEPPIN,HIGH);
    delay(STEPTIME);
    digitalWrite(STEPPIN,LOW);
    delay(STEPTIME);
  }
  digitalWrite(ENAPIN,HIGH);//DISABLE STEPPER
}
