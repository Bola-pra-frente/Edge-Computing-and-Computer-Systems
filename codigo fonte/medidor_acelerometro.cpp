#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
 
// Defina suas credenciais Wi-Fi
const char* ssid = "seu wifi";
const char* password = "senha do wifi";
 
// URL do ThingSpeak API (substitua pelo seu canal e chave de API)
const String thingSpeakUrl = "https://api.thingspeak.com/update?api_key=(CHAVE_DA_API)";
 
// Criação do objeto MPU6050
Adafruit_MPU6050 mpu;
 
void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
 
  Serial.println("Iniciando MPU6050 e Conectando ao Wi-Fi");
 
  // Tenta inicializar o MPU6050
  if (!mpu.begin()) {
    Serial.println("Falha ao encontrar o MPU6050!");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 encontrado!");
 
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
 
  // Conectando-se à rede Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Conectando-se ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado ao Wi-Fi! IP: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
 
  // Exibindo valores no serial
  Serial.print("Aceleração X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.println(a.acceleration.z);
 
  Serial.print("Rotação X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.println(g.gyro.z);
 
  Serial.print("Temperatura: ");
  Serial.println(temp.temperature);
 
  // Enviar dados para o ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
 
    // Montando URL com os valores dos sensores
    String url = thingSpeakUrl;
    url += "&field1=" + String(a.acceleration.x);
    url += "&field2=" + String(a.acceleration.y);
    url += "&field3=" + String(a.acceleration.z);
    url += "&field4=" + String(g.gyro.x);
    url += "&field5=" + String(g.gyro.y);
    url += "&field6=" + String(g.gyro.z);
    url += "&field7=" + String(temp.temperature);
 
    // Enviando dados para o ThingSpeak
    http.begin(url);
    int httpCode = http.GET(); // Enviando a solicitação GET
 
    if (httpCode > 0) {
      Serial.printf("Código de resposta: %d\n", httpCode);
    } else {
      Serial.println("Erro na requisição HTTP");
    }
 
    http.end(); // Fechando a conexão HTTP
  } else {
    Serial.println("Erro de conexão Wi-Fi");
  }
 
  // Aguarde antes de enviar novamente
  delay(500);
}