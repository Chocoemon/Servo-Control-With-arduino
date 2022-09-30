#include <MsTimer2.h>

#define SERVO 2
#define PWM_RANGE_MIN 544 // 0 degree
#define PWM_RANGE_MAX 2400 // 180 degree 

String strAngle; //Angle entered by serial communication
bool flag = false; //Enable when data is entered by serial communications
int dutyHIGH = 1500; // PWM HIGH Duration 
void setup(){
  pinMode(2,OUTPUT);
  MsTimer2::set(20,setServo);
  MsTimer2::start();
  Serial.begin(115200);
  Serial.print("Input Angle 0 ~ 180 : ");
}

void loop(){
  if(flag==1){ // Run when serial data is received       
    flag = 0;
    int temp  = strAngle.toInt();
    strAngle ="";
    if((temp  >=  0) && (temp <= 180))
      dutyHIGH = map(temp, 0,180, PWM_RANGE_MIN, PWM_RANGE_MAX);
    
    else // for error handling S
      Serial.println("Please Input Reand 0 ~ 180..!");
      
    Serial.print("Input Angle 0 ~ 180 : ");
  }
  
}

void setServo(){
  digitalWrite(SERVO,HIGH);
  delayMicroseconds(dutyHIGH);
  digitalWrite(SERVO, LOW);
}

void serialEvent()
{
  char myChar = (char)Serial.read();
  if((myChar >= '0') && (myChar <='9')){// for error handling        
    strAngle += myChar; 
  }
    
  else if(myChar == '\n'){flag = true;}
}
