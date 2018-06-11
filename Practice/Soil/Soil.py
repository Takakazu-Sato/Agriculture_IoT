# -*- coding: utf-8 -*-
import numpy as np
import serial
import datetime

def main():
    # COM�|�[�g���w�肵�ăV���A���ʐM�J�n
    ser = serial.Serial("COM3")

    for i in range(11):
        # Arduino��Serial.println�ŏo�͂��ꂽ�l���擾
        line = ser.readline()
        # Arduino����擾�����l��utf-8�Ƀf�R�[�h����K�v����
        humidity = line.rstrip().decode('utf-8')

        print("humidity:\t",humidity)
        print("-----------------------------")

    # �V���A���ʐM�I��
    ser.close()

if __name__ == '__main__':
    main()
