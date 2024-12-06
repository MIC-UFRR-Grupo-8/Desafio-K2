const int PIN_BUZZER = 5;
const int PIN_PIR = 23;
const int PIN_BUTTON = 22;

int contador=0;

void setup() {
  pinMode(PIN_BUZZER,OUTPUT);
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_BUTTON,INPUT_PULLUP);
  Serial.begin(115200); /* Define baud rate for serial communication */

  Serial.print("Sensor de movimento\n");
  Serial.print("Ready!\n");
}

void loop() {

  if ( (digitalRead(PIN_PIR) == HIGH) && (digitalRead(PIN_BUTTON) == LOW)) {
            digitalWrite(PIN_LED,HIGH);
            contador++; // Incrementa o contador de usos do dispenser
            Serial.print("Dispenser utilizado. Total de usos: ");
            Serial.println(contador);
            // Aguarda até que o botão seja solto
            while (digitalRead(PIN_BUTTON) == LOW);
        } 
  else{
    digitalWrite(PIN_BUZZER,LOW);
  }
}