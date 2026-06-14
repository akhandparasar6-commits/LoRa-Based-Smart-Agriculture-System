#include <SPI.h>
#include <LoRa.h>

#define SS_PIN 5
#define RST_PIN 14
#define DIO0_PIN 26

#define SOIL_PIN 34

void setup() {
  Serial.begin(115200);

  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa Init Failed!");
    while (1);
  }

  Serial.println("LoRa Transmitter Ready");
}

void loop() {

  int moisture = analogRead(SOIL_PIN);

  Serial.print("Soil Moisture: ");
  Serial.println(moisture);

  LoRa.beginPacket();
  LoRa.print("Moisture=");
  LoRa.print(moisture);
  LoRa.endPacket();

  Serial.println("Data Sent");

  delay(5000);
}
