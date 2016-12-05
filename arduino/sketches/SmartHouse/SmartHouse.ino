#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>

#define PHOTO_RES_PIN A0
#define RELAY_PIN 2
#define DHT11_PIN 3
#define PORT 80
#define DOMAIN  "avakiana-26-14.herokuapp.com"
#define POSTING_INTERVAL 4000L

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress ip(192, 168, 0, 106);
EthernetClient client;
DHT dht(DHT11_PIN, DHT11);

unsigned long lastConnectionTime = 0;            

void setup() {
  Serial.println(Ethernet.localIP());
  
  pinMode(8, OUTPUT);
  
  Serial.begin(9600);
  
  dht.begin();

  if (Ethernet.begin(mac) == 0) {
    Serial.println(Ethernet.localIP());
    Ethernet.begin(mac, ip);
  }
}

boolean x = true;

void loop() {

  if (millis() - lastConnectionTime > POSTING_INTERVAL) {
    sendSensorsData(dht.readTemperature(), dht.readHumidity(), getIllumination(PHOTO_RES_PIN));
    Serial.println(getIllumination(PHOTO_RES_PIN));

    sendActualRelayStatus(x);
    x = !x;

    getRequestedRelayStatus();
    
    lastConnectionTime = millis();
  }
}

void sendSensorsData(int temp, int hum, int ill) {

  client.stop();
  
  Serial.println("connecting...");

  if (client.connect(DOMAIN, PORT)) {
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

void sendActualRelayStatus(boolean status) {
   client.stop();
  
  Serial.println("connecting...");

  if (client.connect(DOMAIN, PORT)) {
    Serial.println("connected");

    String relayStatusJson = getRelayStatusJson(status);

    client.println("POST /api/states/update HTTP/1.1");
    client.println("HOST: avakiana-26-14.herokuapp.com");
    client.println("Connection: close");
    client.println("content-length: " + String(relayStatusJson.length()));
    client.println();
    client.println(relayStatusJson);
    client.println();

    Serial.println("Sended");
    
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

boolean getRequestedRelayStatus() {
  client.stop();
  
  Serial.println("connecting...");

  if (client.connect(DOMAIN, PORT)) {
    Serial.println("connected");

    client.println("GET /api/states/show HTTP/1.1");
    client.println("HOST: avakiana-26-14.herokuapp.com");
    client.println("Connection: close");
    client.println();

    Serial.println("Sended");
    
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

  return true;
}

