// IOTLT 20161011 for arduino yun
#include <Bridge.h>
#include <HttpClient.h>

const int LED = 13;
const int PIR = 2;
int ledStatus = 0;

void setup() {
  // put your setup code here, to run once:
  Bridge.begin();
  Serial.begin(9600);
  pinMode(PIR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (ledStatus == 1) {
    if(!digitalRead(PIR)) {
      ledStatus = 0;
    }

  } else {
    if(digitalRead(PIR)) {
      HttpClient client;
      client.get("http://***.***.***.***/"); // put your gr-sakura ip address
      client.get("http://*****.herokuapp.com/alert/intrusion?key=******"); // put your heroku url
      ledStatus = 1;
    }
  }
}
