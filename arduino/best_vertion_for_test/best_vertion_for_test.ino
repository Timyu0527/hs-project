#include <math.h>
#include <Servo.h>

//commend change
const int rounds=1;//needing how many rounds to run
const char dir='R';

//test change+++++++++++
//---motor
const byte equalspee=-3;
const int firstback=200;
const int firsturn=300;
const int curve=550;
const int Bcurve=150;

const byte quick=120;
const byte slow=50;
const byte sslow=40;
const byte middle=70;
const byte maxi=252;
//----Servo
int standardL=166;
int standardR=10;
int angleR=130;
int angleL=2*105-angleR;
//color
const int ww=20;  //white judge
const int dar=40;  //for red color judge
const int darg=30;
const int dd=70;  //for black judge

//////////////////////////////////////////////////
//====definitions=========================================
//++++sensors++++++
//----color set------
#define S0 A5
#define S1 A4
#define S2 A2
#define S3 A1 
#define sensorOut A0

int red = 0;  
int green = 0;  
int blue = 0;  
//-----------------------------

//----ir set------
#define irL 45
#define irM 47
#define irR 49

//#define irLB 44
//#define irRB 48

int statusL;  int statusL2;
int statusR;  int statusR2;
int statusM;

//int statusLB,statusRB;
//------------------------------
//++++++++++++++++++++++++++++++++++++++

//++++motors++++++
//----running set-------
#define motorL 51
#define motorL2 53
#define motorR 50
#define motorR2 52

#define pL 6
#define pR 7

#define stby 41
//-----------------------------

//----Servo set------
Servo rightServo;
Servo leftServo;
Servo directionServo;
Servo kickServo;
//-----------------------------
//++++++++++++++++++++++++++++++++++

//++++variables++++++
int r=0;
char commend='b';
//++++++++++++++++++++++++++++++++++
//=======================================================

//====liberaries======
//++++color sens++++++
void color()  
{
  digitalWrite(S2, LOW);  
  digitalWrite(S3, LOW);  
  red = pulseIn(sensorOut, digitalRead(sensorOut) == HIGH ? LOW : HIGH, 200);  
  digitalWrite(S3, HIGH);  
  blue = pulseIn(sensorOut, digitalRead(sensorOut) == HIGH ? LOW : HIGH, 200);  
  digitalWrite(S2, HIGH);  
  green = pulseIn(sensorOut, digitalRead(sensorOut) == HIGH ? LOW : HIGH, 200);  
}

boolean YorN(char color){ 
  boolean yes=false;
  switch(color){
    
    case 'W':if (blue < ww && green < ww && blue <ww){yes=true;}
    break;
    
    case 'R':if (red < green && YorN('D') == false && red < blue && green > dar) 
      {yes=true;}
      break;
    
    case 'G':if (green < red && red > darg && YorN('D') == false)
      {yes=true;}
      break;

    /*case 'B':if (blue < red && blue < green && YorN('W') == false)
      {yes=true;}
      break;*/

    case 'Y':if (blue > ww && abs(green - red)<=5 && YorN('D') == false)
      {yes=true;}
      break;

    case 'D':if (red > dd && green > dd && blue > dd){yes=true;}
      break; 
  }
  return yes;
}

//+++++++++++++++++++++++++++++++++++++++++++

//++++motion control++++++
//----forward or backward----
void go(char ward){
  switch(ward){

  case'F':
    digitalWrite(motorL,HIGH);   
    digitalWrite(motorR,HIGH);
    digitalWrite(motorL2,LOW);
    digitalWrite(motorR2,LOW);
    break;

  case'B':
    digitalWrite(motorL,LOW); 
    digitalWrite(motorR,LOW); 
    digitalWrite(motorL2,HIGH); 
    digitalWrite(motorR2,HIGH);
    break;
  }
  analogWrite(pL,quick-equalspee);  
  analogWrite(pR,quick);
}

void go(char ward , byte spee){
  switch(ward){

  case'F':
    digitalWrite(motorL,HIGH);   
    digitalWrite(motorR,HIGH);
    digitalWrite(motorL2,LOW);
    digitalWrite(motorR2,LOW);
    break;

  case'B':
    digitalWrite(motorL,LOW); 
    digitalWrite(motorR,LOW); 
    digitalWrite(motorL2,HIGH); 
    digitalWrite(motorR2,HIGH);
    break;
  }
  analogWrite(pL,spee-equalspee);  
  analogWrite(pR,spee);
}

