//------循跡模組設定(視實際情況自行更改)------ 
#define follow_1 2
#define follow_2 3
#define follow_3 4
#define follow_4 5
#define follow_5 6
#define follow_out_a 8
#define follow_out_b 9

//------Color Sensor設定(視實際情況自行更改)------
#define out 7
//#define s0 10
//#define s1 11
#define ena 10
#define enb 11
//#define s2 12
//#define s3 13
#define color_get 12
#define en_get 13

//------超音波感測器設定(視實際情況自行更改)------
#define trig A0
#define echo A1

int color_num=0;
int follow_num=0;

int red;
int blue;
int green;
//-------超音波感測到的距離------------
unsigned long d;
String trafic_light;

int en_get_num;
void setup() {
  pinMode(follow_1     ,INPUT);
  pinMode(follow_2     ,INPUT);
  pinMode(follow_3     ,INPUT);
  pinMode(follow_4     ,INPUT);
  pinMode(follow_5     ,INPUT);  
  pinMode(out          ,OUTPUT);
  pinMode(follow_out_a ,OUTPUT);
  pinMode(follow_out_b ,OUTPUT);
  pinMode(ena          ,OUTPUT);
  pinMode(enb          ,OUTPUT);  
  pinMode(color_get    ,INPUT);
  pinMode(en_get       ,INPUT);
  pinMode(trig         ,OUTPUT);
  pinMode(echo         ,INPUT);
//  pinMode(A2,OUTPUT);
//  pinMode(A3,OUTPUT);
//  pinMode(A4,OUTPUT);
//  pinMode(A5,INPUT);

  // 設定頻率尺度(frequency scaling)為 20%
//  digitalWrite(s0,HIGH);
//  digitalWrite(s1,HIGH);

 // Serial.begin(9600);
}

void loop() {

  color_num=0;
  follow_num=0;

  
 // wave();
 // color(trafic_light);
  
//  follow_output(color_num,follow_num);
  follow_output2();
//  walk(color_num,follow_num);
  ena_enb();
}

/*void color(String trafic_light){
  
  digitalWrite(s2, LOW);                                                // S2 LOW and S3 LOW, 打開紅色濾鏡
  digitalWrite(s3, LOW);  
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);                                               // S2 LOW and S3 HIGH, 打開藍色濾鏡
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);                                               // S2 HIGH and S3 HIGH, 打開綠色濾鏡
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  
  Serial.print(" R Intensity:");  //在序列埠螢幕中印出R G B三種顏色感應器輸出值
  Serial.print(red, DEC);  
  Serial.print(" G Intensity: ");  
  Serial.print(green, DEC);  
  Serial.print(" B Intensity : ");  
  Serial.print(blue, DEC); 
  
  if(trafic_light=="close_light"){ 
  
  if (red < blue && red < green)                 
  {  
   Serial.println(" - (Red Color)");
   color_num=1;  
  }  
  else if (blue < red && blue < green)   //當藍色 B 輸出值為最低時，在序列埠螢幕中印出 Blue Color，點亮藍色 LED
  {  
   Serial.println(" - (Blue Color)");
   color_num=0;  
  }  
  else if (green < red && green < blue)  //在序列埠螢幕中印出 Green Color，點亮綠色 LED
  {  
   Serial.println(" - (Green Color)");  
   color_num=0;
  }  
  else{
  Serial.println();  
  color_num=0;
  }
  delay(10); 
  
  } 
  
}
*/
void color(){
  color_num = digitalRead(color_get);
}
void ena_enb(){
  
  en_get_num=digitalRead(en_get);
   
  if(en_get_num==0){
    analogWrite(ena,180);
    analogWrite(enb,180);
//  }else if(ena_get_num==0&&enb_get_num==1){
//    analogWrite(ena,0);
//    analogWrite(enb,255);
//  }else if(ena_get_num==1&&enb_get_num==0){
//    analogWrite(ena,255);
//    analogWrite(enb,0);
  }else{
    analogWrite(ena,255);
    analogWrite(enb,255);
  }
}
void follow() {
  follow_num = 0;
  if(digitalRead(follow_1)== 0)
    follow_num += 1 ;
    
  if(digitalRead(follow_2)== 0)
    follow_num += 10 ;
     
  if(digitalRead(follow_3)== 0)
    follow_num += 100 ; 
     
  if(digitalRead(follow_4)== 0)
    follow_num += 1000 ;
    
  if(digitalRead(follow_5)== 0)
    follow_num += 10000 ;

//  Serial.println(follow_num); 
    
}

