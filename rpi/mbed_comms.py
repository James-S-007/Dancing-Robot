#https://www.engineersgarage.com/articles-raspberry-pi-serial-communication-uart-protocol-ttl-port-usb-serial-boards/
from time import sleep
import serial
import os
from SpotifyClient import SpotifyClient

ser = serial.Serial("/dev/ttyACM0", baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=1)
spotify_client = SpotifyClient()

curr_song_uri = None
while True:
    if ser.inWaiting():
        data = ser.readline()
        print(f'Data Received: {data}')
        if data == b'n':
            spotify_client.next_track()
            print('Going to next track...')
        elif data == b'p':
            spotify_client.previous_track()
            print('Going to previous track...')
        elif data == b'<':
            spotify_client.rewind()
            print('Rewinding track...')
        elif data == b'>':
            spotify_client.toggle_playback()
            print('Toggling playback...')
        else:
            print('Err: Invalid character received')
    else:
        song_info = spotify_client.get_current_song()
        if not song_info:
            song_info['name'] = 'No track playing'
            song_info['artist'] = ''
            song_info['tempo'] = 0
            song_info['uri'] = ''
        if song_info['uri'] != curr_song_uri:
            curr_song_uri = song_info['uri']
            str_to_send = str.encode(f"?{song_info['name']}#${song_info['artist']}#")
            print(f'Sending: {str_to_send}')
            ser.write(str_to_send) # Tempo: {song_info['tempo']}"))
        sleep(0.2)
    sleep(0.03)