void go(char ward , byte spee , int t){
  switch(ward){

  case'F':
    go('F',spee);
    break;

  case'B':
    go('B',spee);
    break;
  }
  delay(t);
}
//---------------------------------------

//----turn------
void turn(char dire){
  switch(dire){
    
    case 'R':
    digitalWrite(motorL,HIGH); 
    digitalWrite(motorR,LOW); 
    digitalWrite(motorL2,LOW); 
    digitalWrite(motorR2,LOW);
    break;

    case 'L':
    digitalWrite(motorL,LOW); 
    digitalWrite(motorR,HIGH); 
    digitalWrite(motorL2,LOW); 
    digitalWrite(motorR2,LOW);
    break;

    case 'B':
    digitalWrite(motorL,HIGH); 
    digitalWrite(motorR,LOW); 
    digitalWrite(motorL2,LOW); 
    digitalWrite(motorR2,HIGH);
    break;

    case 'D':
    digitalWrite(motorL,LOW); 
    digitalWrite(motorR,HIGH); 
    digitalWrite(motorL2,HIGH); 
    digitalWrite(motorR2,LOW);
    break;
  }
  analogWrite(pL,quick-equalspee);  
  analogWrite(pR,quick);
}

void turn(char dire , byte spee){
  switch(dire){
    
    case 'R':
    digitalWrite(motorL,HIGH); 
    digitalWrite(motorR,LOW); 
    digitalWrite(motorL2,LOW); 
    digitalWrite(motorR2,LOW);
    break;

    case 'L':
    digitalWrite(motorL,LOW); 
    digitalWrite(motorR,HIGH); 
    digitalWrite(motorL2,LOW); 
    digitalWrite(motorR2,LOW);
    break;

    case 'B':
    digitalWrite(motorL,HIGH); 
    digitalWrite(motorR,LOW); 
    digitalWrite(motorL2,LOW); 
    digitalWrite(motorR2,HIGH);
    break;

    case 'D':
    digitalWrite(motorL,LOW); 
    digitalWrite(motorR,HIGH); 
    digitalWrite(motorL2,HIGH); 
    digitalWrite(motorR2,LOW);
    break;
  }
  analogWrite(pL,spee-equalspee);  
  analogWrite(pR,spee);
}

void turn(char dire , byte spee , int t){
  switch(dire){
     
    case 'R':
    turn('R',spee);
    break;

    case 'L':
    turn('L',spee);
    break;

    case 'B':
    turn('B',spee);
    break;

    case 'D':
    turn('D',spee);
    break;
  }
  delay(t);
}

//this library lets car turn right or left in the line
void turn(char dire , boolean line){
  
  if(line == true){
    switch(dire){
    
      case 'R':
      go('B',quick,firstback);
      turn('R',quick,firsturn);
    
      statusM=digitalRead(irM);   
      while(statusM == LOW)  {turn('R');  statusM=digitalRead(irM);}
      turn('L',slow,curve);
      break;
      
      case 'L':
      go('B',quick,firstback);
      turn('L',quick,firsturn);
    
      statusM=digitalRead(irM);   
      while(statusM == LOW)  {turn('L');  statusM=digitalRead(irM);}
      turn('R',slow,curve);
      break;

      case 'B':
      turn('B',quick,firsturn);
      
      statusM=digitalRead(irM);
      while(statusM == LOW){
      turn('B');
      statusM=digitalRead(irM);
      }
      
      turn('D',slow,Bcurve);
      break;
    }
  }

  else {switch(dire){
     
    case 'R':
    turn('R');
    break;

    case 'L':
    turn('L');
    break;

    case 'B':
    turn('B');
    break;
    }
  }
}
//-----------------------------------------------

//----stopp------
void stopp(){
    digitalWrite(motorL,LOW); 
    digitalWrite(motorR,LOW); 
    digitalWrite(motorL2,LOW); 
    digitalWrite(motorR2,LOW);

  analogWrite(pL,0);  
  analogWrite(pR,0);
}

void stopp(int t){
    stopp();
    delay(t);
}
//---------------------------------------------

