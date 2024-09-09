/* 
 
ThingSpeak_Read_Data Test
 
 
For the Xpert Automatix ESP32 Development Board.
 
created Sep 2024
by XpertAutomatix
 
This example code is in the public domain.
 
 https://github.com/Xpertautomatix/Products
 
*/

#include <ThingSpeak.h>
#include <WiFi.h>

#define CHANNEL_ID YOUR CHANNEL ID  // add your channel ID  
#define CHANNEL_R_API_KEY YOUR CHANNEL READ API KEY //add your channel Read API key
#define CHANNEL_W_API_KEY YOUR CHANNEL WRITE  API KEY //add your channel Write API key
WiFiClient client;
int counter = 0;                // This data to storing in Thingspeak 
//WIFI STATION USER NAME PASSWORD
const char* WIFI_ssid     = "Mr.KT";
const char* WIFI_password = "pavi1911";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //--------------------------------------------------------------------------------------------//
  ThingSpeak.begin(client);
  //--------------------------------------------------------------------------------------------//

  //clear old config
  WiFi.disconnect(true);        //disable wifi station 
  WiFi.softAPdisconnect(true);  //disable wifi access point 

  pinMode(2, OUTPUT);           // Inbuilt LED light
  delay(1000);                  // Some delay
//---------------------------------------------------------------------------------------------------//
  Serial.println("PROJECT NAME      : ESP32 WIFI STATION");
  Serial.print  ("WIFI SSID         : ");
  Serial.println(WIFI_ssid);
  Serial.print  ("WIFI PASSWORD     : ");
  Serial.println(WIFI_password);
//----------------------------------------------------------------------------------------------------//
  digitalWrite(2,HIGH);
  delay(500);
  digitalWrite(2,LOW);

  CONNECT_WiFi();
}
//----------------------------------------------------------------------------------------------------//
void loop() {
  // put your main code here, to run repeatedly:
  while ((!(WiFi.status() == WL_CONNECTED)))
    {
      CONNECT_WiFi();
    }
    //YOUR CODE HERE...
  //----------------------------------------------------------------------------------------------//
    counter++;      // counter increment the  value every 16 sec
    ThingSpeak.writeField(CHANNEL_ID, 3, counter, CHANNEL_W_API_KEY); //channel_ID // Field_NO // Data // Write API Key //
  //----------------------------------------------------------------------------------------------//
    String Field_3 = ThingSpeak.readStringField(CHANNEL_ID, 3, CHANNEL_R_API_KEY);
    Serial.print("Field3: ");
    Serial.println(Field_3);
  //--------------------------------------------------------------------------------------------------//
    delay(15000);
  //-----------------------------------------------------------------------------------------------//
}
//-----------------------------------------------------------------------------------------------------//
void CONNECT_WiFi()
{ 
  Serial.println("Connecting to WIFi");
  int i=0;

  WiFi.mode(WIFI_STA);
  // IF YOU COFIG THEN USE THIS // ----- // WiFi.config(WIFI_local_IP, WIFI_gateway, WIFI_subnet, WIFI_primaryDNS, WIFI_secondaryDNS);
  WiFi.begin(WIFI_ssid, WIFI_password);
  
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    digitalWrite(2,HIGH);
    delay(300);
    digitalWrite(2,LOW);
    delay(200);
    
    Serial.print(".");
    delay(1000);
  }

  digitalWrite(2,HIGH);
  delay(500);
  digitalWrite(2,LOW);

  Serial.println("WIFI connected");

  Serial.print("WIFI IP ADDRESS       : ");
  Serial.println(WiFi.localIP());

  Serial.print("WIFI Strength         : ");
  Serial.println(WiFi.RSSI());

  Serial.print("ESP32 MAC address     : ");
  Serial.println(WiFi.macAddress());
}