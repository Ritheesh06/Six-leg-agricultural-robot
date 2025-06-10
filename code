#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// WiFi Credentials
const char* ssid = "AGRI_BOT";
const char* password = "12345678";

// Web Server
ESP8266WebServer server(80);

// Motor Driver Pins
#define IN1 D5  // Motor A
#define IN2 D6
#define IN3 D3  // Motor B
#define IN4 D4

// Relay Pins
#define sprinklerRelay D1
#define seedRelay D2

// LCD Setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Web Page
void handleRoot() {
  String page = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  page += "<style>body{text-align:center;font-family:Arial;background:#eef}button{width:120px;height:60px;margin:10px;font-size:18px;}</style>";
  page += "<script>function move(cmd){var x=new XMLHttpRequest();x.open('GET', cmd, true);x.send();}</script></head><body>";
  page += "<h1>AGRI BOT</h1>";
  page += "<button onclick=\"move('F')\">Forward</button><br>";
  page += "<button onclick=\"move('L')\">Left</button>";
  page += "<button onclick=\"move('S')\">Stop</button>";
  page += "<button onclick=\"move('R')\">Right</button><br>";
  page += "<button onclick=\"move('B')\">Backward</button><br><br>";
  page += "<button onclick=\"move('Sprinkler')\">Sprinkler</button>";
  page += "<button onclick=\"move('SeedDispenser')\">Seed Sower</button>";
  page += "</body></html>";
  server.send(200, "text/html", page);
}

// Motor Functions
void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  server.send(200, "text/plain", "Forward");
}

void moveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  server.send(200, "text/plain", "Backward");
}

void moveLeft() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);  // Motor A backward
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  // Motor B forward
  server.send(200, "text/plain", "Left Turn");
}

void moveRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  // Motor A forward
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);  // Motor B backward
  server.send(200, "text/plain", "Right Turn");
}

void moveStop() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  server.send(200, "text/plain", "Stopped");
}

// Relay Control
void activateSprinkler() {
  digitalWrite(sprinklerRelay, HIGH);
  delay(3000);
  digitalWrite(sprinklerRelay, LOW);
  server.send(200, "text/plain", "Sprinkler Activated");
}

void activateSeedDispenser() {
  digitalWrite(seedRelay, HIGH);
  delay(3000);
  digitalWrite(seedRelay, LOW);
  server.send(200, "text/plain", "Seed Sower Activated");
}

// Setup
void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("AGRI BOT READY");

  WiFi.softAP(ssid, password);
  Serial.println("WiFi AP Started");

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Relay pins
  pinMode(sprinklerRelay, OUTPUT);
  pinMode(seedRelay, OUTPUT);
  digitalWrite(sprinklerRelay, LOW);
  digitalWrite(seedRelay, LOW);

  // Server routes
  server.on("/", handleRoot);
  server.on("/F", moveForward);
  server.on("/B", moveBackward);
  server.on("/L", moveLeft);
  server.on("/R", moveRight);
  server.on("/S", moveStop);
  server.on("/Sprinkler", activateSprinkler);
  server.on("/SeedDispenser", activateSeedDispenser);

  server.begin();
  Serial.println("Web Server Running");
}

// Loop
void loop() {
  server.handleClient();
}
