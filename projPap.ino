#include <SoftwareSerial.h>

// RX, TX do Bluetooth
SoftwareSerial bluetoo(12, 7); // RX, TX

int AIN1=2; //Motor A sentido 1
int AIN2=3; //Motor A sentido 2
int STBY=4; //Standby do driver
int BIN1=5; //Motor B sentido 1
int BIN2=6; //Motor B sentido 2
int PWMA=10;// enable pin 1
int PWMB=11;// enable pin 2
int pinTrip = 9;  //define ultrasonic ting pin to D12
int pinEcho = 8;   //define ultrasonic echo pin to D13

int Fspeed;
int Lspeed;
int Rspeed;
int velocidade;

char modo = 'M'; // 'M' = Manual, 'A' = Automático

void setup()
 {
  Serial.begin(9600);
  bluetoo.begin(9600);
  Serial.println("HC-06 pronto. Use 1/0/l/r para mover.");

  int i;
  velocidade = 150;
  for (i=2;i<=6;i++) // Ardunio motor driver module
  pinMode(i,OUTPUT); // set digital pins 2,3,4,5,6 as output
  pinMode(10,OUTPUT);// set digital pins 10, 11 as output
  pinMode(11,OUTPUT);
  pinMode(pinTrip,OUTPUT);
  pinMode(pinEcho,INPUT); 

 }
 void ask_pin_F()   // medir a distância à frente
    {
      digitalWrite(pinTrip, LOW);   // emite sinal baixo (LOW) no sensor ultrasónico por 2 microssegundos
      delayMicroseconds(2);
      digitalWrite(pinTrip, HIGH);  // emite sinal alto (HIGH) no sensor ultrasónico por pelo menos 10 microssegundos
      delayMicroseconds(10);
      digitalWrite(pinTrip, LOW);    // termina o pulso com sinal baixo (LOW)
      float Fdistance = pulseIn(pinEcho, HIGH);  // lê o tempo que o sinal leva para voltar (eco)
      Fdistance= Fdistance/5.8/10;       // converte o tempo em distância (em cm)
      Fspeed = Fdistance;              // guarda a distância lida na variável Fspeed (velocidade frontal)
      Serial.print("Fspeed = ");
      Serial.print(Fspeed );
      Serial.println("  cm");   
    }  
    
    
   
  // 2 DC motor rotate CW for 1S, and rotate CCW for 1S
  // rotate CW
  
 void loop() {
  // Comando Bluetooth manual
   //Serial.print("ola: ");
    // 2 DC motor rotate CW for 1S, and rotate CCW for 1S
  // rotate CW
  //front();
  //delay(1000);
  //stop();
  //back(); 
  //delay(1000);
  //stop(); 
  //delay(1000);
  //left(); 
  //delay(1000);
  //stop();
  //delay(1000);
  //right();
  //delay(1000);
  //stop();
  //delay(1000);
    

  if (bluetoo.available()) {
    char cmd = bluetoo.read();
    Serial.print("Comando BT: ");
    Serial.println(cmd);
    if(cmd == 'B')
      velocidade = 100;
    else if(cmd == 'N')
      velocidade = 150;
    else if(cmd == 'F')
      velocidade = 200;
    else if(cmd == 'D')
      velocidade = 300;

    
    
    if (cmd == 'A') {
      modo = 'A';
      stop(); // para evitar movimento contínuo ao mudar de modo
      Serial.println("Modo automático ativado.");
    }
    else if (cmd == 'M') {
      modo = 'M';
      stop();
      Serial.println("Modo manual ativado.");
    }

    if (modo == 'M') {
      switch (cmd) {
        case '1': front(); break;
        case '2': back(); break;
        case '3': left(); break;
        case '4': right(); break;
        case '0': stop(); break;
      }
    }
  }

  if (modo == 'A') {
    loop112();  // chama o modo de desvio automático
  }
}
  
void loop112() 
    {      
      ask_pin_F();            // ler a distância à frente
     if(Fspeed < 10)         // se a distância à frente for menor que 10 cm    
     {
      stop();               // parar o robô
      delay(100);
      back();                // andar para trás durante 0.2 segundos
      delay(200);
      }
      
      if(Fspeed < 25)         // se a distância à frente for menor que 25 cm
      {
        stop(); 
        left(); 
        delay(200);             // clear the output data 
        ask_pin_F();            // read the front distance
        Lspeed = Fspeed; 
        right();
        delay(400);
        ask_pin_F();            //read the front distance 
        Rspeed = Fspeed; 
          
        if(Lspeed > Rspeed)   // se a distância à esquerda for maior que à direita
        {
        left();
        delay(400);
        front();
        }
        
        if(Lspeed <= Rspeed)   // se a distância à esquerda for menor ou igual à da direita
        {
         front();
        } 
        
        if (Lspeed < 10 && Rspeed < 10)   // se as distâncias dos dois lados forem menores que 10 cm
        {
         back();      //anda para tras        
        }          
      }
      else                      
      {
       front();     
      }     
    }    
void front() {
 digitalWrite(STBY, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, velocidade); 
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, velocidade); 
}


void back() {
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, velocidade); 
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, velocidade); 
}

void stop() {
  digitalWrite(STBY,LOW);
}

void left() {
   
    digitalWrite(STBY,HIGH);
    digitalWrite(AIN1,HIGH);
    digitalWrite(AIN2,LOW);
    analogWrite(PWMA,velocidade); 
    digitalWrite(BIN1,LOW);
    digitalWrite(BIN2,HIGH);
    analogWrite(PWMB,velocidade); 
}

void right() {
    digitalWrite(STBY,HIGH);
    digitalWrite(AIN1,LOW);
    digitalWrite(AIN2,HIGH);
    analogWrite(PWMA,velocidade); 
    digitalWrite(BIN1,HIGH); 
    digitalWrite(BIN2,LOW);
    analogWrite(PWMB,velocidade); 
}