#define BUZ 49

void setup() {
  Serial.begin(9600);
  /*for(int i = 500; i < 12500; i+=2){
    tone(BUZ, i);
    delay(1);
    Serial.println(i);
  }*/
  tone(BUZ,-100);
  delay(5000);
  noTone(BUZ);
}

void loop() {
  // put your main code here, to run repeatedly:

}
