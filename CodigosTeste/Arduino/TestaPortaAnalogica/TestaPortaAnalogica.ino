void setup() {
  Serial.begin(9600);
}

void loop() {
    Serial.println("Iniciou");
    analogWrite(0,HIGH);
    delay(500);
    analogWrite(0,LOW);
    delay(500);
}
