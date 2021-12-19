#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>

DHT dht(D4, DHT11);

WiFiClient client;

#define green D0
#define yellow D1
#define red D2
#define blue D3

long myChannelNumber = 0000000;
const char myWriteAPIKey[] = "IM0OZY7OMERZLG64";

void setup() {
  Serial.begin(9600);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  WiFi.begin("SSID", "Password");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
}

void loop() {
  float t = dht.readTemperature();
  Serial.println("Temperature: " + (String) t);
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  if (20 < t && t <= 40)
  {
    digitalWrite(green, HIGH );
    digitalWrite(yellow, HIGH );
    digitalWrite(red, LOW );
    digitalWrite(blue, LOW);
    delay(100);
  }
  else if (41 < t && t <= 60)
  {
    digitalWrite(green, LOW );
    digitalWrite(yellow, LOW );
    digitalWrite(red, HIGH );
    digitalWrite(blue, HIGH);
    delay(100);
  }
  delay(2000);
}
