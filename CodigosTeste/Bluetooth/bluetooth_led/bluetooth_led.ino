
char incomingByte; // Char recebido pelo Serial.
int LED = 13; // Pino do LED
void setup() {
        pinMode(13, LED);
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}


void loop() {
        
        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();
               // Serial.println(incomingByte);
                if (incomingByte == 'L'){
                  Serial.println("LED: Ligado.");
                  digitalWrite(13, HIGH);
                  
                }
                if (incomingByte == 'D'){
                  digitalWrite(13, LOW);
                  Serial.println("LED: Desligado.");
                }
        }
}

