#define BUZ 53

void setup() {
  Serial.begin(9600);
  for(int i = 500; i < 20000; i+=2){
    tone(BUZ, i);
  }
  noTone(BUZ);
}

void loop() {
  // put your main code here, to run repeatedly:

}
