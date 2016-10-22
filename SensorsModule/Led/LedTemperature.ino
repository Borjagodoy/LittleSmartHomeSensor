#include <ESP8266HTTPClient.h>

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "YOUR_HOST"
#define FIREBASE_AUTH "Your_Pass_Auth_Firebase"
#define WIFI_SSID "yout_SSID"
#define WIFI_PASSWORD "Your_password_wifi"

const int ledPin = 15;

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
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
  Firebase.set("LedTemperature", 0);
  
}


void loop() {
  if(Firebase.getInt("temperature")>28){
  digitalWrite(15, 1);
  digitalWrite(13, 1);
  Firebase.set("LedTemperature",1);
  }
  else{
  digitalWrite(15, 0);
  digitalWrite(13, 0);
  Firebase.set("LedTemperature",0);
  }
  
  delay(200);
}