//----followLine------
void followLine(char ward){

  statusL=digitalRead(irL);
  statusR=digitalRead(irR);
  statusM=digitalRead(irM);
/*  statusLB=digitalRead(irLB);
  statusRB=digitalRead(irRB);*/

  if(statusR==HIGH)  {statusR=LOW;  statusR2=HIGH;}
  else{statusR=HIGH;  statusR2=LOW;}

  if(statusL==HIGH)  {statusL=LOW;  statusL2=HIGH;}
  else{statusL=HIGH;  statusL2=LOW;}

  switch(ward){
    case 'F':
      /*if(statusLB==HIGH){
        digitalWrite(motorR,HIGH);  
        digitalWrite(motorR2,LOW);
        }
      if(statusRB==HIGH){
        digitalWrite(motorL,HIGH);  
        digitalWrite(motorL2,LOW); 
        }*/
       
      if(statusM==HIGH)  {go('F');}
      /*else if(statusM == LOW && statusL == HIGH && statusR==HIGH){
        int lef=0,rig=0;
        while(lef < 200 && statusM == LOW){turn('L');delay(1);  lef+=1;}
        while(rig < 400 && statusM == LOW){turn('R');  delay(1);  rig+=1;}
        }*/
      else{
        digitalWrite(motorL,statusL);
        digitalWrite(motorL2,statusL2);
        digitalWrite(motorR,statusR);
        digitalWrite(motorR2,statusR2);
      }
      break;
      
    case 'B':
      if(statusM==HIGH){go('B');}
      else{
        digitalWrite(motorL,statusR2);
        digitalWrite(motorL2,statusR);
        digitalWrite(motorR,statusL2);
        digitalWrite(motorR2,statusL);
      }
      break;
  }

  analogWrite(pL,middle-equalspee);  
  analogWrite(pR,middle);
}

void followLine(char ward , byte spee){

  statusL=digitalRead(irL);
  statusR=digitalRead(irR);
  statusM=digitalRead(irM);
  //statusLB=digitalRead(irLB);
  //statusRB=digitalRead(irRB);

  if(statusR==HIGH)  {statusR=LOW;  statusR2=HIGH;}
  else{statusR=HIGH;  statusR2=LOW;}

  if(statusL==HIGH)  {statusL=LOW;  statusL2=HIGH;}
  else{statusL=HIGH;  statusL2=LOW;}

  switch(ward){
    case 'F':
      /*if(statusLB==HIGH)  {turn('R');}
      else if(statusRB==HIGH)  {turn('L');}*/
       
      if(statusM==HIGH)  {go('F');}
      /*else if(statusM == LOW && statusL == HIGH && statusR==HIGH){
        int lef=0,rig=0;
        while(lef < 200 && statusM == LOW){turn('L');delay(1);  lef+=1;}
        while(rig < 400 && statusM == LOW){turn('R');  delay(1);  rig+=1;}
        }*/
      else{
        digitalWrite(motorL,statusL);
        digitalWrite(motorL2,statusL2);
        digitalWrite(motorR,statusR);
        digitalWrite(motorR2,statusR2);
      }
      break;
      
    /*case 'B':
      if(statusM==HIGH){go('B');}
      else{
        digitalWrite(motorL,statusR2);
        digitalWrite(motorL2,statusR);
        digitalWrite(motorR,statusL2);
        digitalWrite(motorR2,statusL);
      }
      break;*/
  }

  analogWrite(pL,spee-equalspee);  
  analogWrite(pR,spee);
}
//-------------------------------------

//----weight------
void weight( int initial , int altimate){
  bool UorD;
  int L=standardL-initial;
  int R=standardR+initial;
 
   if(initial >= altimate){
      UorD=false;
   }else{
      UorD=true;
    } 
    leftServo.write(L);
    rightServo.write(R);

    if(UorD==true){
      while(R < altimate){
      L-=1;
      R+=1;
      delay(50);
      leftServo.write(L);
      rightServo.write(R);
    }
    }else{
      while(R >= altimate){
       L+=1;
       R-=1;
       delay(50);
       leftServo.write(L);
       rightServo.write(R);
     }                                  
   }
}

//----kick the ball------
void kickBall(char dire){
  
  kickServo.write(30);

  switch(dire){
    case'M':
    directionServo.write(105);
    break;

    case'R':
    directionServo.write(angleR);  //need to check
    break;

    case'L':
    directionServo.write(angleL);
    break;
  }  
  delay(600);
  
  kickServo.write(150);
  delay(600);
  }

  //----------------------------------------------

