#define TRIGGER_PIN 13
#define ECHO_PIN 12
#define BUTTON_PIN 14

const int PIN_BUZZER = 5;
const int PIN_LED = 2;
const int PIN_PIR = 23;
long duration;
int distancia;
int contador = 0;

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_PIR, INPUT);

  Serial.println("Sistema de Monitoramento de Dispenser Iniciado");
}

void loop() {

  // Gera um pulso de 10 microssegundos no pino Trigger para iniciar a medição
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Lê a duração do pulso no pino Echo
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calcula a distância em centímetros
  distancia = duration * 0.034 / 2;
  //-------------------------------------------------------------------

  Serial.print("DISTANCIA ");
  Serial.println(distancia);

  if (digitalRead(PIN_PIR) == HIGH) { //PIR
    digitalWrite(PIN_LED,HIGH);

  Serial.println("PESSOA DETECTADA");

    if (distancia > 0 && distancia <= 20) {  //detecta até 20 cm //ULTRASSONICO
      Serial.println("Pessoa detectada próxima ao dispenser");

      // Verifica se o botão foi pressionado para simular o uso do dispenser
      if (digitalRead(BUTTON_PIN) == LOW) {  // LOW indica que o botão foi pressionado //BOTAO
        delay(50);                           // debounce
        if (digitalRead(BUTTON_PIN) == LOW) {
          digitalWrite(PIN_BUZZER, HIGH);
          contador++;  // Incrementa o contador de usos do dispenser
          Serial.print("Dispenser utilizado. Total de usos: ");
          Serial.println(contador);

          while (digitalRead(BUTTON_PIN) == LOW);
        }
      }
      digitalWrite(PIN_BUZZER, LOW);
    }


    // Aguarda até que o botão seja solto
    while (digitalRead(BUTTON_PIN) == LOW);
  } else {
    
    digitalWrite(PIN_LED, LOW);
  }


  delay(100);  // Aguarda um pouco antes da próxima verificação
}
