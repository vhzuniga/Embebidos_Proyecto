#include <Arduino.h>
#include <U8g2lib.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <apwifieeprommode.h> // Archivo con las funciones intentoconexion y loopAP

// Configuración de sensores y pines
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
#define SOIL_SENSOR_1_PIN 32
#define SOIL_SENSOR_2_PIN 33
#define ENA_1_PIN 18
#define IN1_1_PIN 19
#define ENB_2_PIN 27
#define IN3_2_PIN 14
#define LDR_PIN 36

// Configuración MQTT
const char* mqtt_server = "eb80f84641694b1183650454d1726b0d.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "vhzuniga";
const char* mqtt_password = "Sandrita2.";
const char* mqtt_topic_data = "plantas/datos";
const char* mqtt_topic_manual = "plantas/manual";
const char* mqtt_topic_config = "plantas/config";

WiFiClientSecure espClient;
PubSubClient client(espClient);

// Variables de configuración de humedad mínima y máxima
float soil1_min = 20, soil1_max = 60;
float soil2_min = 20, soil2_max = 60;




// Pantalla OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

// Variables para reconexión MQTT
unsigned long lastReconnectAttempt = 0;

// Reconexión MQTT con temporizador
void reconnectMQTT() {
  if (!client.connected()) {
    unsigned long now = millis();
    if (now - lastReconnectAttempt > 5000) { // Intentar cada 5 segundos
      lastReconnectAttempt = now;
      Serial.println("Intentando conectar a MQTT...");
      if (client.connect("ESP32_Client", mqtt_user, mqtt_password)) {
        Serial.println("Conexión exitosa a MQTT");
        client.subscribe(mqtt_topic_config);
        client.subscribe(mqtt_topic_manual);
      } else {
        Serial.print("Error al conectar a MQTT. Estado: ");
        Serial.println(client.state());
      }
    }
  }
}

// Manejo de mensajes MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Mensaje recibido en ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(message);

  if (String(topic) == mqtt_topic_config) {
    StaticJsonDocument<256> doc;
    deserializeJson(doc, message);

    soil1_min = doc["Planta 1"]["min"] | soil1_min;
    soil1_max = doc["Planta 1"]["max"] | soil1_max;
    soil2_min = doc["Planta 2"]["min"] | soil2_min;
    soil2_max = doc["Planta 2"]["max"] | soil2_max;

    Serial.println("Configuración actualizada:");
    Serial.printf("Planta 1: min %.2f, max %.2f\n", soil1_min, soil1_max);
    Serial.printf("Planta 2: min %.2f, max %.2f\n", soil2_min, soil2_max);
  } else if (String(topic) == mqtt_topic_manual) {
    StaticJsonDocument<128> doc;
    deserializeJson(doc, message);
    String bomba = doc["bomba"];
    if (bomba == "bomba1") {
      Serial.println("Encendiendo manualmente bomba 1");
      digitalWrite(IN1_1_PIN, HIGH); // Dirección fija
      analogWrite(ENA_1_PIN, 255);  // Máxima potencia PWM
      delay(5000);
      analogWrite(ENA_1_PIN, 0);    // Apagar PWM
    } else if (bomba == "bomba2") {
      Serial.println("Encendiendo manualmente bomba 2");
      digitalWrite(IN3_2_PIN, HIGH); // Dirección fija
      analogWrite(ENB_2_PIN, 255);  // Máxima potencia PWM
      delay(5000);
      analogWrite(ENB_2_PIN, 0);    // Apagar PWM
    }
  }
}

void setup() {
  Serial.begin(115200);
  intentoconexion("p101zd", "123456789");

  dht.begin();
  u8g2.begin();

  pinMode(ENA_1_PIN, OUTPUT);
  pinMode(IN1_1_PIN, OUTPUT);
  pinMode(ENB_2_PIN, OUTPUT);
  pinMode(IN3_2_PIN, OUTPUT);

  digitalWrite(ENA_1_PIN, LOW);
  digitalWrite(IN1_1_PIN, LOW);
  digitalWrite(ENB_2_PIN, LOW);
  digitalWrite(IN3_2_PIN, LOW);

  espClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Mensaje inicial en OLED
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x13_tr);
  u8g2.drawStr(0, 13, "Iniciando...");
  u8g2.sendBuffer();
}

void loop() {
  loopAP();

  // Reconexión MQTT
  reconnectMQTT();

  // Si no hay conexión MQTT, omitir otras tareas
  if (!client.connected()) {
    client.loop();
    return;
  }

  client.loop();

  // Leer sensores
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soil1Value = analogRead(SOIL_SENSOR_1_PIN);
  int soil2Value = analogRead(SOIL_SENSOR_2_PIN);
  int ldrValue = analogRead(LDR_PIN);

  // Convertir valores de sensores
  float soil1Humidity = map(soil1Value, 4095, 0, 0, 100);
  float soil2Humidity = map(soil2Value, 4095, 0, 0, 100);
  float intensity = map(ldrValue, 0, 4095, 0, 100);  

  // Control de bombas basado en humedad (PWM invertido)
  digitalWrite(IN1_1_PIN, HIGH); // Dirección fija
  if (soil1Humidity < soil1_min) {
    analogWrite(ENA_1_PIN, 255); // Máxima potencia
  } else if (soil1Humidity > soil1_max) {
    analogWrite(ENA_1_PIN, 0); // Apagado
  } else {
    float ratio = 1 - ((soil1Humidity - soil1_min) / (soil1_max - soil1_min));
    analogWrite(ENA_1_PIN, ratio * 255);
  }

  digitalWrite(IN3_2_PIN, HIGH); // Dirección fija
  if (soil2Humidity < soil2_min) {
    analogWrite(ENB_2_PIN, 255); // Máxima potencia
  } else if (soil2Humidity > soil2_max) {
    analogWrite(ENB_2_PIN, 0); // Apagado
  } else {
    float ratio = 1 - ((soil2Humidity - soil2_min) / (soil2_max - soil2_min));
    analogWrite(ENB_2_PIN, ratio * 255);
  }

  // Mostrar en OLED
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x13_tr);
  u8g2.drawStr(0, 10, ("Temp: " + String(temperature) + "C").c_str());
  u8g2.drawStr(0, 25, ("Soil1: " + String(soil1Humidity) + "%").c_str());
  u8g2.drawStr(0, 40, ("Soil2: " + String(soil2Humidity) + "%").c_str());
  u8g2.sendBuffer();

  // Publicar datos por MQTT
  StaticJsonDocument<256> doc;
  doc["humedadSuelo1"] = soil1Humidity;
  doc["humedadSuelo2"] = soil2Humidity;
  doc["intensidadLuz"] = intensity;
  doc["temperatura"] = temperature;
  doc["humedadRelativa"] = humidity;

  String payload;
  serializeJson(doc, payload);
  client.publish(mqtt_topic_data, payload.c_str());

  delay(5000); // Intervalo de lectura y publicación
}
