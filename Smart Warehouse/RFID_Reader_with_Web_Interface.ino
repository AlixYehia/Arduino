#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <MFRC522.h>

// Define constants for pins
const int SS_PIN = D4;
const int RST_PIN = D3;

MFRC522 rfid(SS_PIN, RST_PIN);
ESP8266WebServer server(80);
String firstTagID = "";
String secondTagID = "";
String tagID = "";

byte tagCount = 0;
String message1 = "";
String message2 = "";
 static int lastRandNum = 0;
 
// Wifi info
const char* ssid = "Xiao";
const char* password = "11223322";

int chosenNumbers[10] = {0}; // Array to keep track of the numbers that have already been chosen
int numChosen = 0; // Number of numbers that have already been chosen

void handleRoot() {
  // Generate HTML code as a string
  String html = "<!DOCTYPE html> <html>\n";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  html += "<title>RFID Reader</title>\n";
  html += "<meta http-equiv=\"refresh\" content=\"2\">\n"; // refresh the page every 2 seconds
  html += "<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  html += "body{margin-top: 50px;} h1 {color: #a020f0;margin: 50px auto 30px;}h3 {color: #a020f0;margin-bottom: 50px;}\n";
  html += ".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding:13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  html += ".button-on {background-color: #3498db;}\n";
  html += ".button-on:active {background-color: #FF0000;}\n";
  html += ".button-off {background-color: #FF0000;}\n";
  html += ".button-off:active {background-color: #FF0000;}\n";
  html += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  html += "</style>\n";
  html += "</head><body>\n";
  html += "<h1>RFID Reader</h1>\n";
  html += "<h3>Tag ID:</h3>\n";

  // Add random number to the messages
  static int lastRandNum1 = 0;
  static int lastRandNum2 = 0;
  String message1 = "";
  if (firstTagID == "452fc028") {
    if (lastRandNum1 == 0) {
      lastRandNum1 = random(1000, 9999);
    }
    message1 = "1 - Medicine Package Was Scanned - " + String(lastRandNum1);
  }
  String message2 = "";
  if (secondTagID == "ca4d1f40") {
    if (lastRandNum2 == 0) {
      lastRandNum2 = random(1000, 9999);
    }
    message2 = "2 - Tools Package Was Scanned - " + String(lastRandNum2);
  }

  html += "<p>";
  html += message1 + "<br/>";
  html += message2;
  html += "</p>\n";
  html += "</body>\n";
  html += "</html>\n";
  server.send(200, "text/html", html);

  // Update lastRandNum if firstTagID is scanned again
  if (firstTagID == "452fc028" && message1 != "") {
    lastRandNum1 = lastRandNum1;
  }
  // Update lastRandNum if secondTagID is scanned again
  if (secondTagID == "ca4d1f40" && message2 != "") {
    lastRandNum2 = lastRandNum2;
  }
}

void handleNotFound() {
  String message = "Page not found\n";
  server.send(404, "text/plain", message);
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
server.handleClient();

  // Check if a new RFID tag is present
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Read the ID of the RFID tag
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Convert the ID to a string
  tagID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    tagID += String(rfid.uid.uidByte[i] < 0x10 ?"0" : "") + String(rfid.uid.uidByte[i], HEX);
  }
  
  Serial.println("Tag ID: " + tagID);

  // Store the tag ID in the appropriate variable
  if (tagCount == 0) {
    firstTagID = tagID;
  } else if (tagCount == 1) {
    secondTagID = tagID;
  }
  tagCount++;

  // If both tag IDs have been read, print them to the serial monitor
  if (tagCount == 2) {
    Serial.println("1- " + firstTagID);
    Serial.println("2- " + secondTagID);
    tagCount = 0;
  }

  // Generate HTML code as a string and send it to the client
  handleRoot();

  // Halt the PICC and stop encryption on the PCD to prepare for the next reading
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

int generateRandomNumber() {
  int randomNumber = 0;
  do {
    randomNumber = random(1, 11);
  } while (isNumberChosen(randomNumber));
  chosenNumbers[numChosen] = randomNumber;
  numChosen++;
  return randomNumber;
}

bool isNumberChosen(int number) {
  for (int i = 0; i < numChosen; i++) {
    if (chosenNumbers[i] == number) {
      return true;
    }
  }
  return false;
}