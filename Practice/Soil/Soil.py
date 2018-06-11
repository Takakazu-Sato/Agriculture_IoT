# -*- coding: utf-8 -*-
import numpy as np
import serial
import datetime

def main():
    # COMポートを指定してシリアル通信開始
    ser = serial.Serial("COM3")

    for i in range(11):
        # ArduinoのSerial.printlnで出力された値を取得
        line = ser.readline()
        # Arduinoから取得した値はutf-8にデコードする必要あり
        humidity = line.rstrip().decode('utf-8')

        print("humidity:\t",humidity)
        print("-----------------------------")

    # シリアル通信終了
    ser.close()

if __name__ == '__main__':
    main()
