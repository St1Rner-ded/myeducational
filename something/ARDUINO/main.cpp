#include <Arduino.h>

const int segPin[]={2,3,4,5,6,7,8,9}; //A,B,C,D,E,F,G,DP
const int digPin[]={A5,A4,A3,A2}; //Разряды слевва направо

const byte digs[10]={
  0b11111100, //0
  0b01100000, //1.
  0b11011010, //2
  0b11110010, //3.
  0b01100110, //4
  0b10110110, //5.
  0b10111110, //6
  0b11100000, //7.
  0b11111110, //8
  0b11110110  //9.
};

void displayNum(int dig1, int dig2, int dig3, int dig4) {
 int digits[4]={dig1,dig2,dig3,dig4};
 long total = dig1*1000+dig2*100+dig3*10+dig4;

 int aDigs=1;
 if (total>=10) aDigs=2;
 if (total>=100) aDigs=3;
 if (total>=1000) aDigs=4;
 
  for (int i=0; i<aDigs; i++) {
    int digInd = 3-i;

    for (int i=0; i<4; i++) {digitalWrite(digPin[i], HIGH);}

    int curDigV=digits[digInd];

    for (int seg=0; seg<8; seg++) {
      bool bitValue = bitRead(digs[curDigV],7-seg);
      digitalWrite(segPin[seg], bitValue ? HIGH:LOW);
    }
    digitalWrite(digPin[digInd],LOW);
    delay(5);
  }
}

void setup() {
  for (int i=0; i<8; i++) pinMode(segPin[i], OUTPUT);
  for (int i=0; i<4; i++) pinMode(digPin[i], OUTPUT);
}

void loop() {
long secs=millis()/1000;
secs%=10000;
int sec1 = (secs /1000)%10;
int sec2 = (secs /100)%10;
int sec3 = (secs /10)%10;
int sec4 = secs%10;
displayNum(sec1,sec2,sec3,sec4);
}