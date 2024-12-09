#include <WiFiS3.h>
#include <EEPROM.h>

// Default AP credentials
const char* DEFAULT_SSID = "SetupWiFi";
const char* DEFAULT_PASSWORD = "password123";

// EEPROM addresses
const int SSID_ADDR = 0;
const int PASS_ADDR = 32;
const int CONFIGURED_FLAG_ADDR = 96;

// Maximum lengths for credentials
const int MAX_SSID_LENGTH = 32;
const int MAX_PASS_LENGTH = 64;

// Current AP credentials
char current_ssid[MAX_SSID_LENGTH];
char current_password[MAX_PASS_LENGTH];

// TCP server on port 80
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  
  if (!isConfigured()) {
    strncpy(current_ssid, DEFAULT_SSID, MAX_SSID_LENGTH);
    strncpy(current_password, DEFAULT_PASSWORD, MAX_PASS_LENGTH);
  } else {
    loadCredentials();
  }
  
  setupAP();
  server.begin();
  
  Serial.println("Server started");

  // Print current WiFi credentials to Serial Monitor
  Serial.print("Current SSID: ");
  Serial.println(current_ssid);
  Serial.print("Current Password: ");
  Serial.println(current_password);
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("New client connected");
    String currentLine = "";
    String request = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        
        if (c == '\n') {
          if (currentLine.length() == 0) {
            if (request.indexOf("POST /unlock") >= 0) {
              handleUnlock(client);
            } else if (request.indexOf("POST /activaterfid") >= 0) {
              handleRFIDActivation(client);
            } else if (request.indexOf("POST /wifi") >= 0) {
              processCredentials(client);
            } else {
              sendWebPage(client);
            }
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    
    client.stop();
    Serial.println("Client disconnected");
  }
}