/*void follow_output(int color_num,int follow_num){

  if (color_num == 1){   //判斷為紅燈時
    analogWrite(follow_out,255);      
  }0
  else if (color_num == 0){   //判斷不為紅燈時
        
    //判斷循跡
    if (follow_num == 0 || follow_num == 100 || follow_num == 11111){  //直走
      analogWrite(follow_out,0); 
//      Serial.println("0");          
    }
    else if (follow_num == 1100){  //小小左
      analogWrite(follow_out,33);
//      Serial.println("33");       
    }
    else if (follow_num == 110){  //小小右
      analogWrite(follow_out,138);   
//      Serial.println("138");        
    }
    else if (follow_num == 1000){  //小左
      analogWrite(follow_out,54);  
//      Serial.println("54");         
    }
    else if (follow_num == 10){  //小右
      analogWrite(follow_out,159); 
//      Serial.println("159");           
    }
    else if (follow_num == 11000){  //中左
      analogWrite(follow_out,75);   
//      Serial.println("75");        
    }
    else if (follow_num == 11){   //中右
      analogWrite(follow_out,180); 
//      Serial.println("180");           
    }
    else if (follow_num == 10000){   //大左
      analogWrite(follow_out,106); 
//      Serial.println("106"); ;     
    }
    else if (follow_num == 1){   //大右
      analogWrite(follow_out,201); 
//      Serial.println("201");           
    }
    else if (follow_num == 11100){  //大大左 
      analogWrite(follow_out,117);  
//      Serial.println("117");          
    }
    else if (follow_num == 111){   //大大右
      analogWrite(follow_out,222); 
//      Serial.println("222");        
    }
    else{                       //都不是 (旋轉)
      analogWrite(follow_out,222); 
//      Serial.println("222");         
    }
  }
}
*/
void follow_output2(){
  
  color();
  follow();

  
  if (color_num == 1){   //判斷為紅燈時
   digitalWrite(follow_out_a,0);
   digitalWrite(follow_out_b,0);    
  }
  else if (color_num == 0){   //判斷不為紅燈時
        
    //判斷循跡
    if (follow_num == 0 || follow_num == 100 || follow_num == 11111){  //直走
      digitalWrite(follow_out_a,1);
      digitalWrite(follow_out_b,1);  
         
    }
    else if (follow_num == 1100){  //小小左
      digitalWrite(follow_out_a,0); 
      digitalWrite(follow_out_b,1); 
     
    }
    else if (follow_num == 110){  //小小右
      digitalWrite(follow_out_a,1); 
      digitalWrite(follow_out_b,0);         
    }
    else if (follow_num == 1000){  //小左
      digitalWrite(follow_out_a,0); 
      digitalWrite(follow_out_b,1);        
    }
    else if (follow_num == 10){  //小右
      digitalWrite(follow_out_a,1); 
      digitalWrite(follow_out_b,0);            
    }
    else if (follow_num == 11000){  //中左
      digitalWrite(follow_out_a,0); 
      digitalWrite(follow_out_b,1);         
    }
    else if (follow_num == 11){   //中右
      digitalWrite(follow_out_a,1); 
      digitalWrite(follow_out_b,0);            
    }
    else if (follow_num == 10000){   //大左
      digitalWrite(follow_out_a,0); 
      digitalWrite(follow_out_b,1);      
    }
    else if (follow_num == 1){   //大右
      digitalWrite(follow_out_a,1); 
      digitalWrite(follow_out_b,0);           
    }
    else if (follow_num == 11100){  //大大左 
      digitalWrite(follow_out_a,0); 
      digitalWrite(follow_out_b,1); ;          
    }
    else if (follow_num == 111){   //大大右
      digitalWrite(follow_out_a,1); 
      digitalWrite(follow_out_b,0);       
    }
    else{                       //都不是 (旋轉)
      digitalWrite(follow_out_a,0); 
      digitalWrite(follow_out_b,1);          
    }
  }
}


/*void walk(int color_num,int follow_num){
  if (color_num == 1){   //判斷為紅燈時
    analogWrite(ena,255);
    analogWrite(enb,255);  
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);      
  }
  else if (color_num == 0){   //判斷不為紅燈時
        
    //判斷循跡
    if (follow_num == 400000 || follow_num == 400100 || follow_num == 411111){  //直走
      analogWrite(ena,255);
      analogWrite(enb,255);  
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
           
    }
    else if (follow_num == 401100){  //小小左
      analogWrite(ena,200);
      analogWrite(enb,255); 
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);     
    }
    else if (follow_num == 400110){  //小小右
      analogWrite(ena,255);
      analogWrite(enb,200);   
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);     
    }
    else if (follow_num == 401000){  //小左
      analogWrite(ena,150);
      analogWrite(enb,255);   
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);     
    }
    else if (follow_num == 400010){  //小右
      analogWrite(ena,255);
      analogWrite(enb,150);   
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);     
    }
    else if (follow_num == 411000){  //中左
      analogWrite(ena,100);
      analogWrite(enb,255);  
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);     
    }
    else if (follow_num == 400011){   //中右
      analogWrite(ena,255);
      analogWrite(enb,100);  
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);     
    }
    else if (follow_num == 410000){   //大左
      analogWrite(ena,150);
      analogWrite(enb,255);  
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);     
    }
    else if (follow_num == 400001){   //大右
      analogWrite(ena,255);
      analogWrite(enb,150);  
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);     
    }
    else if (follow_num == 411100){  //大大左 
      analogWrite(ena,200);
      analogWrite(enb,255);  
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);     
    }
    else if (follow_num == 400111){   //大大右
      analogWrite(ena,200);
      analogWrite(enb,255);  
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);   
    }
    else{                       //都不是 (旋轉)
      analogWrite(ena,255);
      analogWrite(enb,255);  
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);   
    }
  }
  
}
*/
/*void wave(){
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  d = pulseIn(echo,HIGH,23200) / 58;

  if (d<=25 && d!=0)
    trafic_light = "close_light";
  
  else
    trafic_light = "not_close_light";
  
}
*/
