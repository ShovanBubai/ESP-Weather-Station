

#include <ESP8266WiFi.h>
#include "DHT.h"
#include <SFE_BMP180.h>
#include <Wire.h>
 
#define ALTITUDE 431.0
#define DHTPIN 0     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
 
SFE_BMP180 pressure;
DHT dht(DHTPIN, DHTTYPE);
const char* ssid     = "######"; // Your ssid
const char* password = "######"; // Your Password
 
char status;
double T,P,p0,a;

/*Enter the static ip that you want to set
IPAddress ip(192, 168, 43, 142); 
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0); 
*/
WiFiServer server(80);
void setup() {
Serial.begin(115200);
delay(100);
dht.begin();
Serial.print("Connecting to ");
Serial.println(ssid);
/*Configuring the WI-FI with the specified static IP.
WiFi.config(ip, gateway, subnet);
*/
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
 
Serial.println("");
Serial.println("WiFi is connected");
server.begin();
Serial.println("Server started");
 
 
Serial.println(WiFi.localIP());
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
  delay(1000);
}
 
void loop() {
    status = pressure.getPressure(P,T);
    if (status != 0)
    {
p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
Serial.print("relative (sea-level) pressure: ");
Serial.print(p0,2);
Serial.print(" mb, ");
Serial.print("\n");
Serial.print("Temperature: ");
Serial.print(dht.readTemperature());
Serial.print("°C");
Serial.print("\n");
}
 
float h = dht.readHumidity();
// Read temperature as Celsius (the default)
float t = dht.readTemperature();
// Read temperature as Fahrenheit (isFahrenheit = true)
float f = dht.readTemperature(true);
// Altitude
float a = p0/10;

  
WiFiClient client = server.available();
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");  // the connection will be closed after completion of the response
client.println("Refresh: 10");  // update the page after 10 sec
client.println();
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<style>html { font-family: Cairo; display: block; margin: 0px auto; text-align: center;color: #333333; background-color: #ccffb3;}");
client.println("body{margin-top: 50px;}");
client.println("h1 {margin: 50px auto 30px; font-size: 45px; text-align: center;}");
client.println(".side_adjust{display: inline-block;vertical-align: middle;position: relative;}");
client.println(".text1{font-weight: 180; padding-left: 0px; font-size: 32px; width: 100px; text-align: left; color: #3498db;}");
client.println(".data1{font-weight: 180; padding-left: 80px; font-size: 30px;color: #3498db;}");
client.println(".text2{font-weight: 180; padding-left: 0px; font-size: 32px; width: 100px; text-align: left; color: #ff6600;}");
client.println(".data2{font-weight: 180; padding-left: 80px; font-size: 30px;color: #ff6600;}");
client.println(".text3{font-weight: 180; padding-left: 0px; font-size: 32px; width: 100px; text-align: left; color: #0066ff;}");
client.println(".data3{font-weight: 180; padding-left: 80px; font-size: 30px;color: #0066ff;}");
client.println(".text4{font-weight: 180; padding-left: 0px; font-size: 32px; width: 100px; text-align: left; color: #ff00f7;}");
client.println(".data4{font-weight: 180; padding-left: 80px; font-size: 30px;color: #ff00f7;}");
client.println(".data{padding: 10px;}");
client.println("</style>");
client.println("</head>");
client.println("<body>");
client.println("<div id=\"webpage\">");   
client.println("<h1>Welcome to ESP Weather Station</h1>");
client.println("<div class=\"data\">");
client.println("<div class=\"side_adjust text1\">Humidity:</div>");
client.println("<div class=\"side_adjust data1\">");
client.print(h);
client.println("<div class=\"side_adjust text1\">%</div>");
client.println("</div>");
client.println("<div class=\"data\">");
client.println("<div class=\"side_adjust text2\">Temperature:</div>");
client.println("<div class=\"side_adjust data2\">");
client.print(t);
client.println("<div class=\"side_adjust text2\">&#176;C</div>");
client.print(f);
client.println("<div class=\"side_adjust text2\">&#176;F</div>");
client.println("</div>");
client.println("<div class=\"data\">");
client.println("<div class=\"side_adjust text3\">Pressure:</div>");
client.println("<div class=\"side_adjust data3\">");
client.print(p0,2);
client.println("<div class=\"side_adjust text3\">mb</div>");
client.println("</div>");
client.println("<div class=\"data\">");
client.println("<div class=\"side_adjust text4\">Altitude:</div>");
client.println("<div class=\"side_adjust data4\">");
client.print(a);
client.println("<div class=\"side_adjust text4\">m</div>");
client.println("</div>");
client.println("</div>");
client.println("</body>");
client.println("</html>");
 delay(4000);
}
