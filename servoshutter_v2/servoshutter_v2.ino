/*
  Arduino Servo_shutter v.2 sketch
  This version is a 2-setting adjustment for each servo.
  It does not activate the front buttons for use.

  Serial commands:
  "M#" move motor # to opposite position of current position.
  "G#" get current position of motor #.

  "G" returns:
  "0\n" is position OFF.
  "1\n" is position ON.
 
  KFS, KAM
*/

#include <Servo.h>
const int addressBits = 3;
const int numServos = 6;

const int OFF = 90;
const int ON = 60;

int currentSerial[numServos]={0,0,0,0,0,0};
// int currentSerialValue=0;

Servo servos[numServos];
Servo test;
int servoPins[numServos] = {A0,A1,A2,A3,A4,A5};
int addrPins[addressBits] = {6,5,4};
int muxAddrPins[addressBits] = {9,10,11};

//int* muxAddr[8] = {4,6,7,5,3,0,1,2};
int ledData = 8;
int ledControl = 7;
int buttonData = 12;

void setup()
{
  //servos = malloc(6*sizeof(Servo));
  for(int i=0; i<numServos; i++)
  {
    servos[i].attach(servoPins[i]);
    int ind = currentSerial[i];
    if (ind==0)
      servos[i].write(ON);
    else if (ind==-1)
      servos[i].write(OFF);  
  }
  for(int i=0; i<addressBits; i++)
  {
    pinMode(addrPins[i], OUTPUT);
    pinMode(muxAddrPins[i], INPUT);
  }
  pinMode(ledData, OUTPUT);
  pinMode(ledControl, OUTPUT);
  pinMode(buttonData, OUTPUT);
  delay(100);
  digitalWrite(ledControl,LOW);
  digitalWrite(buttonData, HIGH);
  digitalWrite(addrPins[0], LOW);
  digitalWrite(addrPins[1], LOW);
  digitalWrite(addrPins[2], LOW);
  Serial.setTimeout(200);
  Serial.begin(9600);
}


void loop()
{
  readSerial();
}

void readSerial()
{
  while (Serial.available()==0) {}
  
  String comm = Serial.readString();
  comm.trim();
  if(comm[0]=='M') 
   {
    char comms[1] = {comm[1]};
    int ind=atoi(comms);
    
    currentSerial[ind]= ~currentSerial[ind];
    if (currentSerial[ind]==0)
    servos[ind].write(ON);
    else 
    servos[ind].write(OFF);
   }
  if(comm[0]=='G') 
   {
    char comms[1] = {comm[1]};
    int ind=atoi(comms);
    int val=currentSerial[ind];
    if (val==0) {
     Serial.print('1');
     Serial.print('\n');
     }
    else if (val==-1) {
     Serial.print('0');
     Serial.print('\n');
     }
   }

} 
