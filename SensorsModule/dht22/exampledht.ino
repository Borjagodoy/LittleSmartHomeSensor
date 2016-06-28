#include <ESP8266HTTPClient.h>

#include "DHT.h"

#define DHTPIN D2     // Pin donde está conectado el sensor
#include <ESP8266WiFi.h>

//#define DHTTYPE DHT11   // Descomentar si se usa el DHT 11
#define DHTTYPE DHT22   // Sensor DHT22
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "littlesmarthome.firebaseio.com"
#define FIREBASE_AUTH "RtHLWjhpJ2UuaiZNlDtwJvIAri2vnrGsXvoOKY8x"
#define WIFI_SSID "MOVISTAR_0131"
#define WIFI_PASSWORD "NwHkVaR8qN5NygCCEzNh"


DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando...");
  dht.begin();
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("temperature", 0);
  Firebase.set("humedad", 0);
}
void loop() {
  delay(2000);
  float h = dht.readHumidity(); //Leemos la Humedad
  float t = dht.readTemperature(); //Leemos la temperatura en grados Celsius
  float f = dht.readTemperature(true); //Leemos la temperatura en grados Fahrenheit
  //--------Enviamos las lecturas por el puerto serial-------------
  Serial.print("Humedad ");
  Serial.print(h);
  Firebase.setInt("humedad", h);
  Serial.print(" %t");
  Serial.print("Temperatura: ");
  Firebase.setInt("temperature", t);
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.println(" *F");
}

