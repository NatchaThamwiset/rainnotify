
#include <WiFiManager.h>
#include <TridentTD_LineNotify.h>
#define LINE_TOKEN  "iQ2ClIX24buY3bbRtX23jjCN9Hplhxe8zIROIxo1PAv"

WiFiManager wm;
void initWiFi() {
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}



void setup()
{
  pinMode(33, INPUT);
  LINE.setToken(LINE_TOKEN);
  WiFi.mode(WIFI_STA); 
  Serial.begin(115200);

 bool res;
     res = wm.autoConnect("ConfigWiFi(Rain)");
      if(!res) {
        Serial.println("Failed to connect");
        ESP.restart();
    } 
    else {
        Serial.println("connected...yeey :)");
    }
    initWiFi();
}

int count = 0;
void loop(){
  int g = digitalRead(33);
  if(g == 0){
    count += 1;
    if(count >= 10){
      LINE.notify("ตรวจพบฝน อย่าลืมเก็บผ้านะ");
      delay(3000);
      }
      delay(200);
    }
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Reconnecting to WiFi...");
    initWiFi();    
  }
 
}
