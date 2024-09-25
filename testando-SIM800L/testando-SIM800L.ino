#define TINY_GSM_MODEM_SIM800
#include <Wire.h>
#include <SPI.h>
#include <PubSubClient.h>
#include <TinyGsmClient.h>
#include <SSLClient.h>

// Definições do módulo SIM800L
#define MODEM_RST 7
#define MODEM_PWRKEY 6
#define MODEM_POWER_ON 5
#define MODEM_TX 10
#define MODEM_RX 11
#define SerialMon Serial
#define SerialAT Serial1

// Definições da rede
const char apn[] = "your_apn";
const char user[] = "your_user";
const char pass[] = "your_pass";

// Definições do broker MQTT
const char* broker = "your_broker_address";
const int port = 8883;
const char* mqttUser = "your_mqtt_user";
const char* mqttPassword = "your_mqtt_password";

// Variável para o certificado CA
const char* TAs = "-----BEGIN CERTIFICATE-----\n...";

// Inicialização do cliente GSM e MQTT
TinyGsm modem(SerialAT);
TinyGsmClientSecure gsmClient(modem);
SSLClient client(gsmClient, TAs, sizeof(TAs) / sizeof(TAs[0]), BR_SSL_BUFSIZE_BIDI, 512, SSLClient::DebugLevel::SSL_DEBUG_OFF);
PubSubClient mqtt(client);

void connectMQTT();
void mqttCallback(char* topic, byte* payload, unsigned int length);

void setup() {
  // Inicialização das portas seriais
  SerialMon.begin(115200);
  delay(10);
  SerialAT.begin(9600);
  delay(3000);

  // Inicialização do módulo SIM800L
  pinMode(MODEM_PWRKEY, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_PWRKEY, LOW);
  digitalWrite(MODEM_POWER_ON, HIGH);
  delay(1000);
  digitalWrite(MODEM_PWRKEY, HIGH);
  delay(2000);
  digitalWrite(MODEM_PWRKEY, LOW);
  delay(3000);

  // Conexão à rede
  SerialMon.print("Conectando à rede...");
  modem.restart();
  modem.gprsConnect(apn, user, pass);
  SerialMon.println("Conectado!");

  // Configuração do cliente MQTT
  client.setCACert(TAs);
  mqtt.setServer(broker, port);
  mqtt.setCallback(mqttCallback);

  // Conexão ao broker MQTT
  connectMQTT();
}

void loop() {
  if (!mqtt.connected()) {
    connectMQTT();
  }
  mqtt.loop();
}

void connectMQTT() {
  while (!mqtt.connected()) {
    SerialMon.print("Conectando ao broker MQTT...");
    if (mqtt.connect("ArduinoClient", mqttUser, mqttPassword)) {
      SerialMon.println("Conectado!");
      mqtt.subscribe("your_topic");
    } else {
      SerialMon.print("Falha na conexão, rc=");
      SerialMon.print(mqtt.state());
      delay(5000);
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  SerialMon.print("Mensagem recebida [");
  SerialMon.print(topic);
  SerialMon.print("]: ");
  for (unsigned int i = 0; i < length; i++) {
    SerialMon.print((char)payload[i]);
  }
  SerialMon.println();
}