void sendWebPage(WiFiClient &client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  client.println("<!DOCTYPE html><html lang='en'>");
  client.println("<head><title>Smart Door Control & WiFi Configuration</title>");
  client.println("<meta charset='UTF-8'>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
  client.println("<style>");

  // General Body Styles
  client.println("body { font-family: 'Arial', sans-serif; background-color: #f0f0f5; margin: 0; padding: 0; box-sizing: border-box; color: #333; }");
  client.println(".container { width: 100%; max-width: 960px; margin: 30px auto; padding: 25px; background: #ffffff; border-radius: 16px; box-shadow: 0 12px 40px rgba(0, 0, 0, 0.1); }");

  // Header Section
  client.println(".header { text-align: center; margin-bottom: 40px; }");
  client.println(".header h1 { font-size: 2.6em; font-weight: 700; color: #333; margin-bottom: 10px; }");
  client.println(".header p { font-size: 1.2em; color: #777; font-weight: 300; margin-top: 0; }");

  // Section Styling
  client.println(".section { background-color: #f9f9f9; padding: 25px; border-radius: 12px; box-shadow: 0 6px 20px rgba(0, 0, 0, 0.05); margin-bottom: 25px; }");
  client.println(".section h3 { font-size: 1.6em; font-weight: 600; color: #333; margin-bottom: 15px; letter-spacing: 0.5px; }");

  // Form Elements and Buttons
  client.println("input[type='text'], input[type='password'], button { width: 100%; padding: 14px; margin-top: 10px; font-size: 1.1em; border-radius: 10px; border: 1px solid #ccc; background-color: #f5f5f5; color: #333; box-sizing: border-box; transition: all 0.3s ease; }");

  // Focused Input Elements
  client.println("input[type='text']:focus, input[type='password']:focus { border-color: #4CAF50; outline: none; background-color: #fff; }");

  // Button Styling (No color change on press)
  client.println("button { font-weight: 600; border: none; cursor: pointer; border-radius: 10px; padding: 16px; text-transform: uppercase; letter-spacing: 1px; transition: all 0.3s ease; }");

  // Unlock Door Button - Orange
  client.println(".unlock-btn { background-color: #FF7043; color: #fff; }");
  client.println(".unlock-btn:hover { background-color: #FF5722; }");

  // RFID Button - Blue
  client.println(".rfid-btn { background-color: #2196F3; color: #fff; }");
  client.println(".rfid-btn:hover { background-color: #1976D2; }");

  // WiFi Settings Button - Green
  client.println(".wifi-btn { background-color: #4CAF50; color: #fff; }");
  client.println(".wifi-btn:hover { background-color: #388E3C; }");

  // Footer Section Styling
  client.println(".footer { text-align: center; font-size: 0.9em; color: #777; margin-top: 30px; }");
  client.println(".footer a { color: #4CAF50; text-decoration: none; font-weight: 600; transition: all 0.3s ease; }");
  client.println(".footer a:hover { text-decoration: underline; color: #388E3C; }");

  // Responsive Styles
  client.println("@media (max-width: 768px) {");
  client.println("  .container { padding: 20px; }");
  client.println("  .header h1 { font-size: 2.4em; }");
  client.println("  .section h3 { font-size: 1.4em; }");
  client.println("  input[type='text'], input[type='password'], button { padding: 14px; font-size: 1em; }");
  client.println("}");
  
  client.println("@media (max-width: 480px) {");
  client.println("  .container { width: 90%; padding: 15px; }");
  client.println("  .header h1 { font-size: 1.9em; }");
  client.println("  input[type='text'], input[type='password'], button { padding: 12px; font-size: 0.95em; }");
  client.println("}");

  client.println("</style>");
  
  client.println("<script>");
  client.println("function submitWifi(event) {");
  client.println("  event.preventDefault();");
  client.println("  const form = event.target;");
  client.println("  const formData = new FormData(form);");
  client.println("  fetch('/wifi', {");
  client.println("    method: 'POST',");
  client.println("    body: new URLSearchParams(formData)");
  client.println("  }).then(() => {");
  client.println("    alert('WiFi settings updated! Please reconnect to the new network with the updated credentials.');");
  client.println("  });");
  client.println("}");
  client.println("function handleRFIDActivation(event) {");
  client.println("  event.preventDefault();");
  client.println("  fetch('/activaterfid', { method: 'POST' })");
  client.println("    .then(response => response.text())");
  client.println("    .then(data => {");
  client.println("      alert('New RFID Card Activated Successfully');");
  client.println("    });");
  client.println("}");  
  client.println("function handleUnlock(event) {");
  client.println("  event.preventDefault();");
  client.println("  fetch('/unlock', { method: 'POST' })");
  client.println("    .then(response => response.text())");
  client.println("    .then(data => {");
  client.println("      alert('Door Unlock Command Sent Successfully');");
  client.println("    });");
  client.println("}");
  client.println("</script>");
  
  client.println("</head>");
  client.println("<body><div class='container'>");
  
  // Header
  client.println("<div class='header'>");
  client.println("<h1>Smart Door Control</h1>");
  client.println("<p>Manage door access and WiFi settings seamlessly</p>");
  client.println("</div>");
  
  // Door Control Section
  client.println("<div class='section'>");
  client.println("<h3>Door Control</h3>");
  client.println("<form onsubmit='handleUnlock(event)'>");
  client.println("<button type='submit' class='unlock-btn'>Unlock Door</button>");
  client.println("</form></div>");
  
  // RFID Activation Section
  client.println("<div class='section'>");
  client.println("<h3>RFID Card Activation</h3>");
  client.println("<form onsubmit='handleRFIDActivation(event)'>");
  client.println("<button type='submit' class='rfid-btn'>Activate New RFID Card</button>");
  client.println("</form></div>");
  
  // WiFi Configuration Section
  client.println("<div class='section'>");
  client.println("<h3>WiFi Configuration</h3>");
  client.println("<form onsubmit='submitWifi(event)'>");
  client.println("New SSID:<br><input type='text' name='ssid' maxlength='31' required><br>");
  client.println("New Password (min 8 chars):<br><input type='password' name='password' minlength='8' maxlength='63' required><br>");
  client.println("<button type='submit' class='wifi-btn'>Update WiFi Settings</button>");
  client.println("</form></div>");
  
  // Footer Section
  client.println("<div class='footer'>");
  client.println("<p>&copy; 2024 SmartTech Solutions. All rights reserved.</p>");
  client.println("<p><a href='/privacy-policy'>Privacy Policy</a> | <a href='/terms'>Terms of Service</a></p>");
  client.println("</div>");
  
  client.println("</div></body></html>");
}

void handleUnlock(WiFiClient &client) {
  // Print to serial monitor when the unlock button is pressed
  Serial.println("UNLOCK_COMMAND_RECEIVED");
  
  // Send HTTP response back to client (browser)
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/plain");
  client.println();
  client.println("Door unlock command sent successfully");
}

void handleRFIDActivation(WiFiClient &client) {
  // Print to serial monitor when RFID activation is triggered
  Serial.println("ACTIVATE_RFID_COMMAND_RECEIVED");
  
  // Send HTTP response back to client (browser)
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/plain");
  client.println();
  client.println("RFID activation mode enabled");
}

void processCredentials(WiFiClient &client) {
  String buffer = "";
  while(client.available()) {
    buffer += (char)client.read();
  }
  
  int ssidStart = buffer.indexOf("ssid=") + 5;
  int ssidEnd = buffer.indexOf("&", ssidStart);
  int passStart = buffer.indexOf("password=") + 9;
  int passEnd = buffer.indexOf("&", passStart);
  
  if (ssidEnd == -1) ssidEnd = buffer.length();
  if (passEnd == -1) passEnd = buffer.length();
  
  String new_ssid = buffer.substring(ssidStart, ssidEnd);
  String new_password = buffer.substring(passStart, passEnd);
  
  new_ssid.replace("+", " ");
  new_password.replace("+", " ");
  
  if (new_password.length() >= 8) {
    saveCredentials(new_ssid.c_str(), new_password.c_str());
    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/plain");
    client.println();
    client.println("WiFi settings updated successfully");
    
    delay(500);
    
    strncpy(current_ssid, new_ssid.c_str(), MAX_SSID_LENGTH);
    strncpy(current_password, new_password.c_str(), MAX_PASS_LENGTH);
    setupAP();
  }
}

bool isConfigured() {
  return EEPROM.read(CONFIGURED_FLAG_ADDR) == 1;
}

void loadCredentials() {
  for (int i = 0; i < MAX_SSID_LENGTH; i++) {
    current_ssid[i] = EEPROM.read(SSID_ADDR + i);
  }
  for (int i = 0; i < MAX_PASS_LENGTH; i++) {
    current_password[i] = EEPROM.read(PASS_ADDR + i);
  }
}

void saveCredentials(const char* ssid, const char* password) {
  for (int i = 0; i < strlen(ssid); i++) {
    EEPROM.write(SSID_ADDR + i, ssid[i]);
  }
  EEPROM.write(SSID_ADDR + strlen(ssid), 0);
  
  for (int i = 0; i < strlen(password); i++) {
    EEPROM.write(PASS_ADDR + i, password[i]);
  }
  EEPROM.write(PASS_ADDR + strlen(password), 0);
  
  EEPROM.write(CONFIGURED_FLAG_ADDR, 1);
}

void setupAP() {
  WiFi.beginAP(current_ssid, current_password);
  
  IPAddress IP = WiFi.localIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}