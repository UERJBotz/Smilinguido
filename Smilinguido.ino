
//definindo pinos de entrada ESP32D
const int Sensor1 = 36;
const int Sensor2 = 39;
const int Sensor3 = 34; 
const int Sensor4 = 35;
const int Sensor5 = 32;
const int Sensor6 = 33;
const int Sensor7 = 25;
const int Sensor8 = 26;
const int SensorDireito = 27;

//Definindo pinos dos motores
//motor esquerdo motor A
const int IN1 = 23;
const int IN2 = 22;

//motor direito MOTOR B
const int IN3 = 21;
const int IN4 = 19;

//definindo velocidade dos motores 
int vel_m = 200;

//Valores de constante
float kp = 5.0;
float ki = 0;
float kd = 2.0;

//valor inicial das inicias de controle pid
float erroanterior = 0;
float erro = 0;
float integral = 0;
float derivada = 0;
float proporcional = 0;
float saidaPID = 0;
void setup() { 
//Os sensores vão enviar informação para os pinos nomeados 
pinMode(Sensor1,INPUT);
pinMode(Sensor2,INPUT);
pinMode(Sensor3,INPUT);
pinMode(Sensor4,INPUT);
pinMode(Sensor5,INPUT);  
pinMode(Sensor6,INPUT);
pinMode(Sensor7,INPUT);
pinMode(Sensor8,INPUT);
//pinMode(SensorDireito,INPUT);

//pinos de saida motor
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);

//definindo o sentido do motor como frente
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
}

void loop() {
// termos pid
proporcional = erro;
integral = integral + erro;
derivada = erro - erroanterior;

//leitura de cada pino Sr's para ver o que está acontecendo 
int sr11 = digitalRead(Sensor1);
int sr22 = digitalRead(Sensor2);
int sr33 = digitalRead(Sensor3);
int sr44 = digitalRead(Sensor4);
int sr55 = digitalRead(Sensor5); 
int sr66 = digitalRead(Sensor6);
int sr77 = digitalRead(Sensor7);
int sr88 = digitalRead(Sensor8);
int sensorD = digitalRead(SensorDireito);

//condição para leitura de erro, se um dos sensores estiver ligado leia o erro..
  if(sr11== HIGH)
      erro = -3;

  else if(sr22== HIGH)
       erro = -2 ;

  else if(sr33 == HIGH)
      erro = -1;

  else if(sr44 == HIGH)
      erro = -0.5 ;    

  else if (sr55 == HIGH)
      erro = 0.5 ;

  else if(sr66 == HIGH)
    erro = 1 ;

  else if(sr77 == HIGH)
    erro = 2 ;

  else if (sr88 == HIGH)
    erro = 3;   

  //calculo de saida PID
   saidaPID = (kp*proporcional) + (ki*integral) + (kd*derivada);

  //controlando a vel das rodas de acordo com a leitura de cada erro 
 
  if(erro== -3){
    analogWrite(IN1,100);
    analogWrite(IN3,vel_m);
  }
  else if(erro== -2){
    analogWrite(IN1,190);
    analogWrite(IN3,vel_m);
  }
  else if(erro== -1){
    analogWrite(IN1,150);
    analogWrite(IN3,vel_m);
  }
  else if(erro==- 0.5){
    analogWrite(IN1,190);
    analogWrite(IN3,vel_m);
  }
  else if(erro== 0.5){
    analogWrite(IN1,vel_m);
    analogWrite(IN3,vel_m);
  }

  else if(erro== 1){
    analogWrite(IN1,vel_m);
    analogWrite(IN3,190);
  }

  else if(erro== 2){
    analogWrite(IN1,vel_m);
    analogWrite(IN3,150);
  }

  else if(erro==3){
   analogWrite(IN1,vel_m);
   analogWrite(IN3,150);
  }
}

