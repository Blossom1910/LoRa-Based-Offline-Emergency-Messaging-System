//Lora based Offline Emergency Messaging System
ONE WAY COMMUNICATION CODES: 
Sender: 

#include <SPI.h>
#include <LoRa.h>

#define SS   18
#define RST  14
#define DIO0 26

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {   // change to 866E6 / 915E6 if needed
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // Set LoRa parameters (MUST match the receiver!)
  LoRa.setSpreadingFactor(10);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);

  Serial.println("LoRa Sender Ready.");
}

void loop() {
  String message = "Hello my name is BLOSSOM: " + String(counter);

  Serial.print("Sending: ");
  Serial.println(message);

  // Send LoRa packet
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();

  counter++;
  delay(5000);   // Send a packet every 5 seconds
}


Reciever: 
#include <SPI.h>
#include <LoRa.h>

// ---- ESP32 LoRa Pin Configuration (Receiver) ----
#define SS    18
#define RST   14
#define DIO0  26

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("ESP32 LoRa Receiver");

  // Set LoRa pins
  LoRa.setPins(SS, RST, DIO0);

  // Initialize LoRa at 433 MHz (MUST match transmitter)
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // --- MUST MATCH TRANSMITTER SETTINGS ---
  LoRa.setSpreadingFactor(10);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);

  Serial.println("LoRa Receiver Ready. Listening...");
}

void loop() {
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    Serial.print("Received: ");

    String receivedMessage = "";

    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }
// Print data and RSSI
    Serial.print(receivedData);
    Serial.print(" | RSSI: ");
    Serial.println(LoRa.packetRssi());
  }
}

