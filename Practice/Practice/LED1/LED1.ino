#define LED_PIN 10
#define LED_SWITCH 2

void setup() {
  pinMode(LED_SWITCH,INPUT);
  pinMode(LED_PIN,OUTPUT);
}

void loop() {
  if(digitalRead(LED_SWITCH) == HIGH){
     digitalWrite(LED_PIN,HIGH);
     delay(500);
  }else{
     digitalWrite(LED_PIN,LOW);
     delay(500);
  }
}
