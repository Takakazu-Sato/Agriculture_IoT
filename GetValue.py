# -*- coding: utf-8 -*-
import serial
import numpy as np
import datetime

def main():
    # COMポートを指定してシリアル通信開始
    ser = serial.Serial('COM3',9600,timeout=1)
    #文字列送信
    while True:
        flag = input()
        flag2 = flag.encode('utf-8')
        ser.write(flag2)

        line = ser.readline()
        line2 = line.rstrip().decode('utf-8')
        all_sensors = line2.split(',')
        print(all_sensors[0])
        print(all_sensors[1])
        print(all_sensors[2])
        print(all_sensors[3])
        print(all_sensors[4])
        print(all_sensors[5])
        print("-----------------------------")

    ser.close()

if __name__ == '__main__':
    main()
