//Notas musicais
#define nota_C 32.703194
#define nota_D 36.708096
#define nota_E 41.203442
#define nota_F 43.653526
#define nota_G 48.999424
#define nota_A 55
#define nota_B 61.735416
//Notas da Oitava Zero, C0, D0, E0, etc
#define TEMPO 500
#define SIZE 0 // Isto deve ser definido manualmente de acordo com a música
double musica[SIZE] = {}; 
double pitch[SIZE]  = {};
// Brilha Brilha Estrelinha -> {nota(G,3), nota(G,3), nota(D,4), nota(D,4), nota(E,4), nota(E,4), nota(D,4), nota(C,4), nota(C,4),nota(B,3),nota(B,3),nota(A,3),nota(G,3), 0  };
//Tempo da música (picth)   -> {T,         T,         T,         T,         T,         T,         2*T,       T,         T,        T,        T,        2*T,      2*T,       2*T};

double nota(double nota, int oitava){
  return nota*pow(2,oitava);
}
void tocaMusica(double * musica, double * pitch, int size, int pino_buzzer){
  for(int i = 0; i < size; i++){
    if(musica[i] != 0){
      tone(pino_buzzer, musica[i]);
    }
    delay(pitch[i]);
    noTone(pino_buzzer);
  }
}

