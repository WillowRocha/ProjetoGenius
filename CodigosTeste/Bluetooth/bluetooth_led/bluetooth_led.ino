
char incomingByte; // Char recebido pelo Serial.
int LED = 2; // Pino do LED
void setup() {
        pinMode(LED, OUTPUT);
        Serial.begin(115200);     // opens serial port, sets data rate to 9600 bps
}


void loop() {
        
        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();
               // Serial.println(incomingByte);
                if (incomingByte == 'L'){
                  Serial.println("LED: Ligado.");
                  digitalWrite(LED, HIGH);
                  
                }
                if (incomingByte == 'D'){
                  digitalWrite(LED, LOW);
                  Serial.println("LED: Desligado.");
                }
        }
}

