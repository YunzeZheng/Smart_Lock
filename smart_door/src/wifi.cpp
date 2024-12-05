#include <Arduino.h>
#include "main.h"

// WiFiServer server(80);

// void wifi_setup(const char Set_ssid[], const char Set_password[]) {
//   int attempts = 0;
//   // Wait for the connection
//   while (WiFi.status() != WL_CONNECTED && attempts < 5) {
//     lcd_show_message("Connecting to Wi-Fi...");
//     Serial.println("Attempting to connect...");
//     WiFi.begin(Set_ssid, Set_password);
//     delay(1000);
//     attempts++;
//   }
//   lcd_FirstCol("WIFI complete");
// }


// const char* htmlCode = R"rawliteral(
// <html>
//   <body>
//     <h2>WiFi Setup</h2>
//     <form action="/submit" method="POST">
//       SSID: <input type="text" name="ssid"><br>
//       Password: <input type="password" name="password"><br>
//       <input type="submit" value="Connect">
//     </form>
//   </body>
// </html>
// )rawliteral";

// String HTTPValue(String request, String key) {
//   int start = request.indexOf(key + "=");
//   if (start == -1) return "";
//   start += key.length() + 1;
//   int end = request.indexOf("&", start);
//   if (end == -1) end = request.indexOf(" ", start);
//   return request.substring(start, end);
// }

// void handleClient() {
//   WiFiClient client = server.available();

//   if (client) {
//     String request = "";
//     while (client.available()) {
//       char c = client.read();  // Read client data
//       request += c;
//     }

//       if (request.indexOf("POST /submit") != -1) {
//         String ssid = HTTPValue(request, "ssid");
//         String password = HTTPValue(request, "password");

//       // Display
//         lcd_FirstCol(ssid.c_str());
//         lcd_SecondCol(password.c_str());

//       // Connect to the provided WiFi network
//         wifi_setup(ssid.c_str(),password.c_str());

//       // Send the appropriate response to the client
//         client.println("HTTP/1.1 200 OK");
//         client.println("Content-Type: text/html");
//         client.println("Connection: close");
//         client.println();

//         delay(4);  // Allow time to send the response
//         client.stop();  // Close the connection
//       }
//     }
// }