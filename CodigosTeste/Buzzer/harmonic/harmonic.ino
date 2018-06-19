const int buzzer = 8; //Constante armazenando o número do pino que vamos utilizar

#define C 32.703194
#define D 36.708096
#define E 41.203442
#define F 43.653526
#define G 48.999424
#define A 55
#define B 61.735416
//Notas da Oitava um, C1, D, etc

double nota(double nota, int oitava){
  return nota*pow(2,oitava);
}

void setup() {
  pinMode(buzzer,OUTPUT);
}
 
void loop() { 
    tone(buzzer, nota(C,3));
    delay(1000);
    tone(buzzer, nota(E,3));
    delay(1000);
    tone(buzzer, nota(G,3));
    delay(1000);
    noTone(buzzer);
}
