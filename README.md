# Temperature and humidity monitoring system
Note: Will update link later.
## Sensor component:
### Hardware:
- ESP32-CAM AI-THINKER.
- DHT11.
- MB102 Breadboard.
- Wires.
### Software:
- Android IDE.
### Note:
- Install all necessary library (Adafruit_Sensor.h, DHT.h, DHT_U.h, WiFi.h, HttpClient.h). Also, it should be Http, not HTTP or other variants. Same with WiFi.
- Make sure the Wifi the microcontroller connect to is 2.1GHz. Maybe it's depended on the microcontroller (new or old version or things like that) but mine doesn't seem to work with 5GHz Wifi.

## Server component:
### Hardware:
- A computer (or laptop) of some kind, maybe a little decent. Don't know if a potato can run it or not but, well, it's better be safe.
- The computer should be connected to the same Wifi as the microcontroller (since we use 192.168.x.x. We use http so ngrok shouldn't work here).
- Also, have a (virtual) environment with the necessary library (check the requirements.txt file).

## How to run:
1. Run the server.
2. Get the server ip. Remember to get the 192.168.x.x one, not the 127.0.x.x one (since it's for one device, and we use at least two devices here).
3. Replace the neccessary information in the Arduino source code.
4. Run the Arduino device.
5. Go to the server ip and check the result.