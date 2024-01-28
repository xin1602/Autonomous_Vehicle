 #include "PS2X_lib.h"
#include <Servo.h>

#define change 13

#define clk 3
#define attention 4
#define command 5
#define data 6

#define in1 7
#define in2 8
#define in3 11
#define in4 12
//#define ena_give 9
#define en_give 10

#define follow_in_a A0 
#define follow_in_b A1 
#define follow_in_c 9

#define servoAttach1_pin A2 
#define servoAttach2_pin A3 
#define servoAttach3_pin A4 
#define servoAttach4_pin A5


Servo servoAttach1; 
Servo servoAttach2;
Servo servoAttach3;
Servo servoAttach4;  

PS2X ps2x;
int i=0;
int j=1;
int speedd;
int time_1;
int time_4;
//-------馬達控制------------
int servoAttach1_time = 0;
int servoAttach4_time = 0;
//-------智駕------------
int follow_get_a;
int follow_get_b;
int follow_get_c;//直角轉彎
void setup() {
  // put your setup code here, to run once:

  pinMode(change,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(en_give,OUTPUT);
  pinMode(follow_in_a,INPUT);
  pinMode(follow_in_b,INPUT);
  pinMode(follow_in_c,INPUT);
  pinMode(servoAttach1_pin,OUTPUT);
  pinMode(servoAttach2_pin,OUTPUT);
  pinMode(servoAttach3_pin,OUTPUT);
  pinMode(servoAttach4_pin,OUTPUT);
  
//  Serial.begin(9600);
  
  servoAttach1.attach(servoAttach1_pin);
  servoAttach2.attach(servoAttach2_pin);
  servoAttach3.attach(servoAttach3_pin);
  servoAttach4.attach(servoAttach4_pin);

  servoAttach1.write(90);

  servoAttach4.write(0);

  do{
    delay(100);
  }while(ps2x.config_gamepad(clk,command,attention,data));
    //Serial.println("gamepad is found");
}


void loop() {
  // put your main code here, to run repeatedly:
  ps2x.read_gamepad();
  if(ps2x.Button(PSB_TRIANGLE)){
    i=1;
  }else if(i==1){
     j++;
     if(j%2==1)
       j=1;
     else if(j%2==0)
       j=0;
       i=0;
  }
  if(j==1){
    
//    follow();
    follow2();
   
  }
  else{
    digitalWrite(en_give,1);
    walk();
    servo_control();
  }
  delay(10);
}

/*void follow(){
/////////////////////智駕控制車體
  follow_get = analogRead(follow_in);
  follow_get = map(follow_get,0,1023,0,255);
  Serial.println(follow_get);
///////////////////////////////////直走/停止
  if((follow_get>=0&&follow_get<=22)||(follow_get>=233&&follow_get<=255)){
    analogWrite(ena,255);
    analogWrite(enb,255);
  }  
/////////////////////////////////////左轉 
  else if(follow_get>=23&&follow_get<=43){
    analogWrite(ena,200);
    analogWrite(enb,255); 
  }else if(follow_get>=44&&follow_get<=64){
    analogWrite(ena,150);
    analogWrite(enb,255); 
  }else if(follow_get>=65&&follow_get<=85){
    analogWrite(ena,100);
    analogWrite(enb,255); 
  }else if(follow_get>=86&&follow_get<=106){
    analogWrite(ena,150);
    analogWrite(enb,255); 
  }else if(follow_get>=107&&follow_get<=127){
    analogWrite(ena,200);
    analogWrite(enb,255); 
  }
/////////////////////////////////////右轉    
  else if(follow_get>=128&&follow_get<=148){
    analogWrite(ena,255);
    analogWrite(enb,200); 
  }else if(follow_get>=149&&follow_get<=169){
    analogWrite(ena,255);
    analogWrite(enb,150); 
  }else if(follow_get>=170&&follow_get<=190){
    analogWrite(ena,255);
    analogWrite(enb,100); 
  }else if(follow_get>=191&&follow_get<=211){
    analogWrite(ena,255);
    analogWrite(enb,150); 
  }else if(follow_get>=212&&follow_get<=232){
    analogWrite(ena,255);
    analogWrite(enb,200); 
  }
////////////////////////////////////
  if((follow_get>=0&&follow_get<=106)||(follow_get>=191&&follow_get<=211)){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
  }else if(follow_get>=107&&follow_get<=127){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);   
  }else if(follow_get>=212&&follow_get<=232){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);   
  }else if(follow_get>=233&&follow_get<=255){
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);   
  }
}
*/
void follow2(){
/////////////////////智駕控制車體
  follow_get_a = digitalRead(follow_in_a);
  follow_get_b = digitalRead(follow_in_b);
  follow_get_c = digitalRead(follow_in_c);
//  Serial.println(follow_get);
////////////////////////////////// 停止/直走/左轉/右轉
//  if((follow_get_a==0&&follow_get_b==0)||(follow_get_a==1&&follow_get_b==1)||(follow_get_a==0&&follow_get_b==1)||(follow_get_a==1&&follow_get_b==0)){
//    analogWrite(ena,254);
//    analogWrite(enb,254);
//  }  


////////////////////////////////////
  if(follow_get_a==1&&follow_get_b==1){
    digitalWrite(en_give,0);
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
  }else if(follow_get_a==0&&follow_get_b==1){
    digitalWrite(en_give,1);
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);   
  }else if(follow_get_a==1&&follow_get_b==0){
    digitalWrite(en_give,1);
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);   
  }else if(follow_get_a==0&&follow_get_b==0){
    digitalWrite(en_give,1);
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);   
  }
}

