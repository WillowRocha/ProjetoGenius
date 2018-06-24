/*
  Botao
 
 Liga e desliga um LED conectado ao pino digital 13 quando pressionado um botao conectado ao pino 2.
 
 O Circuito:
 * LED conectado ao pino 13 e ao terra
 * botao conectado ao pino 2 desde 5V
 * resistor de 10K conectado ao pino 2 desde o terra
*/

// constantes nao sao alteradas. 
// Sao usadas aqui para definir os numeros dos pinos:
const int ledOutro = 11;
const int ledAmarelo =  12;      // o numero do pino do LED
const int ledVerde = 13;
const int botaoOutro = 7;
const int botaoAmarelo = 8;
const int botaoVerde = 9;


// variaveis que devem mudar:
int buttonState = 0;         // variavel para ler o estado do botao

void setup() {
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledOutro, OUTPUT);
  pinMode(botaoAmarelo, INPUT);
  pinMode(botaoVerde, INPUT);
  pinMode(botaoOutro, INPUT);
}

void loop(){
  
  if (digitalRead(botaoAmarelo) == HIGH) {    
    digitalWrite(ledAmarelo, HIGH);  
  } else {
    digitalWrite(ledAmarelo, LOW);
  }
  if (digitalRead(botaoVerde) == HIGH) {    
    digitalWrite(ledVerde, HIGH);  
  } else {
    digitalWrite(ledVerde, LOW);
  }
  if (digitalRead(botaoOutro) == HIGH) {    
    digitalWrite(ledOutro, HIGH);  
  } else {
    digitalWrite(ledOutro, LOW);
  }
}
