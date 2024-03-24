//----OnLooker----//

#include <WiFi.h>
#include "sMQTTBroker.h"

sMQTTBroker broker;

unsigned long Time;
unsigned long freeRam;

const char* ssid     = "";
const char* password = "";

IPAddress local_IP(192, 168, 1, 50);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

void setup(){
 	Serial.begin(115200);

  	if (!WiFi.config(local_IP, gateway, subnet)) {
    		Serial.println("STA Failed to configure");
  	}

  	Serial.print("Connecting to ");
  	Serial.println(ssid);

	WiFi.begin(ssid, password);

  	while (WiFi.status() != WL_CONNECTED) {
    		delay(500);
    		Serial.print(".");
	}
	Serial.print("IP:\t");
	Serial.println(WiFi.localIP());

	const unsigned short mqttPort = 1883;
	broker.init(mqttPort);

}

void loop(){

	broker.update();

	if(millis()-Time > 1000){
		Time=millis();

		if(ESP.getFreeHeap() != freeRam){
			freeRam = ESP.getFreeHeap();
			Serial.print("RAM: ");
			Serial.println(freeRam);
		}
	}
}