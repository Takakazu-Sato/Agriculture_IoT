#include <DHT.h>
#define DHTTYPE DHT22
#define DHT22_PIN 7
DHT dht(DHT22_PIN, DHTTYPE);

void setup() {
  pinMode(DHT22_PIN, INPUT);      
  Serial.begin(9600);
}

char ch[10];
char ct[10];

void loop()
{
  float h  = dht.readHumidity() ;
  float t  = 5.0/9.0*(dht.readTemperature(true)-32.0); // fahrenheit -> celsius
  dtostrf(h, 6, 2, ch);
  dtostrf(t, 6, 2, ct);

  String postData = "{humidity:";
  postData.concat(ch);
  postData.concat(",temperture:");
  postData.concat(ct);
  postData.concat("}");

//  Serial.print("POST /api/measurements HTTP/1.1\r\n");
//  Serial.print("Content-Length: " + String(postData.length()) + "\r\n\r\n");
  Serial.println(postData);

  delay(1000);

}
