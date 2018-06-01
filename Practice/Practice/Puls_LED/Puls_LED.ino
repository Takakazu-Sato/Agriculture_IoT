//LEDをつなぐピンを定義
#define LED_PIN1 13
#define LED_PIN2 10

void setup() {
  //LEDのピンを出力に
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
}

//メインループ
void loop() {
  //LED1を点灯
  digitalWrite(LED_PIN1, HIGH);
  //LED2を点灯
  digitalWrite(LED_PIN2, HIGH);
  //1ミリ秒遅延
  delay(1);
  //LED1を消灯
  digitalWrite(LED_PIN1, LOW);
  //LED2を点灯
  digitalWrite(LED_PIN2, HIGH);
  //15ミリ秒遅延
  delay(1);
}
