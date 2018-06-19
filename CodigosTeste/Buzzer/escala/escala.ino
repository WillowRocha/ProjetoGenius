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

#define T 500
#define SIZE 14
double musica[SIZE] = {nota(G,3), nota(G,3), nota(D,4), nota(D,4), nota(E,4), nota(E,4), nota(D,4), nota(C,4), nota(C,4),nota(B,3),nota(B,3),nota(A,3),nota(G,3), 0};
double pitch[SIZE]  = {T,          T,         T,         T,         T,         T,         2*T,       T,         T,         T,         T,         2*T,       2*T,        2*T};


void setup() {
  pinMode(buzzer,OUTPUT);
}
 
void loop() { 
  for(int i = 0; i < SIZE; i++){
    if(musica[i] != 0){
      tone(buzzer, musica[i]);
    }
    delay(pitch[i]);
    noTone(buzzer);
  }
 
}
