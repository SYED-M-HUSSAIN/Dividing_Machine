# include<AccelStepper.h>
AccelStepper stepper1(1,8,9);
AccelStepper stepper2(1,10,11);
int pos = 8000;
void setup(){
  stepper1.setMaxSpeed(500);
  stepper1.setAcceleration(500);
  stepper2.setMaxSpeed(500);
  stepper2.setAcceleration(500);
  
}
void loop(){
  if(stepper1.distanceToGo()==0){
    delay(500);
    pos=-pos;
    stepper1.moveTo(pos);
    
  }
  stepper1.run();
 
}