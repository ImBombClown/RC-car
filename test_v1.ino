// C++ code
//ver 2
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

const byte e1 = 3;
const byte i1 = 4;
const byte i2 = 5;
const byte e2 = 9;
const byte i3 = 10;
const byte i4 = 11;
const byte rx_pin = 6;
const byte tx_pin = 7;
unsigned long lastSpeedChange = 0UL;
int speed = 255;
char new_value = 'n';
char old_value = ' ';

void stop(){
  analogWrite(e1, 0);
  analogWrite (e2, 0);
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite (i3, LOW);
  digitalWrite (i4, LOW);
}

void move(byte in1, byte in2, byte in3, byte in4){
  analogWrite(e1, speed);
  analogWrite(e2,speed);
  digitalWrite(i1, in1);
  digitalWrite(i2, in2);
  digitalWrite(i3, in3);
  digitalWrite(i4, in4);}


void setup()
{
   pinMode (e1, OUTPUT);
   pinMode (e2, OUTPUT);
   pinMode (i1, OUTPUT);
   pinMode (i2, OUTPUT);
   pinMode (i3, OUTPUT);
   pinMode (i4, OUTPUT);
  Dabble.begin(9600, rx_pin, tx_pin);
  
}

void loop()
{ 
  Dabble.processInput();
  if (!Dabble.isAppConnected()){
    stop();
  return;}
  
  bool is_speed = false;
  if (millis() - lastSpeedChange > 50){
  if(GamePad.isTrianglePressed()&&speed<=250){
    speed+=5;
    is_speed = true;
  }
  else if(GamePad.isCrossPressed()&&speed>=5){
    speed-=5;
    is_speed = true;}
    lastSpeedChange = millis();
  }
  if (GamePad.isUpPressed()){
	new_value = 'u';
  }
  else if (GamePad.isDownPressed()){
    new_value = 'd';
  }
  else if (GamePad.isLeftPressed()){
    new_value = 'l';
  }
  else if (GamePad.isRightPressed()){
    new_value = 'r';
  }
  else new_value = 's';
  
  if (new_value != old_value || is_speed == true){
    switch (new_value){
    case 'l': move(HIGH, LOW, HIGH, LOW); break;
    case 'r': move (LOW, HIGH, LOW, HIGH); break;
    case 'd': move (LOW, HIGH, HIGH, LOW); break;
    case 'u': move (HIGH, LOW, LOW, HIGH); break;
    case 's': analogWrite(e1,0); analogWrite(e2,0); break;}
  }
  old_value = new_value;
}
 
