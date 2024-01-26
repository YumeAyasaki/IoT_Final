#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <HttpClient.h>

#define DHTPIN 2
#define DHTTYPE DHT11

// Variables for sensor and time thingy
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
unsigned long lastTime = 0;

// Network
const char* ssid = "Duy Thong";
const char* password = "12345678";
const String serverName = "192.168.1.6";
const int port = 5000;
WiFiClient wifi;
HttpClient client(wifi, serverName, port);

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

      // Send data to server using GET method

      String data = "?temperature=" + String(temperature) + "&humidity=" + String(humidity);
      String sendingToServer = "http://" + serverName + ":" + port + "/update/" + data;

      client.beginRequest();
      Serial.println(sendingToServer);
      client.get(sendingToServer);
      client.endRequest();

      int statusCode = client.responseStatusCode();
      String response = client.responseBody();

      Serial.print("Status code: ");
      Serial.println(statusCode);
      Serial.print("Response: ");
      Serial.println(response);
    }
    else {
      Serial.println("Can't send data");
    }
  }
}
