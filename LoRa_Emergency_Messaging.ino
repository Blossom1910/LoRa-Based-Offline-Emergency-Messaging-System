//Lora based Offline Emergency Messaging System
ONE WAY COMMUNICATION CODES: 
Sender: 

#include <SPI.h> 
#include <LoRa.h> 
#include <Keypad.h>
// LoRa Transceiver Module Pins 
#define SS_PIN 5 
#define RST_PIN 14 
#define DIO0_PIN 2 
// Keypad Setup 
const byte ROWS = 4; // four rows 
const byte COLS = 4; // four columns 
char keys[ROWS][COLS] = { 
{'1','2','3','A'}, 
{'4','5','6','B'}, 
{'7','8','9','C'}, 
{'*','0','#','D'} 
}; 
// Define the connections for the keypad  
// ROWS PINS: GPIO 12, 13, 25, 26 
// COLS PINS: GPIO 27, 32, 33, 15 
byte rowPins[ROWS] = {12, 13, 25, 26}; // Connect to the row pinouts of the keypad 
byte colPins[COLS] = {27, 32, 33, 15}; // Connect to the column pinouts of the keypad 
// Initialize keypad library 
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 
int counter = 0; 
// SETUP
void setup() { 
// Initialize Serial Monitor 
Serial.begin(115200); 
while (!Serial); 
Serial.println("LoRa Keypad Sender"); 
// Setup LoRa transceiver module 
LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN); 
// Frequency 433E6 for Asia 
while (!LoRa.begin(433E6)) { 
Serial.println("."); 
delay(500); 
} 
// sync word (0xF3) has to match the receiver 
LoRa.setSyncWord(0xF3); 
Serial.println("LoRa Initializing OK!"); 
} 
// LOOP  
void loop() { 
// Check for a key press 
char customKey = customKeypad.getKey(); 
// Only proceed if a key was pressed 
if (customKey){ 
counter++; // Increment the counter for the new message 
String message = "Key: " + String(customKey) + " | Count: " + String(counter); 
Serial.print("Sending packet: "); 
Serial.println(message); 
// Send LoRa packet to receiver 
LoRa.beginPacket(); 
LoRa.print(message); 
LoRa.endPacket(); 
//Small delay so that the packets go to the receiver at a fixed rate  
delay(500);  
} 
// The loop is now continuously checking for a key press,  
} 
Reciever: 
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
Serial.println("LoRa Receiver"); 
//setup LoRa transceiver module 
LoRa.setPins(ss, rst, dio0); 

//433E6 for Asia...same as the sender
while (!LoRa.begin(433E6)) { 
Serial.println("."); 
delay(500); 
} 

LoRa.setSyncWord(0xF3); 
Serial.println("LoRa Initializing OK!"); 
} 
void loop() { 
// try to parse packet 
int packetSize = LoRa.parsePacket(); 
if (packetSize) { 
// received a packet 
Serial.print("Received packet '"); 
// read packet 
while (LoRa.available()) { 
String LoRaData = LoRa.readString(); 
Serial.print(LoRaData);  
} 
// print RSSI of packet 
Serial.print("' with RSSI "); 
Serial.println(LoRa.packetRssi()); 
} 
}
