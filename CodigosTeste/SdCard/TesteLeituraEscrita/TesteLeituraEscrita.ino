#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.print("Inicializa o SD card...");

  if (!SD.begin()) {
    Serial.println("Erro ao abrir SD.");
    return;
  }


  myFile = SD.open("Teste.txt", FILE_WRITE);

  if (myFile) {
    myFile.println("Uma Frase qualquer no aquivo");
    myFile.println("Uma Outra frase no aquivo");
    myFile.close();
  }
  else {
    Serial.println("Nao foi possivel abrir o arquivo");
  }

  myFile = SD.open("Teste.txt");
  if (myFile) {
    Serial.println("Conteudo de Teste.txt:");
    Serial.write(myFile.fscanf("%s", 5);
    /*while (myFile.available()) {
      Serial.write(myFile.read());
    }*/
    myFile.close();
  }
  else {
    Serial.println("Nao pude abrir o arquivo.");
  }
}

void loop() {}
