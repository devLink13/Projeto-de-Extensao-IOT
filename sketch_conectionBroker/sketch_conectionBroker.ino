/*
  -     ENVIAR SMS COM MÓDULO GSM GPRS SIM800L    -
  =================================================
  === BLOG DA ROBOTICA - www.blogdarobotica.com ===
  =================================================
  Autor: Jonas Souza
  E-mail: contato@blogdarobotica.com
  Facebook: facebook.com/blogdarobotica
  Instagram:@blogdarobotica
  YouTube: youtube.com/user/blogdarobotica
  =================================================
  === CASA DA ROBOTICA - www.casadarobotica.com ===
  =================================================
  Facebook: facebook.com/casadaroboticaoficial
  Instagram:@casadarobotica
  ==================================================
*/
#include <SoftwareSerial.h> //Adiciona da biblioteca SoftwareSerial.h
#include <Arduino.h>

SoftwareSerial mySerial(3, 2); //Cria objeto mySerial passando como parâmetro as portas digitais 3 e 2

void updateSerial();

void setup(){
  Serial.begin(9600); //Inicializa a comunicação serial

  mySerial.begin(9600); //Inicializa comunicação entre o SIM800L e o Arduino

  delay(1000);  //Intervalo de 1 segundo

  mySerial.println("AT"); //Teste de conexão 
  updateSerial(); //Chamada da função updateSerial()
  
  mySerial.println("AT+CMGF=1"); //Configuração do modo SMS text
  updateSerial(); //Chamada da função updateSerial()
  
  mySerial.println("AT+CMGS=\"+5553991725057\""); //Número de telefone que irá receber a mensagem, “ZZ” corresponde ao código telefônico do pais e “XXXXXXXXXXX” corresponde ao número de telefone com o DDD
  updateSerial(); //Chamada da função updateSerial()
  
  mySerial.print("TESTANDO O MODULO SIM800L"); //Texto que será enviado para o usúario
  updateSerial(); //Chamada da função updateSerial()
  
  mySerial.write(26); //confirmação das configurações e envio dos dados para comunicação serial.
}

void loop(){
}

void updateSerial() {
  
  while (mySerial.available()) //Verifica se a comunicação serial está disponível
  {
    Serial.write(mySerial.read()); //Realiza leitura serial dos dados de entrada Arduino
  }
  delay(500); //Intervalo de 0,5 segundos
}