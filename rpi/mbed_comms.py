#https://www.engineersgarage.com/articles-raspberry-pi-serial-communication-uart-protocol-ttl-port-usb-serial-boards/
import time
from time import sleep
import serial

ser = serial.Serial("/dev/ttyS0", baudrate = 9600, parity=serial.PARITY_NONE,
stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=1)

while 1:
    rx_data = ser.read() #read serial data
    sleep(0.03)
    data_left = ser.inWaiting()
    rx_data += ser.data(data_left)
    print(rx_data)
    ser.write(rx_data) #write data to serial port

#LCD control
#LED control
#Spotify API connection
#Bluetooth connection
