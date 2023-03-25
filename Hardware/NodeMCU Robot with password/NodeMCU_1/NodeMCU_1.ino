  /////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP8266     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <ESP8266WiFi.h>

String  i;
WiFiServer server(80);

void setup()
{
  i = "stop";
  Serial.begin(57600);
  WiFi.disconnect();
  delay(3000);
  WiFi.begin("ishit", "ishukapunet");
  Serial.println("Connecting to WiFi");
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(300);
    Serial.println("....");

  }
  Serial.println("Connected to WiFi");
  Serial.println((WiFi.localIP().toString()));
  server.begin();
}


void loop()
{

  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  i = (client.readStringUntil('\r'));
  i.remove(0, 5);
  i.remove(i.length() - 9, 9);


  if (i == "front") {

    Serial.println("F");

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    delay(1);
  }


  if (i == "left") {

    Serial.println("L");

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    delay(1);
  }


  if (i == "right") {

    Serial.println("R");

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    delay(1);
  }


  if (i == "back") {

    Serial.println("B");

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    delay(1);
  }


  if (i == "stop") {

    Serial.println("S");

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    delay(1);
  }


  if (i == "automodeon") {

    Serial.println("A");

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    delay(1);
  }

  if (i == "automodeoff") {

    Serial.println("O");

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    delay(1);
  }

}
