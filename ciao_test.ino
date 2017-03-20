
#include <Wire.h>
#include <UnoWiFiDevEd.h> // 必須引用「橋接器」程式庫
 
#define CONNECTOR "rest" // 連接器類型
#define SERVER_ADDR "140.113.124.3" // 網站伺服器IP位址
 
int r = 100; // 暫存隨機數字的變數
String command = "/brightness?r=";   // 傳給網站伺服器的路徑參數
 
void setup() {
  Serial.begin(9600);
  Ciao.begin(); // 啟用「橋接器」
  // 以"rest"連接器類型，連線到網站伺服器，送出隨機數字。
  Ciao.write(CONNECTOR, SERVER_ADDR, command+r);
}
void loop() {
  delay(1000); // 暫停10秒
  //r = random(1000); // 取隨機數字
  
  
  CiaoData data=Ciao.write(CONNECTOR, SERVER_ADDR, command+r);
  if(!data.isEmpty()){
    Serial.println(String(data.get(0))); 
    Serial.println(String(data.get(1)));
    Serial.println(String(data.get(2)));
    }
  else Serial.println("???");
  
}
