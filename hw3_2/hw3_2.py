import numpy as np
import serial
import time

# send the waveform table to mbed
serdev = 'COM4'
s = serial.Serial(serdev)
print("Sending commmand ...")

i=0
for i in range(10):
    s.write(b'5')
    s.write(b'Hellow ')
    s.write(b'2')
    s.write(b'3')
    s.write(b'1')
    s.write(b'4')
    s.write(b'2')
time.sleep(0.001)