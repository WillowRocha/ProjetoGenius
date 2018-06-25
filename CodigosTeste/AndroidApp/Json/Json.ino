#include "ArduinoJson-v5.13.2.h"
#include <SPI.h>
#include <SD.h>

File file;

void setup() {
  Serial.begin(9600);
  if(!SD.begin()){
    Serial.println("Erro ao abrir SD card!");
  }
  
  
  // put your setup code here, to run once:
  const size_t bufferSize = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3);
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.createObject();
  root["sensor"] = "gps";
  root["time"] = 123456789;

  JsonArray& data = root.createNestedArray("data");
  data.add(48.323);
  data.add(2.4323);

  file = SD.open("alemanha.txt", FILE_WRITE);
  if(file){
    root.printTo(Serial);
    root.printTo(file);
    file.close();
  } else {
    Serial.println("Falha ao abrir arquivo!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
