#include <Wire.h>
#include <UnoWiFiDevEd.h>
#define CONNECTOR "rest" // 連接器類型
#define SERVER_ADDR "140.113.124.3" // 網站伺服器IP位址
int r = 0; 
String command = "/rn?r=";   // 傳給網站伺服器的路徑參數
String command2="/people?r=";
int LED=13;
int irpin=7;
int irpin2=8;
int obstacle1=HIGH; //means no obstacle 
int obstacle2=HIGH;
int counter=0;
int counter2=0;
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
      if(counter==0) counter=1;
      if(counter2==1) counter2=2;
    }
    if(obstacle2==LOW){
      if(counter==1) counter=2;
      if(counter2==0) counter2=1;  
    }
    if(counter==2){
      //go in 
      r=1;
      CiaoData data=Ciao.write(CONNECTOR, SERVER_ADDR, command2+r);
      if(!data.isEmpty()){
          Serial.println(String(data.get(2)));
      }
      else Serial.println("???");
      counter=0;
      counter2=0;
    }
    if(counter2==2){
      //go out
      r=-1;
      CiaoData data=Ciao.write(CONNECTOR, SERVER_ADDR, command2+r);
      if(!data.isEmpty()){
          Serial.println(String(data.get(2)));
      }
      else Serial.println("???");
      counter=0;
      counter2=0;   
    }
    delay(500);
}
