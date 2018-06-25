#include <SPI.h>
#include <SD.h>
#include "Json.h"

#define FILE_NAME "shit.txt"
#define SEPARATOR ";"
#define RANK_SIZE 25
File rankingFile;

struct ranking {
  int id;
  String nome;
  int pontuacao;
  int pos_ranking;
};
typedef struct ranking Ranking;

JsonObject& parseRankingToJson(Ranking* ranking, int ranking_size){
  const size_t bufferSize = JSON_ARRAY_SIZE(ranking_size) + JSON_OBJECT_SIZE(3);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  
  JsonObject& root = jsonBuffer.createObject();
  JsonArray& rank = root.createNestedArray("rankingArray");
  
  for(int i = 0; i < ranking_size; i++){
    JsonObject& pos = jsonBuffer.createObject();
    pos["id"] = ranking[i].id;
    pos["nome"] = ranking[i].nome;
    pos["pontuacao"] = ranking[i].pontuacao;
    rank.add(pos);
  }
  return root;
}

int parseRankingFromJson(Ranking* ranking, String texto, int tam_texto){
  const size_t bufferSize = tam_texto+1;
  DynamicJsonBuffer jsonBuffer(bufferSize);
  
  JsonObject& root = jsonBuffer.parseObject(texto);
  
  JsonArray& rank = root["rankingArray"];
  int tam = rank.size();
  
  int rank_size = 0;
  while(rank_size < tam){
    JsonObject& pos = rank[rank_size];
    int id = pos["id"];
    String nome = pos["nome"];
    int pontuacao = pos["pontuacao"];
    ranking[rank_size].id = id;
    ranking[rank_size].nome = nome;
    ranking[rank_size].pontuacao = pontuacao;
    rank_size++;
  }
  return rank_size;
}

JsonObject& parseRankingFinalToJson(Ranking usuario, Ranking* ranking, int ranking_size){
  const size_t bufferSize = JSON_ARRAY_SIZE(ranking_size) + JSON_OBJECT_SIZE(3);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  
  JsonObject& root = jsonBuffer.createObject();
 
  JsonObject& user = jsonBuffer.createObject();
  user["id"] = usuario.id;
  user["nome"] = usuario.nome;
  user["pontuacao"] = usuario.pontuacao;
  
  JsonObject& ranking_all = parseRankingToJson(ranking, ranking_size);

  root["usuario"] = user;
  root["ranking"] = ranking_all;
  return root;
}

int buscaRankingNoArquivo(Ranking* ranking){
  rankingFile = SD.open(FILE_NAME);
  if(rankingFile){
    String texto_lido = "";
    int tam_texto = 0;
    while(rankingFile.available()){
      char a = rankingFile.read();
      texto_lido += a;
      tam_texto++;
    }
    rankingFile.close();
    if(tam_texto){
      return parseRankingFromJson(ranking, texto_lido, tam_texto);
    }
  }
  return 0;
}

int buscaProximoId(){
  Ranking* rank;
  return 1 + buscaRankingNoArquivo(rank);
}

int salva_ranking_no_arquivo(Ranking *ranking, int ranking_size){
  if (SD.exists(FILE_NAME)) {
    boolean st = SD.remove(FILE_NAME);
    if(st){
      Serial.println("Arquivo deletado");
    } else {
      Serial.println("Falha ao remover");
    }
  } else {
    Serial.println("Arquivo não existe");
  }
  rankingFile = SD.open(FILE_NAME, FILE_WRITE);
  if(rankingFile){
    Serial.println("Abriu pra escrita");
    JsonObject& root = parseRankingToJson(ranking, ranking_size);
    Serial.println("Paseou para o Json");
    root.printTo(rankingFile);
    Serial.println("Escreveu no arquivo");
    rankingFile.close();
    Serial.println("Fechou o arquivo e vai retornar");
    return 1;
  }
  Serial.println("Falha ao abrir arquivo!");
  return 0;
}

int adiciona_jogador_ranking(Ranking user){
  Ranking ranking[RANK_SIZE];
  int ranking_size = buscaRankingNoArquivo(ranking);
  int id = buscaProximoId();
  Serial.println(id);
  ranking[ranking_size].id = id;
  ranking[ranking_size].nome = user.nome;
  ranking[ranking_size++].pontuacao = user.pontuacao;
  return salva_ranking_no_arquivo(ranking, ranking_size);
}


