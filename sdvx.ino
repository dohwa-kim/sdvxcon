#define DELAY            5  // Delay per loop in ms
#define KSM_mode 1
#define SDVX_mode 0
#include <Keyboard.h>
#include <Mouse.h>
 
 enum PinAssignments
 {
  encoderPinA = 0,
  encoderPinB = 1,
  encoderPinC = 3,
  encoderPinD = 2,

 };
//This is up to your pin wiring
 
 int encoderPos[] = {0,0};
 static boolean rotating[] = {false,false};
 
 boolean start_set = false;
 boolean A_set = false;              
 boolean B_set = false;
 boolean C_set = false;              
 boolean D_set = false;
 boolean fxL_set = false;
 boolean fxR_set = false;

int modechange = 0;  //모드 변환용 변수
 
void setup()
{
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(5, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  Keyboard.begin();

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderPinC, INPUT_PULLUP);
  pinMode(encoderPinD, INPUT_PULLUP);
 
  attachInterrupt(0, doEncoderC, CHANGE);
  attachInterrupt(1, doEncoderD, CHANGE);
 
  attachInterrupt(2, doEncoderA, CHANGE);
  attachInterrupt(3, doEncoderB, CHANGE);
  
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
 
  Serial.begin(9600);
}

void loop() {
 
  if(digitalRead(5)==LOW){
     if(start_set == false) {
      Keyboard.press('a');
      start_set = true;
      digitalWrite(12, LOW);
    }
  } else {
    if(start_set == true) {
      Keyboard.release('a');
      start_set = false;
      digitalWrite(12, HIGH);
    }
  }
  if(digitalRead(A0)==LOW){
     if(A_set == false) {
      Keyboard.press('b');
      A_set = true;
      digitalWrite(6, LOW);
    }
  } else {
    if(A_set == true) {
      Keyboard.release('b');
      A_set = false;
      digitalWrite(6, HIGH);
    }
  }
    if(digitalRead(A1)==LOW){
     if(B_set == false) {
      Keyboard.press('c');
      B_set = true;
      digitalWrite(7, LOW);
    }
  } else {
    if(B_set == true) {
      Keyboard.release('c');
      B_set = false;
      digitalWrite(7, HIGH);
    }
  }
  if(digitalRead(A2)==LOW){
     if(C_set == false) {
      Keyboard.press('d');
      C_set = true;
      digitalWrite(8, LOW);
    }
  } else {
    if(C_set == true) {
      Keyboard.release('d');
      C_set = false;
      digitalWrite(8, HIGH);
    }
  }
  if(digitalRead(A3)==LOW){
     if(D_set == false) {
      Keyboard.press('i');
      D_set = true;
      digitalWrite(9, LOW);
    }
  } else {
    if(D_set == true) {
      Keyboard.release('i');
      D_set = false;
      digitalWrite(9, HIGH);
    }
  }
 if(digitalRead(A4)==LOW){
     if(fxL_set == false) {
      Keyboard.press('f');
      fxL_set = true;
      digitalWrite(10, LOW);
    }
  } else {
    if(fxL_set == true) {
      Keyboard.release('f');
      fxL_set = false;
      digitalWrite(10, HIGH);
    }
  }
   if(digitalRead(A5)==LOW){
     if(fxR_set == false) {
      Keyboard.press('g');
      fxR_set = true;
      digitalWrite(11, LOW);
    }
  } else {
    if(fxR_set == true) {
      Keyboard.release('g');
      fxR_set = false;
      digitalWrite(11, HIGH);
    }
  }
  //Encoder Reset  
    if(digitalRead(5)==LOW&&digitalRead(A0)==LOW&&digitalRead(A1)==LOW&&digitalRead(A2)==LOW){ 
    modechange += 1;
  } 
  modechange = modechange%2;
  //모드 변환용 함수. A,B,C,Start 버튼을 동시에 누르면 모드값을 변화시킴.
  //0이면 SDVX 모드, 1이면 KSM 모드.
  switch(modechange) {
      case SDVX_mode: {
      for(int i=0;i<=1;i++) {
    rotating[i] = true;
    if (encoderPos[i] != 0)
        {
           if(i==0)  Mouse.move(encoderPos[i],0,0);
           if(i==1)  Mouse.move(0,encoderPos[i],0);
 
           encoderPos[i] = 0;

         }
       }
     }
    case KSM_mode: {
        for(int i=0;i<=1;i++)
  {
    rotating[i] = true;
    if (encoderPos[i] != 0)
    {
        if(i==0) {
          if(encoderPos[i]>=1) {Keyboard.press('q'); Keyboard.release('q');}
          else {Keyboard.press('w'); Keyboard.release('w'); }
          }
        if(i==1) {
          if(encoderPos[i]>=1) {Keyboard.press('o'); Keyboard.release('o');}
          else {Keyboard.press('p'); Keyboard.release('p');}
        }
      }
               encoderPos[i] = 0;
      }
    }

   }


 
  delay(DELAY);
}
 
void doEncoderA()
{
 
  if( digitalRead(encoderPinA) != A_set )
  {  
    A_set = !A_set;
 
    if ( A_set && !B_set )
      encoderPos[0] += 1;
 
    rotating[0] = false;  
  }
}
 
void doEncoderB()
{
 
  if( digitalRead(encoderPinB) != B_set ) {
    B_set = !B_set;
   
    if( B_set && !A_set )
      encoderPos[0] -= 1;
 
    rotating[0] = false;
  }
}
 
void doEncoderC()
{
  if( digitalRead(encoderPinC) != C_set )
  {  
    C_set = !C_set;
 
    if ( C_set && !D_set )
      encoderPos[1] += 1;
 
    rotating[1] = false;
  }
}
 
void doEncoderD()
{
  if( digitalRead(encoderPinD) != D_set ) {
    D_set = !D_set;
   
    if( D_set && !C_set )
      encoderPos[1] -= 1;
 
    rotating[1] = false;
  }
}
