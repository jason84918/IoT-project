
#include <Wire.h>
#include <UnoWiFiDevEd.h> // 必須引用「橋接器」程式庫
 
#define CONNECTOR "rest" // 連接器類型
#define SERVER_ADDR "140.113.124.2" // 網站伺服器IP位址
 
//int r = 100; // 暫存隨機數字的變數
int brightness = 250;
int r = 250;
String command = "/brightness?r=";   // 傳給網站伺服器的路徑參數
 
void setup() {
  Serial.begin(9600);
  Ciao.begin(); // 啟用「橋接器」
  // 以"rest"連接器類型，連線到網站伺服器，送出隨機數字。
  Ciao.write(CONNECTOR, SERVER_ADDR, command+r);
  pinMode(9, OUTPUT);
}
void loop() {
  delay(1000); // 暫停10秒
  //r = random(1000); // 取隨機數字
  brightness = analogRead(2);
  Serial.print("Near = ");
  Serial.println(brightness);
  CiaoData data=Ciao.write(CONNECTOR, SERVER_ADDR, command+brightness);
  if(!data.isEmpty()){
    Serial.print("LED = ");
    //Serial.println(r);
    Serial.println(String(data.get(2)));
    if(String(data.get(2)) == "255" ){
      analogWrite(9, 255);
      }
    else if(String(data.get(2)) == "170"){
      analogWrite(9, 170);
    }
    else if(String(data.get(2)) == "85"){
      analogWrite(9, 85);
    }
    else{
     analogWrite(9, 0);
    }
  }
  else 
    Serial.println("???");
  /*if(r > 0){
    r = r - 10;
  }
  else{
    r = 250;
    }
  analogWrite(9, r);*/
  
}
