#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(37, 39, 41, 43, 45); //Parâmetros: RST, CE, DC, DIN, CLK

void setup() {
  Serial.begin(9600);
  display.begin();
  display.setContrast(50); //Ajusta o contraste do display
  display.clearDisplay();   //Apaga o buffer e o display
  display.setTextSize(1);  //Seta o tamanho do texto
  //display.setTextColor(BLACK); //Seta a cor do texto
  display.setCursor(0,0);  //Seta a posição do cursor
  display.println("S e T!");  

  //Texto invertido - Branco com fundo preto
  display.setTextColor(WHITE, BLACK); 

  display.println("Arq II");

  display.setTextSize(2); 
  display.setTextColor(WHITE);
  display.print("Arduino");
  display.display();
  delay(5000);

}

void loop() {
  display.clearDisplay();   //Apaga o buffer e o display
   display.setTextColor(WHITE, BLACK);
  display.setTextSize(2); 
  display.setTextColor(WHITE);
  display.println("Funcionou!!!!!");
  display.display();
  delay(2000);

}