//==============================================================

void setup() {
  //----color sensor------
  pinMode(S0, OUTPUT);  digitalWrite(S0,HIGH);
  pinMode(S1, OUTPUT);  digitalWrite(S1,HIGH);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);  
  pinMode(sensorOut, INPUT);

  //----ir sensor------
  pinMode(irL,INPUT);
  pinMode(irR,INPUT);
  pinMode(irM,INPUT);
  /*pinMode(irRB,INPUT);
  pinMode(irLB,INPUT);*/

  //----running------
  pinMode(motorL,OUTPUT); 
  pinMode(motorR,OUTPUT);
  pinMode(motorL2,OUTPUT); 
  pinMode(motorR2,OUTPUT);

  pinMode(pL,OUTPUT);
  pinMode(pR,OUTPUT);

  pinMode(stby,OUTPUT);  digitalWrite(stby,HIGH);

  //----Servo------
  leftServo.attach(8);  leftServo.write(standardL);
  rightServo.attach(9);  rightServo.write(standardR);
  directionServo.attach(11);  directionServo.write(105);
  kickServo.attach(12);  kickServo.write(30);
}
//=============================================================

void loop() {
  color();
 followLine('F');
switch(commend){
//commend--------------------------------------

  case 'b':
    commend='s';
    color();
  break;

  case 's':
  while(YorN('G') == true)  {go('F');  color();}
  go('F',quick,500);
  color();

  commend='j';
  break;

  case 'j':
  while(YorN('R') == false){
    followLine('F',quick);
    color();
  }
    turn('R',true);
    
    followLine('F',quick);
    
    followLine('F',quick);
    
    while(statusR == HIGH || statusL == HIGH || statusM == LOW){
      followLine('F',middle);
    }
stopp();

weight(0,80);

followLine('F',slow);
go('F',slow,200);
followLine('F',slow);
while(statusM == HIGH || (statusR == HIGH && statusL == LOW && statusM == LOW) || (statusR == LOW && statusL == HIGH && statusM == LOW)){
  followLine('F',slow);
}

stopp();
weight(80,55);
go('B',middle,300);

  followLine('B',middle);

    while(statusR == HIGH || statusL == HIGH || statusM == LOW){
      followLine('B',middle);
    }

stopp(300);

    turn('B',true);

    color();
    followLine('F',middle);
    
    while(statusR == HIGH || statusL == HIGH || statusM == LOW){
      followLine('F',middle);
    }
    commend='f';
    followLine('F');
    go('F',quick,450);
    break;

    case 'f':
    color();

    go('F',quick,250);

    followLine('F',quick);
    
    color();
    while(YorN('Y') == false){
      followLine('F',quick);
      color();
    }

    go('B',middle,50);
      turn('R',true);

    followLine('F',slow);
      
    while(statusR == HIGH || statusL == HIGH || statusM == LOW){
      followLine('F',middle);
      }

    go('F',middle,300);
    turn('R',true);
    turn('R',middle,200);
    r+=1;
    if(r == rounds) {commend='m';}
  break;

  case 'm':
  color();

    go('F',quick,250);

    followLine('F',quick);
    
    color();
    while(YorN('Y') == false){
      followLine('F',quick);
      color();
    }
  go('F',quick,300);
  
  followLine('F');
    
    while(statusR == HIGH || statusL == HIGH || statusM == LOW){
      followLine('F');
    }

    go('F',middle,300);
    turn('R',true);

    followLine('F',middle);
  while(statusR == HIGH || statusL == HIGH || statusM == LOW){
    followLine('F',middle);
    color();
  }

  stopp(200);
  kickBall(dir);
  stopp(200);
  
  commend='a';
  break;

  case 'a':  

  
  go('B',quick,500);
  turn('B',true);

  color();
   while(YorN('W') == true){
    followLine('F',middle);
    color();
   }

   
   go('F',maxi,2000);
   commend='o';
   break;

   case 'o':
   
   color();
   while(YorN('R') == false){
    followLine('F',quick);
    color();
   }
  go('F',quick,300);
  
  commend='t';
  break;

  case 't':
  stopp();//*/
  }
}
