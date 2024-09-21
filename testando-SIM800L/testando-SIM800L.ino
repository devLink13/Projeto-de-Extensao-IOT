#include <Arduino.h>

#include <SoftwareSerial.h>

SoftwareSerial sim800(10,11); // cria uma instancia de softwareserial com sim800



//declaração de funções
String enviarAT(String comandoAT, bool resposta = false);


void setup() {
  Serial.begin(9600);
  sim800.begin(9600);
  delay(100);

  Serial.print("TESTANDO SIM 800L, resposta: ");
  String codigo = enviarAT("AT", true);
  Serial.println(codigo);



}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
String enviarAT(String comandoAT, bool resposta = false){
 
  sim800.println(comandoAT); // envia o comando AT
  delay(1000);
  
  //se houver alguma resposta....
  if (sim800.available()) {
    String leitura_AT = sim800.readString();
    leitura_AT.trim();

    if (resposta == true){
      return leitura_AT; //caso queira, retorna a leitura
    }

    else{
      return;
    }
  }
}