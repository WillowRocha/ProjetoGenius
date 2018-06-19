#include <SPI.h>
#include <SD.h>
#include "SdCard.h" //It already includes de JsonParser
#include "Musica.h"

//Comunication
#define SERIAL_BLUETOOTH 115200
#define SERIAL_TERMINAL 9600
#define NUM_LEDS 0 // Numero de Leds instalados
#define BUZZER 0 //Pino do Buzzer
int leds[NUM_LEDS]    = {};
int buttons[NUM_LEDS] = {};

// Para aumentar o número de Leds instalados,
// basta setar NUM_LEDS e inserir os números
// dos pinos no leds[]; Não necessitando
// eles estarem em portas consecutivas.

long sequence[100];
long randButton;
int level, clicked, buttons_pos;
boolean lost;
long pontuation;

String recebeNomeJogador(){
  Serial.println("Informe o nome do Jogador");
  String incomingBytes;
  
  do{
    while(!Serial.available()){delay(10);}
    incomingBytes = "";
    while (Serial.available() > 0){
      char a = char(Serial.read());
      if(a != '\n')
        incomingBytes += a;
      delay(10);
    }
    if(incomingBytes.length() < 3){
      Serial.println("Minimo 3 caracteres");
    }
    if(incomingBytes.length() > 20){
      Serial.println("Numero maximo de caracteres alcancado. Maximo 20 caracteres");
    }
  } while (incomingBytes.length() < 3 || incomingBytes.length() > 20);
  
  return incomingBytes;
}

Ranking montaUsuario(){
  Ranking usuario;
  usuario.id = buscaProximoId();
  usuario.nome = recebeNomeJogador();
  return usuario;
}

void aguardaConexaoBluetooth(){
  if(!Serial.available()){
    Serial.println("Bluetooth nao disponivel, aguardando...");
  }
  while(!Serial.available()){delay(10);}
  
  while(Serial.available() > 0){
    char a = Serial.read();
    delay(10);
  }
}

void ordenaRanking(Ranking rank[], int size_r){
  
}

void enviaRankingInicialViaBluetooth(){
  Serial.println("Enviando Ranking inicial...");
  Ranking rank[RANK_SIZE];
  int size_r = buscaRankingNoArquivo(rank);
  ordenaRanking(rank, size_r);
  JsonObject& ranking = parseRankingToJson(rank, size_r);
  ranking.printTo(Serial);
}

void enviaRankingFinalViaBluetooth(){
  Serial.println("Enviando Ranking final...");
  Ranking rank[RANK_SIZE];
  int size_r = buscaRankingNoArquivo(rank);
  ordenaRanking(rank, size_r);
  //Buscar a posição do jogador atual no Ranking
  JsonObject& ranking = parseRankingToJson(rank, size_r);
  ranking.printTo(Serial);
}

void jogar() {
  do {
    buttons_pos = 0;
    level++;
    Serial.print("Você está no Nível: ");
    Serial.println(level);

    for (int i = 0; i < level; i++) {
      buttons[i] = random(0, NUM_LEDS);
      digitalWrite(leds[sequence[i]], HIGH);
      delay(1000);
      digitalWrite(leds[sequence[i]], LOW);
    }
    if (!lost) {
      level++;
      Serial.println("");
      Serial.println("Parabéns! Você ganhou e agora subiu de nível!");
    }
  } while (!lost);
}

void aguardaStart(){
  Serial.println("\n<<< Aguardando Start >>>");
  Serial.println("Digite 'start' para comecar: ");
  String incomingBytes;
  do{
    incomingBytes = "";
    while(!Serial.available()){delay(10);}
    while (Serial.available() > 0 && incomingBytes.length() < 100){
      char a = char(Serial.read());
      if(a != '\n')
        incomingBytes += a;
      delay(10);
    }
    if(incomingBytes.length() > 0 && incomingBytes != "start")
      Serial.println("Opcao invalida!");
  } while(incomingBytes != "start");
}

void setup() {
  Serial.begin(SERIAL_TERMINAL);
  //while(!Serial);
  Serial.println("Iniciou Serial UM!");
    
  // SDCard
  if(!SD.begin()){
    Serial.println("Nao inicializou o SD");
    while(1);
  }
  //Buzzer
  pinMode(BUZZER, OUTPUT);
  // Randomizar botoes
  randomSeed(analogRead(0));
  for (int i = 0; i < NUM_LEDS; i++)
    pinMode(leds[i], OUTPUT);
  Serial.println("Tudo Configurado!");
}

void loop() {
  aguardaConexaoBluetooth();
  Ranking usuario = montaUsuario();
  enviaRankingInicialViaBluetooth();
  aguardaStart();
  Serial.println("STARTOU!");
  

  

  
  level = 0;
  lost = false;
  pontuation = 0;
  jogar();

}
