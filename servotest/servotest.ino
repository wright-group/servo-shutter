/*
  Arduino Servo Test sketch
*/
#include <Servo.h>
 // Define our Servo

const int addressBits = 3;
const int numServos = 6;
const int OFF = 90;
const int ON = 60;

Servo servos[numServos];
Servo test;
int* servoPins[numServos] = {A0,A1,A2,A3,A4,A5};
int* addrPins[addressBits] = {6,5,4};
int* muxAddrPins[addressBits] = {9,10,11};
int* muxAddr[8] = {4,6,7,5,3,0,1,2};
int ledData = 8;
int ledControl = 7;
int buttonData = 12;

int state=0x00;
int stateMask = 0x3f;
int lastButton=0x00;

void setup()
{
  //servos = malloc(6*sizeof(Servo));
  for(int i=0; i<numServos; i++)
  {
    servos[i].attach(servoPins[i]);
    servos[i].write(ON);
  }
  //test.attatch(A0);
  for(int i=0; i<addressBits; i++)
  {
    pinMode(addrPins[i], OUTPUT);
  }
  pinMode(ledData, OUTPUT);
  pinMode(ledControl, OUTPUT);
  pinMode(buttonData, INPUT);
  digitalWrite(ledControl,HIGH);
  Serial.begin(9600);
  Serial.write("Hi");
}

void loop()
{
  for (int i=0; i<numServos; i++)
  {
    
    int biti = 1<<i;
    writeAddress(i);
    /*if (digitalRead(buttonData) == HIGH)
    {
      if(!(lastButton&biti))
        state ^= biti;
      lastButton |= biti;
    }else
    {
      lastButton &= ~biti;
    }*/
    writePin(ledData, state & biti);
    moveMotor(i, state & biti);
    digitalWrite(ledControl,LOW);
    digitalWrite(ledControl,HIGH);
    //delay(1000);
  }
  writeAddress(numServos);
  if (digitalRead(buttonData) == HIGH)
  {
    state = stateMask;
  }
  writePin(ledData, state);
  digitalWrite(ledControl,LOW);
  digitalWrite(ledControl,HIGH);

  writeAddress(numServos+1);
  if (digitalRead(buttonData) == HIGH)
  {
    state = 0x00;
  }
  writePin(ledData, ~state & stateMask);
  //digitalWrite(ledControl,LOW);
  //digitalWrite(ledControl,HIGH);

  state++;
  //state=0;
  state &= stateMask;
  delay(10000);
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
      //test.write(ON);
      servos[index].write(ON);
    }else
    {
      //test.write(OFF);
      servos[index].write(OFF);
    }
    //delay(100);
}

void serialEvent()
{
  int set=0;
  int set2;
  set2 = Serial.parseInt();
  if(set2 == 1)
    state = Serial.parseInt();
  //if(set2>0)
    //set=set2%360;
  Serial.println(state);
  Serial.flush();
}
