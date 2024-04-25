/*
  https://github.com/tugberkyildirim
  
  In this project, 4 relays are controlled by WiFi AP with Nodemcu.  
  Relay 1 D5,
  Relay 2 D6,
  Relay 3 D7,
  Relay 4 is connected to pin D8.

  NOTE: If you don't have the "ESPAsyncTCP" and "ESPAsyncWebServer" libraries, they are available in the "lib" folder, don't forget to add them.

  Bu projede Nodemcu ile 4 adet röle WiFi AP ile kontrol edilmektedir.  
  Röle 1 D5,
  Röle 2 D6,
  Röle 3 D7,
  Röle 4 D8 numaralı pine bağlı.

  NOT:  "ESPAsyncTCP" ve "ESPAsyncWebServer" kütüphaneleri sizde ekli değilse "lib" klasörünün içinde mevcut, onları eklemeyi unutmayın.
*/

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define PORT_1 D5 //Relay 1
#define PORT_2 D6 //Relay 2
#define PORT_3 D7 //Relay 3
#define PORT_4 D8 //Relay 4

const char* ssid = "NODEMCU";
const char* password = "nodemcu123456";

const int serverPort = 80;

bool relayState1 = LOW;
bool relayState2 = LOW;
bool relayState3 = LOW;
bool relayState4 = LOW;

AsyncWebServer server(serverPort);

void setup() {
  pinMode(PORT_1, OUTPUT);
  pinMode(PORT_2, OUTPUT);
  pinMode(PORT_3, OUTPUT);
  pinMode(PORT_4, OUTPUT);

  digitalWrite(PORT_1, relayState1);
  digitalWrite(PORT_2, relayState2);
  digitalWrite(PORT_3, relayState3);
  digitalWrite(PORT_4, relayState4);

  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/toggle1", HTTP_GET, toggleRelay1);
  server.on("/toggle2", HTTP_GET, toggleRelay2);
  server.on("/toggle3", HTTP_GET, toggleRelay3);
  server.on("/toggle4", HTTP_GET, toggleRelay4);

  server.begin();
}

void loop() {}

void handleRoot(AsyncWebServerRequest *request) {
String html = "<!DOCTYPE html>\
                <html lang=\"en\">\
                <head>\
                  <meta charset=\"UTF-8\">\
                  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
                  <title>Relay Control</title>\
                  <style>\
                    body {\
                      font-family: Arial, sans-serif;\
                      margin: 0;\
                      padding: 0;\
                      display: flex;\
                      justify-content: center;\
                      align-items: center;\
                      height: 100vh;\
                      background-color: #f0f0f0;\
                    }\
                    .container {\
                      display: flex;\
                      flex-direction: column;\
                      align-items: center;\
                    }\
                    .normal-button {\
                      display: inline-block;\
                      width: 100px;\
                      height: 50px;\
                      background-color: #ccc;\
                      border-radius: 5px;\
                      position: relative;\
                      cursor: pointer;\
                      text-align: center;\
                      line-height: 50px;\
                      font-weight: bold;\
                      color: #666;\
                      transition: background-color 0.3s ease, color 0.3s ease;\
                      border: none;\
                      margin-bottom: 20px;\
                      margin-right: 20px;\
                    }\
                    .normal-button.active {\
                      background-color: #007bff;\
                      color: #fff;\
                    }\
                  </style>\
                </head>\
                <body>\
                  <div class=\"container\">\
                  <h4>Port 1</h4>\
                    <div>\
                      <button class=\"normal-button\" id=\"port1\" onclick=\"toggleRelay(1)\">";
html += relayState1 ? "On" : "Off";
html += "</button>\
                    </div>\
                    <h4>Port 2</h4>\
                    <div>\
                      <button class=\"normal-button\" id=\"port2\" onclick=\"toggleRelay(2)\">";
html += relayState2 ? "On" : "Off";
html += "</button>\
                    </div>\
                    <h4>Port 3</h4>\
                    <div>\
                      <button class=\"normal-button\" id=\"port3\" onclick=\"toggleRelay(3)\">";
html += relayState3 ? "On" : "Off";
html += "</button>\
                    </div>\
                      <h4>Port 4</h4>\
                    <div>\
                      <button class=\"normal-button\" id=\"port4\" onclick=\"toggleRelay(4)\">";
html += relayState4 ? "On" : "Off";
html += "</button>\
                    </div>\
                  </div>\
                  <script>\
                    window.addEventListener('load', function () {\
                      const buttons = document.querySelectorAll('.normal-button');\
                      buttons.forEach(function(button, index) {\
                        const xhttp = new XMLHttpRequest();\
                        xhttp.onreadystatechange = function() {\
                          if (this.readyState == 4 && this.status == 200) {\
                            const toggleButton = button.parentElement;\
                            const checkbox = toggleButton.querySelector('.checkbox');\
                            checkbox.checked = !checkbox.checked;\
                            if (checkbox.checked) {\
                              button.classList.add('active');\
                              button.innerHTML = \"On\";\
                            } else {\
                              button.classList.remove('active');\
                              button.innerHTML = \"Off\";\
                            }\
                          }\
                        };\
                      });\
                    });\
                    function toggleRelay(relayNum) {\
                      const xhttp = new XMLHttpRequest();\
                      xhttp.onreadystatechange = function() {\
                        if (this.readyState == 4 && this.status == 200) {\
                          const toggleButton = document.getElementById('toggle' + relayNum);\
                          const button = toggleButton.querySelector('.normal-button');\
                          const checkbox = toggleButton.querySelector('.checkbox');\
                          checkbox.checked = !checkbox.checked;\
                          if (checkbox.checked) {\
                            button.classList.add('active');\
                            button.innerHTML = \"On\";\
                          } else {\
                            button.classList.remove('active');\
                            button.innerHTML = \"Off\";\
                          }\
                        }\
                      };\
                      location.reload();\
                      xhttp.open(\"GET\", \"/toggle\" + relayNum, true);\
                      xhttp.send();\
                    }\
                  </script>\
                </body>\
                </html>";
  request->send(200, "text/html", html);
}

void toggleRelay1(AsyncWebServerRequest *request) {
  relayState1 = !relayState1;
  digitalWrite(PORT_1, relayState1);
  request->send(200, "text/plain", "OK");
}

void toggleRelay2(AsyncWebServerRequest *request) {
  relayState2 = !relayState2;
  digitalWrite(PORT_2, relayState2);
  request->send(200, "text/plain", "OK");
}

void toggleRelay3(AsyncWebServerRequest *request) {
  relayState3 = !relayState3;
  digitalWrite(PORT_3, relayState3);
  request->send(200, "text/plain", "OK");
}

void toggleRelay4(AsyncWebServerRequest *request) {
  relayState4 = !relayState4;
  digitalWrite(PORT_4, relayState4);
  request->send(200, "text/plain", "OK");
}
