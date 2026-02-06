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

// Define pins for Arduino UNO (Receiver)
#define CS_PIN    10
#define RST_PIN   9 
#define IRQ_PIN   2 

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("UNO LoRa Receiver Initializing...");

  LoRa.setPins(CS_PIN, RST_PIN, IRQ_PIN);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  // --- COMPLETE SYNCHRONIZATION SETTINGS (MUST MATCH TRANSMITTER) ---
  LoRa.setSpreadingFactor(10); 
  LoRa.setSignalBandwidth(125E3); 
  LoRa.setCodingRate4(5); 
  LoRa.setSyncWord(0xF3);
  LoRa.enableCrc();

  Serial.println("LoRa Receiver Ready. Listening...");
}

void loop() {
  // Check if a packet has been received
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    // A packet was received, let's read it
    String receivedData = "";
    
    // --- MODIFIED CODE: Use a for loop to read exactly packetSize bytes ---
    for (int i = 0; i < packetSize; i++) {
      receivedData += (char)LoRa.read();
    }

    Serial.print("Received: ");
    Serial.print(receivedData);
    Serial.print(" | RSSI: ");
    Serial.println(LoRa.packetRssi());
  }
}
