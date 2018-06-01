#define LED_PIN 10
#define LED_SWITCH 2

void setup(){
  pinMode(LED_PIN,OUTPUT); //10番ピンを出力に設定

  Serial.begin(9600);//シリアル通信のレートを9600に設定
}

void loop(){

  int inputchar;      //入力状態の読み取りに使う
  int val=0; //0か1を保持

  inputchar = Serial.read();  //シリアル通信で送信された値を読み取る

  if(inputchar!=-1){
    if(inputchar == 's'){  //sが入力された場合
       if(digitalRead(LED_SWITCH) == LOW){ //スイッチオフの時
          digitalWrite(LED_PIN,HIGH); //LED光る
          val = 1;
        }else{
          digitalWrite(LED_PIN,LOW);
          val = 0;
        }
    }
  }
  else{
  }
}
