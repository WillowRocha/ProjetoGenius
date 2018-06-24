#include <SPI.h>
#include <SD.h>
#include "SdCard.h" //It already includes de JsonParser
#include "Musica.h"

//Comunication
#define SERIAL_BLUETOOTH 115200
#define SERIAL_TERMINAL 9600
int current_serial = SERIAL_BLUETOOTH;
#define NUM_LEDS 4 // Numero de Leds instalados
#define BUZZER 49 //Pino do Buzzer
int leds[NUM_LEDS]    = {2, 3, 4, 5};
int buttons[NUM_LEDS] = {6, 7, 8, 9};
int tons[NUM_LEDS]    = {nota(n_C, 3), nota(n_D, 3), nota(n_E, 3), nota(n_F, 3)};
// Para aumentar o número de Leds instalados,
// basta setar NUM_LEDS e inserir os números
// dos pinos no leds[]; Não necessitando
// eles estarem em portas consecutivas.


String recebeNomeJogador() {
  Serial.println("Informe o nome do Jogador");
  String incomingBytes;

  do {
    Serial.println("Verifica Serial");
    while (!Serial.available()) {
      delay(10);
    }
    Serial.println("Serial ta disponivel");
    incomingBytes = "";
    while (Serial.available() > 0) {
      Serial.println("Lendo");
      char a = char(Serial.read());
      if (a != '\n') {
        Serial.print(a);
        incomingBytes += a;
      }
      Serial.println("");
      delay(10);
    }
    Serial.print("IncomingBytes: ");
    Serial.println(incomingBytes);
    if (incomingBytes.length() < 3) {
      Serial.println("Minimo 3 caracteres");
    }
    if (incomingBytes.length() > 20) {
      Serial.println("Numero maximo de caracteres alcancado. Maximo 20 caracteres");
    }
  } while (incomingBytes.length() < 3 || incomingBytes.length() > 20);

  return incomingBytes;
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
  while (!Serial.available()) {
    delay(10);
  }

  while (Serial.available() > 0) {
    char a = Serial.read();
    delay(10);
  }
}

void enviaRankingInicialViaBluetooth() {
  Serial.println("Enviando Ranking inicial...");
  Ranking rank[RANK_SIZE];
  int size_r = buscaRankingNoArquivo(rank);
  JsonObject& ranking = parseRankingToJson(rank, size_r);
  ranking.printTo(Serial);
}

void enviaRankingFinalViaBluetooth(Ranking usuario) {
  Serial.println("Enviando Ranking final...");
  Ranking rank[RANK_SIZE];
  int size_r = buscaRankingNoArquivo(rank);
  JsonObject& ranking = parseRankingFinalToJson(usuario, rank, size_r);
  ranking.printTo(Serial);
}

void acendeLeds(int sequence[], int level) {
  for (int i = 0; i < level; i++) {
    Serial.print("Acendeu led: ");
    Serial.println(sequence[i]);
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
  Serial.println("Vai verificar no loop!");
  do {
    pushed = 0;
    for (int i = 0; i < NUM_LEDS && !pushed; i++) {
      if (digitalRead(buttons[i]) == HIGH) {
        Serial.print("Clicou no pino: ");
        Serial.println(buttons[i]);
        clicked[n_clicked++] = i;
        Serial.print("Posicao botao: ");
        Serial.println(i);
        pushed = 1;
        tone(BUZZER, tons[i]);
        digitalWrite(leds[i], HIGH);
        delay(500);
        noTone(BUZZER);
        digitalWrite(leds[i], LOW);
      }
      if (pushed && clicked[n_clicked - 1] != sequence[n_clicked - 1]) {
        Serial.println("Clicou e perdeu");
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
    sequence[level] = random(5000);
    sequence[level] = sequence[level] % NUM_LEDS;
    level++;
    Serial.print("Você está no Nível: ");
    Serial.println(level);

    Serial.println("Vai acender leds");
    acendeLeds(sequence, level);
    Serial.println("Acendeu leds");
    lost = verificaBotoesClicados(sequence, level);
    Serial.println("Verificou botoes");
    mandaMensagemDeStatus(lost);
    Serial.println("Mandou mensagem de status");
    if (!lost && level == 100) {
      lost = true;
    }
  } while (!lost);
  return level - 1;
}

void aguardaStart() {
  Serial.println("\n<<< Aguardando Start >>>");
  Serial.println("Digite 'start' para comecar: ");
  String incomingBytes;
  do {
    incomingBytes = "";
    while (!Serial.available()) {
      delay(10);
    }
    while (Serial.available() > 0 && incomingBytes.length() < 100) {
      char a = char(Serial.read());
      if (a != '\n')
        incomingBytes += a;
      delay(10);
    }
    if (incomingBytes.length() > 0 && incomingBytes != "start")
      Serial.println("Opcao invalida!");
  } while (incomingBytes != "start");
}

void setup() {
  Serial.begin(current_serial);
  while(!Serial);
  Serial.println("Iniciou Serial UM!");

  // SDCard
  if (!SD.begin()) {
    Serial.println("Nao inicializou o SD");
    while (1);
  }
  //Buzzer
  pinMode(BUZZER, OUTPUT);
  // Randomizar botoes
  randomSeed(analogRead(0));
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT);
  }
  Serial.println("Tudo Configurado!");

  //tocaMusica(brilha_brilha_estrelinha(), BUZZER);
}

void loop() {
  Serial.println("Entrou no loop");
  aguardaConexaoBluetooth();
  Ranking usuario = montaUsuario();
  enviaRankingInicialViaBluetooth();
  aguardaStart();
  jogar();
  adiciona_jogador_ranking(usuario);
  enviaRankingFinalViaBluetooth(usuario);
}
