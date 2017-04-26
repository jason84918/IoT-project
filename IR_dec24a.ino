#include <Wire.h>
#include <UnoWiFiDevEd.h>
#define CONNECTOR "rest" // 連接器類型
#define SERVER_ADDR "140.113.124.2" // 網站伺服器IP位址
int r = 0; 
String command = "/rn?r=";   // 傳給網站伺服器的路徑參數
String command2="/people?r=";
int LED=13;
int irpin=7;
int irpin2=8;
int obstacle1=HIGH; //means no obstacle 
int obstacle2=HIGH;
int state=0; //state{init,coming,leaving.come.leave}
void setup() {
  // put your setup code here, to run once:
   pinMode(LED,OUTPUT);
   pinMode(irpin,INPUT);
   pinMode(irpin2,INPUT);
   Serial.begin(9600);
   Ciao.begin(); // 啟用「橋接器」
  // 以"rest"連接器類型，連線到網站伺服器，送出隨機數字。
  Ciao.write(CONNECTOR, SERVER_ADDR, command+r);
}

void loop() {
    // put your main code here, to run repeatedly:
    obstacle1=digitalRead(irpin);
    obstacle2=digitalRead(irpin2);
    if(obstacle1==LOW){
      if(state==0) state=1;
      else if(state==1) state=1;
      else if(state==2) state=4;
    }
    if(obstacle2==LOW){
      if(state==0) state=2;
      else if(state==2) state=2;
      else if(state==1) state=3;  
      /*Serial.print("counter: ");
      Serial.println(counter);
      Serial.print("counter2: ");
      Serial.println(counter2);*/
    }
    if(state==3){
      //go in
      Serial.println("go in");
      r=1;
      CiaoData data=Ciao.write(CONNECTOR, SERVER_ADDR, command2+r);
      if(!data.isEmpty()){
        Serial.println(String(data.get(2)));
      }
      else Serial.println("???");
      state=0;
      }
    if(state==4){
      //go out
      Serial.println("go out");
      r=-1;
      CiaoData data=Ciao.write(CONNECTOR, SERVER_ADDR, command2+r);
      if(!data.isEmpty()){
        Serial.println(String(data.get(2)));
      }
      else Serial.println("???");
      state=0;
    }
    delay(500);
}
