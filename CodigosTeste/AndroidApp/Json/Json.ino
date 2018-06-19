#include "ArduinoJson-v5.13.2.h"

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  const size_t bufferSize = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3);
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.createObject();
  root["sensor"] = "gps";
  root["time"] = 123456789;

  JsonArray& data = root.createNestedArray("data");
  data.add(48.323);
  data.add(2.4323);

  root.printTo(Serial);

}

void loop() {
  // put your main code here, to run repeatedly:

}
