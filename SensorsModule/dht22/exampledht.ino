#include <ESP8266HTTPClient.h>

#include "DHT.h"

#define DHTPIN D2     // Pin donde está conectado el sensor
#include <ESP8266WiFi.h>

//#define DHTTYPE DHT11   // Descomentar si se usa el DHT 11
#define DHTTYPE DHT22   // Sensor DHT22
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "YOUR_HOST"
#define FIREBASE_AUTH "Your_Pass_Auth_Firebase"
#define WIFI_SSID "yout_SSID"
#define WIFI_PASSWORD "Your_password_wifi"


DHT dht(DHTPIN, DHTTYPE);

double temperaturaCelsius;
double temperaturaFarenheit;
double humedad;
bool eventoLanzado;


void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando...");
  dht.begin();
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("temperature", 0);
  Firebase.set("humedad", 0);
  
  temperaturaCelsius = 0;
  temperaturaFarenheit = 0;
  humedad = 0;
  iniciarConexionWifi();
}


void loop() {
  if(!eventoLanzado){
    leerDatosSensor();
    actualizarDatos();
    mostrarDatos();
    
    esperar(20000);
  } else {
    comprobarEvento(); // wifi lose, new temp, ...
  }
}

/* Si no se conecta a una red wifi, que cree una propia. */
void iniciarConexionWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}

void leerDatosSensor(){
  humedad = dht.readHumidity();
  temperaturaCelsius = dht.readTemperature();
  temperaturaFarenheit = dht.readTemperature(true);
}

void actualizarDatos(){
  Firebase.setInt("humedad", humedad);
  Firebase.setInt("temperature", temperaturaCelsius);
}

void mostrarDatos(){
  Serial.print("Humedad ");
  Serial.print(humedad);
  Serial.print(" %t");
  Serial.print("Temperatura: ");
  Serial.print(temperaturaCelsius);
  Serial.print(" *C ");
  Serial.print(temperaturaFarenheit);
  Serial.println(" *F");
}

void esperar(int tiempo){
  int i = 0;
  
  while(i<tiempo and !eventoLanzado){
    delay(1000);
    eventoLanzado = hayCambios();
    i+=1000;
  }
}


bool hayCambios(){
  
}
