import numpy as np
import serial
import matplotlib.pyplot as plt
import time
import struct

serdev = 'COM4'
s = serial.Serial(serdev)

# read the wavefrom from mbed
# for i in range(15):
x = np.zeros(128)
y = np.zeros(128)
z = np.zeros(128)
i = 0
print("X:       Y:      Z:      ")
s.write(b'1')
while(s.readable()):
    line=s.readline()
    line=line.rstrip(b'\r\n')
    if(line==b'end'):
        break
    x[i] = float(line)
    line=s.readline()
    line=line.rstrip(b'\r\n')
    y[i] = float(line)
    line=s.readline()
    line=line.rstrip(b'\r\n')
    z[i] = float(line)
    print(x[i], '   ', y[i], '  ',z[i])
    i=i+1
    
s = np.arange(0, 128, 1)
fig, ax = plt.subplots(3, 1)
ax[0].plot(s, x)
ax[0].set_xlabel('Time')
ax[0].set_ylabel('Value')
ax[1].plot(s, y)
ax[1].set_xlabel('Time')
ax[1].set_ylabel('Value')
ax[2].plot(s, z)
ax[2].set_xlabel('Time')
ax[2].set_ylabel('Value')
plt.show()

s.close()