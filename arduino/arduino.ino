#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define DHTPIN 2
#define DHTTYPE DHT11

// Variables for sensor and time thingy
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
unsigned long lastTime = 0;

// Network
const char* ssid = "Duy Thong";
const char* password = "12345678";
const String serverName = "http://http://127.0.0.1:5000/update/";
//const String serverName = "https://b129-2405-4802-9177-e6c0-94e8-a8d5-8c58-5f4c.ngrok-free.app/update/";

// Variables for temperature and humidity
float temperature;
float humidity;

void setup() {
  Serial.begin(9600);
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000 + 1000; // add 1 second to the delayMS variable to make sure sensor is ready before taking reading

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void getTemperatureAndHumidity() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    temperature = event.temperature;
    Serial.print(F("Temperature: "));
    Serial.print(temperature);
    Serial.print("  ");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    humidity = event.relative_humidity;
    Serial.print(F("Humidity: "));
    Serial.print(humidity);
    Serial.println("");
  }
}

void loop() {
  if (millis() - lastTime > delayMS) {
    lastTime = millis();

    if (WiFi.status() == WL_CONNECTED) {
      // Get temperature and humidity
      getTemperatureAndHumidity();

      HTTPClient http;
      String serverPath = serverName + "?temperature=" + String(temperature) + "&humidity=" + String(humidity);

      Serial.println(serverPath.c_str());
      http.begin(serverPath.c_str());
      int httpCode = http.GET();
      Serial.println(httpCode);
      if (httpCode > 0) {
        String payload = http.getString();
        Serial.println(payload);
      }
      http.end();
    }
    else {
      Serial.println("Can't send data");
    }
  }
}
