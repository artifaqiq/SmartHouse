#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>

#define PHOTO_RES_PIN A0
#define RELAY1_PIN 2
#define DHT11_PIN 3
#define YELLOW_LED_PIN 5
#define GREEN_LED_PIN 4


#define PORT 80
#define DOMAIN  "avakiana-26-14.herokuapp.com"
#define POSTING_INTERVAL 1000L


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress ip(192, 168, 0, 110);
EthernetClient client;
DHT dht(DHT11_PIN, DHT11);

unsigned long lastConnectionTime = 0;            
boolean relay1_status = false;

void setup() {
  
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  
  digitalWrite(RELAY1_PIN, relay1_status);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  
  Serial.begin(9600);
  
  dht.begin();

  if (Ethernet.begin(mac) == 0) {
    Ethernet.begin(mac, ip);
  }
  digitalWrite(GREEN_LED_PIN, HIGH);
  
}

void loop() {

  if (millis() - lastConnectionTime > POSTING_INTERVAL) {
    sendSensorsData(dht.readTemperature(), dht.readHumidity(), getIllumination(PHOTO_RES_PIN));
    relay1_status = getRequestedRelayStatus();
    sendActualRelayStatus(relay1_status);

    digitalWrite(RELAY1_PIN, relay1_status);
    lastConnectionTime = millis();
  }
}

void sendSensorsData(int temp, int hum, int ill) {

//  client.stop();
  
//  Serial.println("connecting...");

  if (client.connect(DOMAIN, PORT)) {
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
//    Serial.println("connected");

    String sensorsInfoJson = getSensorsInfoJson(temp, hum, ill);

    client.println("POST /api/sensors/update HTTP/1.1");
    client.println("HOST: avakiana-26-14.herokuapp.com");
    client.println("Connection: close");
    client.println("content-length: " + String(sensorsInfoJson.length()));
    client.println();
    client.println(sensorsInfoJson);
    client.println();

//    Serial.println("Sended");
    
  } else {
//    Serial.println("connection failed");
    digitalWrite(GREEN_LED_PIN, LOW);
  }
  
  while(client.connected()) {
    if (client.available()) {
      char c = client.read();
//      Serial.print(c);
    }
  }
  
//  Serial.println("disconnecting.");
  digitalWrite(YELLOW_LED_PIN, LOW);
  client.stop();
}

void sendActualRelayStatus(boolean status) {
//   client.stop();
  
//  Serial.println("connecting...");

  if (client.connect(DOMAIN, PORT)) {
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
//    Serial.println("connected");

    String relayStatusJson = getRelayStatusJson(status);

    client.println("POST /api/states/update HTTP/1.1");
    client.println("HOST: avakiana-26-14.herokuapp.com");
    client.println("Connection: close");
    client.println("content-length: " + String(relayStatusJson.length()));
    client.println();
    client.println(relayStatusJson);
    client.println();

//    Serial.println("Sended");
    
  } else {
//    Serial.println("connection failed");
  }
  while(client.connected()) {
    if (client.available()) {
      char c = client.read();
//      Serial.print(c);
    }
  }
  
//  Serial.println("disconnecting.");
  digitalWrite(YELLOW_LED_PIN, LOW);
  client.stop();
}

boolean getRequestedRelayStatus() {
//  client.stop();
  
//  Serial.println("connecting...");

  if (client.connect(DOMAIN, PORT)) {
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
//    Serial.println("connected");

    client.println("GET /api/states/relay1_requested HTTP/1.1");
    client.println("HOST: avakiana-26-14.herokuapp.com");
    client.println("Connection: close");
    client.println();

//    Serial.println("Sended");
    
  } else {
    Serial.println("connection failed");
  }
  char c;
  while(client.connected()) {
    if (client.available()) {
      c = client.read();
//      Serial.print(c);
    }
  }
  
//  Serial.println("disconnecting.");
  digitalWrite(YELLOW_LED_PIN, LOW);
  client.stop();

  return c == '1' ? true: false;
}

