#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// WiFi Credentials
const char* ssid = "AGRI_BOT";
const char* password = "12345678";

// Web Server
ESP8266WebServer server(80);

// Motor Driver Pins (L293D)
#define motor1A D5
#define motor1B D6
#define motor2A D3
#define motor2B D4

// Additional Motors
#define sprinklerMotor D1  // Sprinkler Motor
#define seedDispenserMotor D2  // Seed Dispenser Motor

// LCD I2C Address
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Handle Web Requests
void handleRoot() {
  String page = "<html><head>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  page += "<style>";
  page += "body { font-family: Arial, sans-serif; text-align: center; background-color: #f0f0f0; }";
  page += "h1 { color: red; font-size: 28px; }";
  page += "button { width: 100px; height: 100px; font-size: 22px; border-radius: 10px; cursor: pointer; margin: 10px; }";
  page += ".btnF { background-color: blue; color: white; }";
  page += ".btnB { background-color: green; color: white; }";
  page += ".btnL { background-color: orange; color: white; }";
  page += ".btnR { background-color: purple; color: white; }";
  page += ".btnS { background-color: red; color: white; width: 120px; font-size: 30px; }";
  page += ".btnSprinkler { background-color: cyan; color: black; width: 130px; font-size: 22px; }";
  page += ".btnSeedDispenser { background-color: brown; color: white; width: 150px; font-size: 22px; }";
  page += "</style>";
  page += "<script>";
  page += "function move(dir) { var x = new XMLHttpRequest(); x.open('GET', dir, true); x.send(); }";
  page += "</script></head>";

  page += "<body><h1>SIX LEG AGRIBOT</h1>";
  page += "<button class='btnF' onclick=\"move('F')\">Forward</button>";
  page += "<button class='btnL' onclick=\"move('L')\">Left</button>";
  page += "<button class='btnS' onclick=\"move('S')\">Stop</button>";
  page += "<button class='btnR' onclick=\"move('R')\">Right</button>";
  page += "<button class='btnB' onclick=\"move('B')\">Backward</button>";
  page += "<br><br>";
  page += "<button class='btnSprinkler' onclick=\"move('Sprinkler')\">Sprinkler</button>";
  page += "<button class='btnSeedDispenser' onclick=\"move('SeedDispenser')\">Seed Dispenser</button>";
  page += "</body></html>";

  server.send(200, "text/html", page);
}

// Motor Control Functions
void moveForward() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  server.send(200, "text/plain", "Moving Forward");
}

void moveBackward() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  server.send(200, "text/plain", "Moving Backward");
}

void moveLeft() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  server.send(200, "text/plain", "Turning Left");
}

void moveRight() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  server.send(200, "text/plain", "Turning Right");
}

void moveStop() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  server.send(200, "text/plain", "Stopped");
}

// Sprinkler Motor Control
void activateSprinkler() {
  digitalWrite(sprinklerMotor, HIGH);
  delay(3000);
  digitalWrite(sprinklerMotor, LOW);
  server.send(200, "text/plain", "Sprinkler Activated");
}

// Seed Dispenser Motor Control
void activateSeedDispenser() {
  digitalWrite(seedDispenserMotor, HIGH);
  delay(3000);
  digitalWrite(seedDispenserMotor, LOW);
  server.send(200, "text/plain", "Seed Dispenser Activated");
}

// Setup Function
void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("AGRI BOT READY");

  WiFi.softAP(ssid, password);
  Serial.println("WiFi AP Started!");

  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(sprinklerMotor, OUTPUT);
  pinMode(seedDispenserMotor, OUTPUT);

  server.on("/", handleRoot);
  server.on("/F", moveForward);
  server.on("/B", moveBackward);
  server.on("/L", moveLeft);
  server.on("/R", moveRight);
  server.on("/S", moveStop);
  server.on("/Sprinkler", activateSprinkler);
  server.on("/SeedDispenser", activateSeedDispenser);
  server.begin();
  Serial.println("Web Server Started!");
}

// Loop Function
void loop() {
  server.handleClient();
}
