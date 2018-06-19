

//NECESSÁRIO
// 4 Leds - pinos 10, 11, 12, 13
// Teclado - pinos 2, 3, 4, 5, 6, 7, 8, 9
// Display
// Bluetooh -

// Para aumentar o número de Leds instalados,
// basta setar NUM_LEDS e inserir os números
// dos pinos no leds[]; Não necessitando
// eles estarem em portas consecutivas.
const int NUM_LEDS = 8, OFFSET_CHAR = 50;
int leds[NUM_LEDS] = {13, 12, 11, 10, 9, 8, 7, 6};

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*' , '0' , '#', 'D'}
};
byte rowPins[ROWS] = {14, 15, 16, 17};
byte colPins[COLS] = {18, 19, 20, 21};

long buttons[100];
long randButton;
int level, clicked, buttons_pos;
boolean lost;
long pontuation;

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  for (int i = 0; i < NUM_LEDS; i++)
    pinMode(leds[i], OUTPUT);

}

void loop() {
  level = 0;
  lost = false;
  pontuation = 0;
  
  do {
    buttons_pos = 0;
    level++;
    Serial.print("Você está no Nível: ");
    Serial.println(level);

    for (int i = 0; i < level; i++) {
      buttons[i] = random(0, NUM_LEDS);
      digitalWrite(leds[buttons[i]], HIGH);
      delay(1000);
      digitalWrite(leds[buttons[i]], LOW);
    }
  
    for (int i = 0; i < level && !lost; i++) {
      do {
        clicked = kpd.getKey();
      } while (clicked == NO_KEY);
      Serial.println(clicked);
      if ((clicked-OFFSET_CHAR)-1 != buttons[i]) {
        lost = true;
        Serial.println("Perdeu");
      } else {
        Serial.println("Correto");
      }
    }
    if (!lost) {
      level++;
      Serial.println("");
      Serial.println("Parabéns! Você ganhou e agora subiu de nível!");
    }
  } while (!lost);
}
