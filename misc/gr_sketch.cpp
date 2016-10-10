/* IOTLT 20161011 for sakuraboard */
#include <Arduino.h>
#include <Ethernet.h>

#define INTERVAL 100

byte mac[] = { 0x**, 0x**, 0x**, 0x**, 0x**, 0x** }; // put any mac address
IPAddress ip(***.***.***.***); // put your gr-sakura ipaddress
EthernetServer server(80);
int emergencyCount = 0;

void setup() {
	// led pin initialize
	pinMode(PIN_LED0,OUTPUT);
    pinMode(PIN_LED1,OUTPUT);
    pinMode(PIN_LED2,OUTPUT);
    pinMode(PIN_LED3,OUTPUT);

	// web server initialize
	Ethernet.begin(mac, ip);
	server.begin();
}

void loop() {
	// alert
	if (emergencyCount > 0) {
	    digitalWrite(PIN_LED0, 1);
	    delay(INTERVAL);
	    digitalWrite(PIN_LED1, 1);
	    delay(INTERVAL);
	    digitalWrite(PIN_LED2, 1);
	    delay(INTERVAL);
	    digitalWrite(PIN_LED3, 1);
	    delay(INTERVAL);
	    digitalWrite(PIN_LED0, 0);
	    delay(INTERVAL);
	    digitalWrite(PIN_LED1, 0);
	    delay(INTERVAL);
	    digitalWrite(PIN_LED2, 0);
	    delay(INTERVAL);
	    digitalWrite(PIN_LED3, 0);
	    delay(INTERVAL);
	    emergencyCount--;

	} else {
		// wait web request
		EthernetClient client = server.available();
		if (client) {
			boolean currentLineIsBlank = true;
			while (client.connected()) {
				if (client.available()) {
					char c = client.read();
					if (c == '\n' && currentLineIsBlank) {
						client.println("HTTP/1.1 200 OK");
						client.println("Content-Type: text/html");
						client.println("Connection: close");
						client.println();
						client.println("");
						client.println("");
						client.println("ok");
						client.println("");
						emergencyCount = 10;
						break;
					}
					if (c == '\n') {
						currentLineIsBlank = true;
					} else if (c != '\r') {
						currentLineIsBlank = false;
					}
				}
			}
			client.stop();
		}
	}
}
