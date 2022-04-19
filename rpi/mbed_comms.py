#https://www.engineersgarage.com/articles-raspberry-pi-serial-communication-uart-protocol-ttl-port-usb-serial-boards/
from time import sleep
import serial
import os
from spotify_client import SpotifyClient

ser = serial.Serial("/dev/ttyACM0", baudrate = 9600, parity=serial.PARITY_NONE,
stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=1)
spotify_client = SpotifyClient()
while 1:
    # rx_data = ser.read() #read serial data
    song_info = {'uri': None}
    if ser.inWaiting():
        data = ser.readline()
        print(data)
    else:
        # ser.write(str.encode('hello'))
        new_song_info = spotify_client.get_current_song()
        if new_song_info['uri'] != song_info['uri']:
            song_info = new_song_info
            ser.write(str.encode(f"Song Name:{song_info['name']}\nArtist: {song_info['artist']}\nTempo: {song_info['tempo']}"))
        sleep(1)
    sleep(0.03)    
    # data_left = ser.inWaiting() #wait until data is recieved
    # if data_left != 0:
        # rx_data += ser.data(data_left)
        # get_current_song(sp)
        #send song info list to mbed        
        # ser.write(rx_data) #tell mbed to update
#mbed controlling all physical components
