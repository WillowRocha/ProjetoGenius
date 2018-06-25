#include <SPI.h>
#include <SD.h>
#include "SdCard.h" //It already includes de JsonParser
#include "Musica.h"
#include <String.h>

//Comunication
#define SERIAL_BLUETOOTH 115200
#define SERIAL_TERMINAL 9600
#define NUM_LEDS 4 // Numero de Leds instalados
#define BUZZER 49 //Pino do Buzzer
int leds[NUM_LEDS]    = {2, 3, 4, 5};
int buttons[NUM_LEDS] = {6, 7, 8, 9};
int tons[NUM_LEDS]    = {nota(n_C, 3), nota(n_D, 3), nota(n_E, 3), nota(n_F, 3)};
// Para aumentar o numero de Leds instalados,
// basta setar NUM_LEDS e inserir os numeros
// dos pinos no leds[]; Nao necessitando
// eles estarem em portas consecutivas.

String recebeDados(int minimo, int limite) {
  String dados = "";
  while (!Serial.available()) {
    delay(10);
  }
  do {
    while (Serial.available() > 0) {
      char a = char(Serial.read());
      if (a != '\n' && dados.length() < limite) {
        dados += a;
      }
      delay(10);
    }
  } while (dados.length() < minimo);
  return dados;
}

String recebeNomeJogador() {
  Serial.println("Informe o nome do Jogador");
  return recebeDados(3, 20);
}

Ranking montaUsuario() {
  Ranking usuario;
  usuario.id = buscaProximoId();
  usuario.nome = recebeNomeJogador();
  return usuario;
}

void aguardaConexaoBluetooth() {
  if (!Serial.available()) {
    Serial.println("Bluetooth nao disponivel, aguardando...");
  }
  recebeDados(0,0);
}

void enviaRankingInicialViaBluetooth() {
  Ranking rank[RANK_SIZE];
  int size_r = buscaRankingNoArquivo(rank);
  JsonObject& ranking = parseRankingToJson(rank, size_r);
  ranking.printTo(Serial);
}

void enviaRankingFinalViaBluetooth(Ranking usuario) {
  Ranking rank[RANK_SIZE];
  int size_r = buscaRankingNoArquivo(rank);
  JsonObject& ranking = parseRankingFinalToJson(usuario, rank, size_r);
  ranking.printTo(Serial);
}

void acendeLeds(int sequence[], int level) {
  for (int i = 0; i < level; i++) {
    digitalWrite(leds[sequence[i]], HIGH);
    tone(BUZZER, tons[sequence[i]]);
    delay(500);
    noTone(BUZZER);
    digitalWrite(leds[sequence[i]], LOW);
  }
}

boolean verificaBotoesClicados(int sequence[], int level) {
  int clicked[100];
  boolean lost = false;
  int n_clicked = 0;
  int pushed = 0;
  do {
    pushed = 0;
    for (int i = 0; i < NUM_LEDS && !pushed; i++) {
      if (digitalRead(buttons[i]) == HIGH) {
        clicked[n_clicked++] = i;
        pushed = 1;
        tone(BUZZER, tons[i]);
        digitalWrite(leds[i], HIGH);
        delay(500);
        noTone(BUZZER);
        digitalWrite(leds[i], LOW);
      }
      if (pushed && clicked[n_clicked - 1] != sequence[n_clicked - 1]) {
        lost = true;
      }
    }
    delay(25);
  } while (!lost && n_clicked < level);
  delay(500);
  return lost;
}

void mandaMensagemDeStatus(boolean lost) {
  if (!lost) {
    Serial.println("GANHOU");
  } else {
    Serial.println("PERDEU");
  }
}

int jogar() {
  int sequence[100]; //Sequencia de leds a piscas
  int level = 0;

  boolean lost = false;
  int pontuation = 0;

  do {
    sequence[level] = random(5000) % NUM_LEDS;
    level++;
    Serial.print("Voce esta no nivel: ");
    Serial.println(level);

    acendeLeds(sequence, level);
    lost = verificaBotoesClicados(sequence, level);
    mandaMensagemDeStatus(lost);
    if (!lost && level == 100) {
      return level;
    }
  } while (!lost);
  return level - 1;
}

void aguardaStart() {
  Serial.println("Digite 'start' para comecar: ");
  String dados;
  do {
    dados = recebeDados(5, 5);
    if (dados.length() > 0 && dados != "start")
      Serial.println("Opcao invalida!");
  } while (dados != "start");
}

void setup() {
  Serial.begin(SERIAL_TERMINAL);
  while (!Serial);
  Serial.print("Iniciou Serial");

  if (!SD.begin()) {
    Serial.println("Nao inicializou o SD");
    while (1);
  }
  pinMode(BUZZER, OUTPUT);
  randomSeed(analogRead(0));
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT);
  }
  Serial.println("Tudo Configurado!");
  //tocaMusica(brilha_brilha_estrelinha(), BUZZER);
}

void loop() {
  aguardaConexaoBluetooth();
  Ranking usuario = montaUsuario();
  enviaRankingInicialViaBluetooth();
  aguardaStart();
  int level = jogar();
  usuario.pontuacao = level;
  adiciona_jogador_ranking(usuario);
  enviaRankingFinalViaBluetooth(usuario);
}

