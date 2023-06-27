#include <Servo.h>
 // Define our Servo

const int addressBits = 3;
const int numServos = 6;
const int OFF = 90;
const int ON = 60;
int number = 0;

Servo servos[numServos];
Servo test;
int* servoPins[numServos] = {A0,A1,A2,A3,A4,A5};
int* addrPins[addressBits] = {6,5,4};
int* muxAddrPins[addressBits] = {9,10,11};
int* muxAddr[8] = {4,6,7,5,3,0,1,2};
int ledData = 8;
int ledControl = 7;
int buttonData = 12;


int stateServos[numServos] = {0,0,0,0,0,0};
int newStateServos[numServos] = {0,0,0,0,0,0};
int state=0;
int stateMask=0;
int lastButton=0;

#define sep " "
#define INPUT_SIZE 100
char input[INPUT_SIZE + 1];
char code = '0';
char c_index = '0';
char c_number = '0';
int index = 0;


void setup() {
  
  for(int i=0; i<numServos; i++)
  {
    servos[i].attach(servoPins[i]);
    servos[i].write(ON);
  }
  
  for(int i=0; i<addressBits; i++)
  {
    pinMode(addrPins[i], OUTPUT);
    //pinMode(muxAddrPins[i], INPUT);
  }
  pinMode(ledData, OUTPUT);
  pinMode(ledControl, OUTPUT);
  pinMode(buttonData, INPUT);

  digitalWrite(ledControl,HIGH);
  Serial.begin(9600);
}


void writeAddress(int addr)
  {
  int mux = muxAddr[addr];
  int biti=1;
  for(int i=0; i<addressBits; i++)
    {
    writePin(addrPins[i],biti&addr);
    writePin(muxAddrPins[i],biti&mux);
    biti <<= 1;
    }
  }


void writePin(int pin, int cond)
{
    if (cond)
    {
      digitalWrite(pin,HIGH);
    }else
    {
      digitalWrite(pin, LOW);
    }
}


void moveMotor(int index, int cond)
{
    if (cond)
    {
      servos[index].write(ON);
    }else
    {
      servos[index].write(OFF);
    }
}


void loop()
{
   
    for (int i = 0; i <= numServos; i++)
    {
    
      if (digitalRead(buttonData) == HIGH)
      {
       moveMotor(i, 1);
      }
      else
      {
       moveMotor(i, 0);
      }
    }
}
