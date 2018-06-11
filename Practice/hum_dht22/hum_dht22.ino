/*********************************************************************

        AM2302 DHT22の簡易湿度計 for Arduino
        (sparkfun SEN-10167 Aosong RHT03 AM2302 MaxDetect RHT03)

本ソースリストおよびソフトウェアは、ライセンスフリーです。
個人での利用は自由に行えます。著作権表示の改変は禁止します。

                               Copyright (c) 2012-2014 Wataru KUNINO
                               http://www.geocities.jp/bokunimowakaru/
*********************************************************************/
/*
参考文献：
・DHT 11 Humidity & Temperature Sensor(D-Robotics社HDT用 IF)
	D-Robotics	7/30/2010
・AM2302 Product Manual
	Aosong	(www.aosong.com)
・Grove - Temp&Humi Sensor [SEN11301P]	Seeed Studio Bazaar
	http://www.seeedstudio.com/depot/grove-temphumi-sensor-p-745.html
・Digital-output relative humidity & temperature sensor/module DHT22
	Aosong Electronics Co.,Ltd	http://www.humiditycn.com
・Arduinoをはじめよう (オライリージャパン)
	Massimo Banzi著 船田功訳
・Arduino 日本語リファレンス
	http://www.musashinodenpa.com/arduino/ref/index.php
*/
#define DHTport			17			// DHT_DATAポート番号(ANALOG 3)
#define SD_CS			10			// SDカードCS端子(デフォルト=10)
#include <SD.h>
const static byte DHTtype=	22;		// AM2302時はDHT=22にする
									// （#ifdefが使えないかった）

// DHTポートの初期化
void DHTInit(void) {
	pinMode(DHTport,INPUT);
	delay(250);
}

// DHT TSシーケンス
byte DHTTSSeq(void) {
	byte dht11_in;
	// start condition
	// 1. pull-down i/o pin from 18ms
	digitalWrite(DHTport, LOW);
	pinMode(DHTport,OUTPUT);
	if(DHTtype==22)	delay(1);
	else 			delay(30);
	pinMode(DHTport,INPUT);
	delayMicroseconds(20+40);	// High 20us + Slave ACK 80us/2

	dht11_in = digitalRead(DHTport);	// 正常時 = LOW
	if(dht11_in){
		Serial.println("dht start condition 1 not met");
		return(1);
	}
	delayMicroseconds(80);
	dht11_in = digitalRead(DHTport);	// 正常時 = HIGH
	if(!dht11_in){
		Serial.println("dht start condition 2 not met");
		return(1);
	}
	while( digitalRead(DHTport) );		// LOW待ち
	return(0);
}

// DHTデータ受信
byte read_dht11_dat(){
	byte i = 0;
	byte result=0;
	for(i=0; i< 8; i++){
		while( !digitalRead(DHTport) ); // High待ち
		delayMicroseconds(49);			// 28us or 70us 
		if( digitalRead(DHTport) ){
			result |=(1<<(7-i));
			while( digitalRead(DHTport) ); // wait '1' finish
		}
	}
	return result;
}

// DHT ACK
void DHT_ACK(void) {
	while( digitalRead(DHTport) );
	delayMicroseconds(50);
//	pinMode(DHTport,OUTPUT);
//	digitalWrite(DHTport, HIGH);
}

void setup() {
	Serial.begin(9600);	
	Serial.print("DHT");
	Serial.println(DHTtype,DEC);
	while( SD.begin(SD_CS) == false ){
		Serial.println("SD ERROR");
		delay(3000);
	}
}

void loop() {
	byte dht11_dat[5];
	byte dht11_check_sum;
	byte i;
	File file;
	char filename[] = "dht_hum.csv";
	char Str[16];
	float hum,temp;
	
	DHTInit();
	DHTTSSeq();
	for (i=0; i<5; i++) dht11_dat[i] = read_dht11_dat();
	DHT_ACK();
	dht11_check_sum = dht11_dat[0]+dht11_dat[1]+dht11_dat[2]+dht11_dat[3];
	if(dht11_dat[4]!= dht11_check_sum){
		Serial.println("DHT11 checksum error");
	}

	/* 表示 */
	
	if(DHTtype==22){
		temp = ((float)(dht11_dat[2]&0x7F)*256.+(float)dht11_dat[3])/10;
		if( dht11_dat[2] & 0x80 ) temp *= -1;
	}else temp =  (float)dht11_dat[2];
	Serial.print("DHT TEMP = ");
	Serial.print( temp , 1 );
	Serial.print(" degC\n");
	
	if(DHTtype==22)	hum = ((float)dht11_dat[0]*256.+(float)dht11_dat[1])/10;
	else			hum =  (float)dht11_dat[0];
	Serial.print("DHT HUM  = ");
	Serial.print( hum , 1 );
	Serial.print(" %\n");
	
	/* SDへ出力 */
	Serial.print("writing SD ... ");
	if( (file = SD.open( filename, FILE_WRITE )) != false ){
		file.print( temp , 1 );
		file.print( ", " );
		file.println( hum , 1 );
		file.close();
		Serial.println( "done" );
	} else Serial.println("failed file open");
	delay(3000);
}