void walk(){
/////////////////////速度控制
  speedd = map(ps2x.Analog(PSS_LX),0,255,0,100);
  digitalWrite(en_give,1);
   if(ps2x.Button(PSB_R2)&&!ps2x.Button(PSB_L2)){
    if(speedd<48){
//    digitalWrite(ena_give,1);
//    digitalWrite(enb_give,0);
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW); 
    }else if(speedd>52){
//    digitalWrite(ena_give,1);
//    digitalWrite(enb_give,0);
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
  }else{
//    digitalWrite(ena_give,1);
//    digitalWrite(enb_give,1);
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
  } 
}else if(ps2x.Button(PSB_L2)&&!ps2x.Button(PSB_R2)){
   digitalWrite(in1, LOW);
   digitalWrite(in2, HIGH);
   digitalWrite(in3, LOW);
   digitalWrite(in4, HIGH);
}else{
   digitalWrite(in1, LOW);
   digitalWrite(in2, LOW);
   digitalWrite(in3, LOW);
   digitalWrite(in4, LOW);
  }
}
void servo_control(){
//---------------如果按的是servoAttach1-------------

  if(ps2x.Button(PSB_CIRCLE)){
    time_1=1;
    if(servoAttach1_time==1||servoAttach1_time==3){ 
      servoAttach1.write(90); //機械手臂底座旋轉至90度
    }else if(servoAttach1_time==0){
      servoAttach1.write(180); //機械手臂底座旋轉至180度
    }else if(servoAttach1_time==2){
      servoAttach1.write(0); //機械手臂底座旋轉至0度
    }
  }
  else if(time_1==1){
    servoAttach1_time++;
    if(servoAttach1_time==4){//回到正中間
      servoAttach1_time = 0;
    }
      time_1=0;   
  }
    
   
//---------------如果按的是servoAttach2-------------

  if(ps2x.Button(PSB_PAD_LEFT)){ 
    servoAttach2.write(0); //不停旋轉(正轉)
  }else if(ps2x.Button(PSB_PAD_RIGHT)){
    servoAttach2.write(180); //不停旋轉(反轉)
  }else{
    servoAttach2.write(90); //馬達不動
  }
//---------------如果按的是servoAttach3-------------
  if(ps2x.Button(PSB_PAD_UP)){ 
    servoAttach3.write(180); //不停旋轉(正轉)
  }else if(ps2x.Button(PSB_PAD_DOWN)){
    servoAttach3.write(0); //不停旋轉(反轉)
  }else{
    servoAttach3.write(90); //馬達不動
  }
//---------------如果按的是servoAttach4-------------
  if(ps2x.Button(PSB_CROSS)){
    time_4=1;
    if(servoAttach4_time%2==0){
     servoAttach4.write(180); //爪子開啟
    }else if(servoAttach4_time%2==1){
      servoAttach4.write(0); //爪子關閉
    }
  }
  else if(time_4==1){
    servoAttach4_time++;
    time_4=0;
  }
   
}
