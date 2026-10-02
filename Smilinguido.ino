#include <BluetoothSerial.h>

BluetoothSerial SerialBT; 

// Pinos de entrada dos sensores (Pinos ADC1 recomendados)
const int sensores[8] = { 36, 39, 34, 35, 32, 33, 25, 26 };
const int SensorDireito = 27;

// Definindo pinos dos motores
// Motor esquerdo (Motor A)
const int IN1 = 23;
const int IN2 = 22;

// Motor direito (Motor B)
const int IN3 = 21;
const int IN4 = 19;

// Definindo velocidade base dos motores 
int vel_m = 200;

// Valores de constantes PID
float kp = 5.0;
float ki = 0.0;
float kd = 2.0;

// Variáveis de controle PID
float erro = 0;
float erroanterior = 0;
float integral = 0;
float derivada = 0;
float proporcional = 0;
float saidaPID = 0;

void setup() { 
  Serial.begin(115200);
  SerialBT.begin("Seguidor_Linha_Telemetria");

  // Configurando sensores como entrada
  for(int i = 0; i < 8; i++){
    pinMode(sensores[i], INPUT);
  }
  pinMode(SensorDireito, INPUT);

  // Pinos de saída dos motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Garantindo que os pinos de direção secundários fiquem em LOW (para o motor rodar com analogWrite)
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);
}

// Função para enviar dados via Bluetooth
void enviarDados(bool leituras[8]) {
  SerialBT.print("Sensores: ");
  for (int i = 0; i < 8; i++) {
    SerialBT.print(leituras[i]);
    SerialBT.print(" ");
  }
  SerialBT.println();
}

// Função para colocar velocidade nos motores
void mover(unsigned int vel_esq, unsigned int vel_dir) {
  analogWrite(IN1, vel_esq);
  analogWrite(IN3, vel_dir);
}

void loop() {
  // Leitura de cada pino dos sensores
  bool leituraD = digitalRead(SensorDireito);

  bool leituras[8] = {0};
  for (int i = 0; i < 8; i++) {
    leituras[i] = digitalRead(sensores[i]);
  }

  // Envia leituras pela serial bluetooth
  enviarDados(leituras);

  // Seta erro baseado nas leituras dos sensores de linha
  if      (leituras[0]) erro = -3;
  else if (leituras[1]) erro = -2;
  else if (leituras[2]) erro = -1;
  else if (leituras[3]) erro = -0.5;
  else if (leituras[4]) erro = 0.5;
  else if (leituras[5]) erro = 1;
  else if (leituras[6]) erro = 2;
  else if (leituras[7]) erro = 3;

  // Termos PID
  proporcional = erro;
  integral = integral + erro;
  derivada = erro - erroanterior;
  erroanterior = erro; // Atualiza o erro anterior 

  // Cálculo de saída PID
  saidaPID = (kp * proporcional) + (ki * integral) + (kd * derivada);

  // Exemplo de controle dos motores usando a base + saída do PID (NÃO SEI ONDE COLOCAR)
  // int velocidadeEsquerda = vel_m - saidaPID;
  // int velocidadeDireita  = vel_m + saidaPID;

  // Controle manual dos motores
  if      (erro == -3)   mover(150, 255);
  else if (erro == -2)   mover(190, vel_m);
  else if (erro == -1)   mover(150,vel_m);
  else if (erro == -0.5) mover(190,vel_m);
  else if (erro == 0.5)  mover(vel_m,vel_m);
  else if (erro == 1)    mover(vel_m,190);
  else if (erro == 2)    mover(vel_m, 150);
  else if (erro == 3)    mover(vel_m, 150);

  delay(10);
}
