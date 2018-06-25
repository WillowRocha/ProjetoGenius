#include "SDCard.h"

void enviaRankingInicialViaBluetooth() {
  Ranking rank[RANK_SIZE];
  int size_r = buscaRankingNoArquivo(rank);
  JsonObject& ranking = parseRankingToJson(rank, size_r);
  Serial.print("Size: ");
  Serial.println(size_r);
  ranking.printTo(Serial);
  Serial.println("");
}

void testaRanking(){
  Ranking rank2[RANK_SIZE];
  Serial.println("Vai ler...");
  int tam = buscaRankingNoArquivo(rank2);
  if(tam){
    enviaRankingInicialViaBluetooth();
  } else {
    Serial.println("Erro ao ler o ranking");
  }
}

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
   if(!SD.begin()){
    Serial.println("Nao inicializou o SD");
    while(1);
  } else {
    Serial.println("Inicou SD");
  }
  int id;
  testaRanking();
  Ranking rank[3];
  rank[0].nome = "Jose";
  rank[0].pontuacao = 20;
  if(adiciona_jogador_ranking(rank[0])){
    Serial.println("Sucesso 0");
  }
  testaRanking();
  rank[1].nome = "Joao";
  rank[1].pontuacao = 50;
  if(adiciona_jogador_ranking(rank[1])){
    Serial.println("Sucesso 1");
  }
  testaRanking();
  rank[2].nome = "Daniel";
  rank[2].pontuacao = 23;
  if(adiciona_jogador_ranking(rank[2])){
    Serial.println("Sucesso 2");
  }
  testaRanking();
}

void loop() {}
