#include <ArduinoJson.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <SPI.h>
#include <WiFi.h>
#include <ArduinoHttpClient.h>

//Defines - used as constants, not good practice in c++
#define PIN_1 6
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5

#define BANK_SIZE 16
#define DELAY 5000

//Global variables - again not good practice in other "real" programming
char ssid[] = "yourNetwork";     //  your network SSID (name)
char pass[] = "secretPassword";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
char serverAddress[] = "10.1.1.50";  // server address
int port = 32001;
WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);

Adafruit_NeoPixel pixels_1(BANK_SIZE, PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_2(BANK_SIZE, PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_3(BANK_SIZE, PIN_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_4(BANK_SIZE, PIN_4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_5(BANK_SIZE, PIN_5, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
  pixels_1.begin();
  pixels_2.begin();
  pixels_3.begin();
  pixels_4.begin();
  pixels_5.begin();

  Serial.begin(9600);
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void loop() {
  // Check WiFi Status
  int red = 255;
  int blue = 255;
  int green = 255;
  if (WiFi.status() == WL_CONNECTED) {
    client.get("/lights");
    //Check the returning code                                                                  
    if (client.responseStatusCode() > 0) {
      // Get the request response payload
      // TODO: Parsing
      const size_t capacity = JSON_OBJECT_SIZE(3) + 20;
      DynamicJsonDocument doc(capacity);
      
      const char* json = "{\"Red\":255,\"Blue\":255,\"Green\":255}";
      
      deserializeJson(doc, client.readString());
      deserializeJson(doc, client.responseBody());
      
      red = doc["Red"]; // 255
      blue = doc["Blue"]; // 255
      green = doc["Green"]; // 255
    }
  }

  //set the colors
  pixels_1.clear();
  pixels_2.clear();
  pixels_3.clear();
  pixels_4.clear();
  pixels_5.clear();
  uint32_t magenta = pixels_1.Color(red, blue, green);
  pixels_1.fill(magenta,0,BANK_SIZE);
  pixels_2.fill(magenta,0,BANK_SIZE);
  pixels_3.fill(magenta,0,BANK_SIZE);
  pixels_4.fill(magenta,0,BANK_SIZE);
  pixels_5.fill(magenta,0,BANK_SIZE);
  pixels_1.show();
  pixels_2.show();
  pixels_3.show();
  pixels_4.show();
  pixels_5.show();

  delay(DELAY);
}
