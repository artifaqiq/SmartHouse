#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>

const int PHOTO_RES_PIN = 1;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char domain[] = "avakiana-26-14.herokuapp.com";  

IPAddress ip(192, 168, 0, 106);
EthernetClient client;
DHT dht(2, DHT11);

unsigned long lastConnectionTime = 0;            
const unsigned long POSTING_INTERVAL = 4000L;

void setup() {
  pinMode(8, OUTPUT);
  
  Serial.begin(9600);
  dht.begin();

  if (Ethernet.begin(mac) == 0) {
    Ethernet.begin(mac, ip);
  }
}

void loop() {

  if (millis() - lastConnectionTime > POSTING_INTERVAL) {
    sendSensorsData(dht.readTemperature(), dht.readHumidity(), getIllumination(PHOTO_RES_PIN));
    Serial.println(getIllumination(PHOTO_RES_PIN));
  }
}

void sendSensorsData(int temp, int hum, int ill) {

  client.stop();
  
  Serial.println("connecting...");

  if (client.connect(domain, 80)) {
    Serial.println("connected");

    String sensorsInfoJson = getSensorsInfoJson(temp, hum, ill);

    client.println("POST /api/sensors/update HTTP/1.1");
    client.println("HOST: avakiana-26-14.herokuapp.com");
    client.println("Connection: close");
    client.println("content-length: " + String(sensorsInfoJson.length()));
    client.println();
    client.println(sensorsInfoJson);
    client.println();

    Serial.println("Sended");
    lastConnectionTime = millis();
    
  } else {
    Serial.println("connection failed");
  }
  while(client.connected()) {
    if (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
  }
  
  Serial.println("disconnecting.");
  client.stop();
}

