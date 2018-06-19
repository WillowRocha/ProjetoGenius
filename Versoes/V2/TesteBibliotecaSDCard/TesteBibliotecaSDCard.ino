#include "SDCard.h"

void testaRanking(){
  Ranking rank2[RANK_SIZE];
  Serial.println("Vai ler...");
  int tam = le_arquivo_e_salva_no_ranking(rank2);
  if(tam){
    Serial.print("O tamanho do ranking eh: ");
    Serial.println(tam);
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
  }
  testaRanking();
  Ranking rank[RANK_SIZE];
  rank[0].id = 1;
  rank[0].nome = "Jose";
  rank[0].pontuacao = 20;
  if(adiciona_jogador_ranking(rank[0])){
    Serial.println("Sucesso 0");
  }
  testaRanking();
  rank[1].id = 2;
  rank[1].nome = "Joao";
  rank[1].pontuacao = 50;
  if(adiciona_jogador_ranking(rank[1])){
    Serial.println("Sucesso 1");
  }
  testaRanking();
  rank[2].id = 3;
  rank[2].nome = "Daniel";
  rank[2].pontuacao = 23;
  if(adiciona_jogador_ranking(rank[2])){
    Serial.println("Sucesso 2");
  }
  testaRanking();
}

void loop() {}
