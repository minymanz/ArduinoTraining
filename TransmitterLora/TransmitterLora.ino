#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module

#define ss 5
#define rst 14
#define dio0 2

void setup() {
//initialize Serial Monitor
  Serial.begin(115200);

  while (!Serial);
  Serial.println("LoRa Sender");

  //setup LoRa transceiver module

  LoRa.setPins(ss, rst, dio0);

  //replace the LoRa.begin(---E-) argument with your location's frequency
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America

  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }

  // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  Serial.print("Sending packet: ");

  //Send LoRa packet to receiver
  LoRa.beginPacket();
  //LoRa.print("4. Kerakyatan yang dipimpin oleh hikmat kebijaksanaan dalam permusyawaratan/perwakilan");
  String text  = Serial.readString();
  Serial.println(text);
  LoRa.print(text);
  LoRa.endPacket();


  delay(3000);
}
