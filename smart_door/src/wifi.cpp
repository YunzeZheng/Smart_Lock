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
  Serial.begin(9600);
  
  // Check if device has been configured before
  if (!isConfigured()) {
    // First time setup - use default credentials
    strncpy(current_ssid, DEFAULT_SSID, MAX_SSID_LENGTH);
    strncpy(current_password, DEFAULT_PASSWORD, MAX_PASS_LENGTH);
  } else {
    // Load credentials from EEPROM
    loadCredentials();
  }
  
  // Start AP
  setupAP();
  server.begin();
  
  // Print current WiFi credentials
  printCurrentWiFiCredentials();

  Serial.println("Server started");
}
void printCurrentWiFiCredentials() {
  Serial.println("Current WiFi Credentials:");
  Serial.print("SSID: ");
  Serial.println(current_ssid);
  Serial.print("Password: ");
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
            // Check if this is a POST request
            if (request.indexOf("POST /unlock") >= 0) {
              handleUnlock(client);
            } else if (request.indexOf("POST /wifi") >= 0) {
              processCredentials(client);
            } else {
              // Default to showing the main page
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
  // Send HTTP headers
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  // Send HTML page
  client.println("<!DOCTYPE html>");
  client.println("<html lang='en'>");
  client.println("<head>");
  client.println("<meta charset='UTF-8'>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
  client.println("<title>Smart Door Control</title>");
  client.println("<style>");
  client.println("body { font-family: 'Roboto', sans-serif; margin: 0; padding: 0; background-color: #f4f6f9; color: #333; line-height: 1.6; }");
  client.println("header { background: linear-gradient(90deg, #0066cc, #005bb5); color: white; padding: 20px; text-align: center; font-size: 1.8em; font-weight: 600; }");
  client.println(".container { max-width: 90%; margin: 40px auto; padding: 20px; background: white; border-radius: 12px; box-shadow: 0 8px 20px rgba(0, 0, 0, 0.1); }");
  client.println(".section { margin: 30px 0; }");
  client.println(".section h3 { margin-bottom: 20px; font-size: 1.5em; color: #0066cc; border-bottom: 3px solid #0066cc; padding-bottom: 5px; }");
  client.println(".form-group { margin-bottom: 20px; }");
  client.println(".form-group label { display: block; margin-bottom: 5px; font-weight: bold; color: #444; }");
  client.println("input, button { width: 100%; padding: 14px; margin-top: 8px; border-radius: 6px; border: 1px solid #ccc; font-size: 1em; box-sizing: border-box; }");
  client.println("input:focus { border-color: #0066cc; outline: none; }");
  client.println("button { background: linear-gradient(90deg, #0066cc, #005bb5); color: white; border: none; font-weight: bold; cursor: pointer; transition: background 0.3s ease; }");
  client.println("button:hover { background: linear-gradient(90deg, #005bb5, #004d99); }");
  client.println(".unlock-btn { background: linear-gradient(90deg, #ff9933, #ff7f00); }");
  client.println(".unlock-btn:hover { background: linear-gradient(90deg, #ff7f00, #e67300); }");
  client.println("@media (min-width: 768px) { .container { max-width: 600px; } }");
  client.println("footer { text-align: center; padding: 20px; font-size: 0.9em; color: #777; background-color: #f4f6f9; margin-top: 40px; }");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<header>Smart Door Control & WiFi Setup</header>");
  client.println("<div class='container'>");

  // Door Control Section
  client.println("<div class='section'>");
  client.println("<h3>Door Control</h3>");
  client.println("<form action='/unlock' method='POST'>");
  client.println("<button type='submit' class='unlock-btn'>Unlock Door</button>");
  client.println("</form>");
  client.println("</div>");

  // WiFi Configuration Section
  client.println("<div class='section'>");
  client.println("<h3>WiFi Configuration</h3>");
  client.println("<form action='/wifi' method='POST'>");
  client.println("<div class='form-group'>");
  client.println("<label for='wifi-name'>New WiFi Name</label>");
  client.println("<input type='text' id='wifi-name' name='ssid' maxlength='31' placeholder='Enter your new WiFi name' required>");
  client.println("</div>");
  client.println("<div class='form-group'>");
  client.println("<label for='password'>New Password</label>");
  client.println("<input type='password' id='password' name='password' minlength='8' maxlength='63' placeholder='Enter your new WiFi password' required>");
  client.println("</div>");
  client.println("<button type='submit'>Update WiFi Settings</button>");
  client.println("</form>");
  client.println("</div>");

  client.println("</div>");
  client.println("<footer>&copy; 2024 Smart Lock - All Rights Reserved</footer>");
  client.println("</body>");
  client.println("</html>");
}

void handleUnlock(WiFiClient &client) {
  // Send message to Serial for door control
  Serial.println("UNLOCK_COMMAND_RECEIVED");
  
  // Send success response back to client
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.println("<html><body>");
  client.println("<script>");
  client.println("alert('Door unlock command sent!');");
  client.println("window.location.href = '/';");  // Redirect back to main page
  client.println("</script>");
  client.println("</body></html>");
}

void processCredentials(WiFiClient &client) {
  String buffer = "";
  while(client.available()) {
    buffer += (char)client.read();
  }
  
  // Look for POST data
  int ssidStart = buffer.indexOf("ssid=") + 5;
  int ssidEnd = buffer.indexOf("&", ssidStart);
  int passStart = buffer.indexOf("password=") + 9;
  int passEnd = buffer.indexOf("&", passStart);
  
  if (ssidEnd == -1) ssidEnd = buffer.length();
  if (passEnd == -1) passEnd = buffer.length();
  
  String new_ssid = buffer.substring(ssidStart, ssidEnd);
  String new_password = buffer.substring(passStart, passEnd);
  
  // URL decode the strings
  new_ssid.replace("+", " ");
  new_password.replace("+", " ");
  
  // Save new credentials if valid
  if (new_password.length() >= 8) {
    saveCredentials(new_ssid.c_str(), new_password.c_str());
    
    // Send success response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.println("<html><body><h2>WiFi Settings Updated!</h2>Restarting AP with new credentials...</body></html>");
    
    // Short delay to allow response to be sent
    delay(1000);
    
    // Restart AP with new credentials
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
  // Write SSID and password to EEPROM
  for (int i = 0; i < strlen(ssid); i++) {
    EEPROM.write(SSID_ADDR + i, ssid[i]);
  }
  EEPROM.write(SSID_ADDR + strlen(ssid), 0);
  
  for (int i = 0; i < strlen(password); i++) {
    EEPROM.write(PASS_ADDR + i, password[i]);
  }
  EEPROM.write(PASS_ADDR + strlen(password), 0);
  
  // Set configured flag
  EEPROM.write(CONFIGURED_FLAG_ADDR, 1);
}

void setupAP() {
  WiFi.beginAP(current_ssid, current_password);
  
  IPAddress IP = WiFi.localIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

//#include <Arduino.h>
//#include "main.h"

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

void printCurrentWiFiCredentials() {
  Serial.println("Current WiFi Credentials:");
  Serial.print("SSID: ");
  Serial.println(current_ssid);
  Serial.print("Password: ");
  Serial.println(current_password);
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

void setupAP() {
  WiFi.beginAP(current_ssid, current_password);
  
  IPAddress IP = WiFi.localIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void handleUnlock(WiFiClient &client) {
  // Send message to Serial for door control
  bool locker_state = true;
  
  // Send success response back to client
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.println("<html><body>");
  client.println("<script>");
  client.println("alert('Door unlock command sent!');");
  client.println("window.location.href = '/';");  // Redirect back to main page
  client.println("</script>");
  client.println("</body></html>");
}

void saveCredentials(const char* ssid, const char* password) {
  // Write SSID and password to EEPROM
  for (int i = 0; i < strlen(ssid); i++) {
    EEPROM.write(SSID_ADDR + i, ssid[i]);
  }
  EEPROM.write(SSID_ADDR + strlen(ssid), 0);
  
  for (int i = 0; i < strlen(password); i++) {
    EEPROM.write(PASS_ADDR + i, password[i]);
  }
  EEPROM.write(PASS_ADDR + strlen(password), 0);
  
  // Set configured flag
  EEPROM.write(CONFIGURED_FLAG_ADDR, 1);
}

void processCredentials(WiFiClient &client) {
  String buffer = "";
  while(client.available()) {
    buffer += (char)client.read();
  }
  
  // Look for POST data
  int ssidStart = buffer.indexOf("ssid=") + 5;
  int ssidEnd = buffer.indexOf("&", ssidStart);
  int passStart = buffer.indexOf("password=") + 9;
  int passEnd = buffer.indexOf("&", passStart);
  
  if (ssidEnd == -1) ssidEnd = buffer.length();
  if (passEnd == -1) passEnd = buffer.length();
  
  String new_ssid = buffer.substring(ssidStart, ssidEnd);
  String new_password = buffer.substring(passStart, passEnd);
  
  // URL decode the strings
  new_ssid.replace("+", " ");
  new_password.replace("+", " ");
  
  // Save new credentials if valid
  if (new_password.length() >= 8) {
    saveCredentials(new_ssid.c_str(), new_password.c_str());
    
    // Send success response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.println("<html><body><h2>WiFi Settings Updated!</h2>Restarting AP with new credentials...</body></html>");
    
    // Short delay to allow response to be sent
    delay(1000);
    
    // Restart AP with new credentials
    strncpy(current_ssid, new_ssid.c_str(), MAX_SSID_LENGTH);
    strncpy(current_password, new_password.c_str(), MAX_PASS_LENGTH);
    setupAP();
  }
}

void sendWebPage(WiFiClient &client) {
  // Send HTTP headers
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  // Send HTML page
  client.println("<!DOCTYPE html>");
  client.println("<html lang='en'>");
  client.println("<head>");
  client.println("<meta charset='UTF-8'>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
  client.println("<title>Smart Door Control</title>");
  client.println("<style>");
  client.println("body { font-family: 'Roboto', sans-serif; margin: 0; padding: 0; background-color: #f4f6f9; color: #333; line-height: 1.6; }");
  client.println("header { background: linear-gradient(90deg, #0066cc, #005bb5); color: white; padding: 20px; text-align: center; font-size: 1.8em; font-weight: 600; }");
  client.println(".container { max-width: 90%; margin: 40px auto; padding: 20px; background: white; border-radius: 12px; box-shadow: 0 8px 20px rgba(0, 0, 0, 0.1); }");
  client.println(".section { margin: 30px 0; }");
  client.println(".section h3 { margin-bottom: 20px; font-size: 1.5em; color: #0066cc; border-bottom: 3px solid #0066cc; padding-bottom: 5px; }");
  client.println(".form-group { margin-bottom: 20px; }");
  client.println(".form-group label { display: block; margin-bottom: 5px; font-weight: bold; color: #444; }");
  client.println("input, button { width: 100%; padding: 14px; margin-top: 8px; border-radius: 6px; border: 1px solid #ccc; font-size: 1em; box-sizing: border-box; }");
  client.println("input:focus { border-color: #0066cc; outline: none; }");
  client.println("button { background: linear-gradient(90deg, #0066cc, #005bb5); color: white; border: none; font-weight: bold; cursor: pointer; transition: background 0.3s ease; }");
  client.println("button:hover { background: linear-gradient(90deg, #005bb5, #004d99); }");
  client.println(".unlock-btn { background: linear-gradient(90deg, #ff9933, #ff7f00); }");
  client.println(".unlock-btn:hover { background: linear-gradient(90deg, #ff7f00, #e67300); }");
  client.println("@media (min-width: 768px) { .container { max-width: 600px; } }");
  client.println("footer { text-align: center; padding: 20px; font-size: 0.9em; color: #777; background-color: #f4f6f9; margin-top: 40px; }");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<header>Smart Door Control & WiFi Setup</header>");
  client.println("<div class='container'>");

  // Door Control Section
  client.println("<div class='section'>");
  client.println("<h3>Door Control</h3>");
  client.println("<form action='/unlock' method='POST'>");
  client.println("<button type='submit' class='unlock-btn'>Unlock Door</button>");
  client.println("</form>");
  client.println("</div>");

  // WiFi Configuration Section
  client.println("<div class='section'>");
  client.println("<h3>WiFi Configuration</h3>");
  client.println("<form action='/wifi' method='POST'>");
  client.println("<div class='form-group'>");
  client.println("<label for='wifi-name'>New WiFi Name</label>");
  client.println("<input type='text' id='wifi-name' name='ssid' maxlength='31' placeholder='Enter your new WiFi name' required>");
  client.println("</div>");
  client.println("<div class='form-group'>");
  client.println("<label for='password'>New Password</label>");
  client.println("<input type='password' id='password' name='password' minlength='8' maxlength='63' placeholder='Enter your new WiFi password' required>");
  client.println("</div>");
  client.println("<button type='submit'>Update WiFi Settings</button>");
  client.println("</form>");
  client.println("</div>");

  client.println("</div>");
  client.println("<footer>&copy; 2024 Smart Lock - All Rights Reserved</footer>");
  client.println("</body>");
  client.println("</html>");
}


void wifi_setup() {
  // Check if device has been configured before
  if (!isConfigured()) {
    // First time setup - use default credentials
    strncpy(current_ssid, DEFAULT_SSID, MAX_SSID_LENGTH);
    strncpy(current_password, DEFAULT_PASSWORD, MAX_PASS_LENGTH);
  } else {
    // Load credentials from EEPROM
    loadCredentials();
  }
  
  // Start AP
  setupAP();
  server.begin();
  
  // Print current WiFi credentials
  printCurrentWiFiCredentials();

  Serial.println("Server started");
}


void ClientOn() {
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
            // Check if this is a POST request
            if (request.indexOf("POST /unlock") >= 0) {
              handleUnlock(client);
            } else if (request.indexOf("POST /wifi") >= 0) {
              processCredentials(client);
            } else {
              // Default to showing the main page
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
