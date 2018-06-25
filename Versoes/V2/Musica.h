//Notas musicais
#define n_C 32.703194
#define n_D 36.708096
#define n_E 41.203442
#define n_F 43.653526
#define n_G 48.999424
#define n_A 55
#define n_B 61.735416
//Notas da Oitava Zero, C0, D0, E0, etc
#define T 500

struct music {
  int n_size;
  double musica[14];
  double pitch[14];
};
typedef struct music Music;

double nota(double nota, int oitava){
  return nota*pow(2,oitava);
}
void tocaMusica(Music m, int pino_buzzer){
  for(int i = 0; i < m.n_size; i++){
    if(m.musica[i] != 0){
      tone(pino_buzzer, m.musica[i]);
    }
    delay(m.pitch[i]);
    noTone(pino_buzzer); 
  }
}

Music salvaMusica(double *musica, double *pitch, int n_size){
  Music m;
  m.n_size = n_size;
  for(int i = 0; i < n_size; i++){
    m.musica[i] = musica[i];
    m.pitch[i] = pitch[i];
  }
  return m;
}

Music brilha_brilha_estrelinha(){
  int n_size = 14;
  double musica[14] = {nota(n_G,3),nota(n_G,3),nota(n_D,4),nota(n_D,4),nota(n_E,4),nota(n_E,4),nota(n_D,4),nota(n_C,4),nota(n_C,4),nota(n_B,3),nota(n_B,3),nota(n_A,3),nota(n_G,3),0};
  double pitch[14] =  {T,T,T,T,T,T,2*T,T,T,T,T,2*T,2*T,2*T};
  return salvaMusica(musica, pitch, n_size);
}


