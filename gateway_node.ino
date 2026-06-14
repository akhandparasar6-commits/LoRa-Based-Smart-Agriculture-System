#include <SPI.h>
#include <LoRa.h>

#define SS_PIN 5
#define RST_PIN 14
#define DIO0_PIN 26

HardwareSerial modem(2);

void setup() {

  Serial.begin(115200);

  modem.begin(115200, SERIAL_8N1, 16, 17);

  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa Init Failed!");
    while (1);
  }

  Serial.println("Gateway Ready");
}

void loop() {

  int packetSize = LoRa.parsePacket();

  if (packetSize) {

    String receivedData = "";

    while (LoRa.available()) {
      receivedData += (char)LoRa.read();
    }

    Serial.println("Received:");
    Serial.println(receivedData);

    // Send to 5G modem
    modem.println(receivedData);
  }
}
