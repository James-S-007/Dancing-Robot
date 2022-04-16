from abc import get_cache_token
import json
import os.path
from pprint import pprint
import spotipy
from spotipy.oauth2 import SpotifyOAuth
from time import sleep

from config import CLIENT_ID, CLIENT_SECRET

REDIRECT_URI = 'https://localhost:8080/callback'
SCOPE = 'user-read-playback-state user-read-currently-playing user-modify-playback-state'
REFRESH_DUR = 3  # seconds to check for change in song

def main():
    auth_manager = SpotifyOAuth(scope=SCOPE, client_id=CLIENT_ID, client_secret=CLIENT_SECRET, redirect_uri=REDIRECT_URI)
    sp = spotipy.Spotify(auth_manager=auth_manager)
    curr_track = get_current_song(sp)
    temp_track = None
    # TODO(James): send initial info to mbed
    while True:
        temp_track = get_current_song(sp)
        if temp_track['uri'] != curr_track['uri']:
            print('Detected song change')
            curr_track = temp_track
            # send info to mbed
        # elif recv serial input from mbed
            # do respective functions (toggle, playback, skip, etc.)
        else:
            sleep(REFRESH_DUR)


def get_current_song(sp):
    """
    Get relevant info of currently playing track
        Params: sp --> spotipy client
        Return --> dict : {
            'uri': Spotify track uri,
            'name': track name,
            'artist': artist name,
            'tempo': tempo of song
        }
    """
    song_info = {}
    curr_track = sp.current_playback()
    song_info['uri'] = curr_track['item']['uri']
    song_info['name'] = curr_track['item']['name']
    song_info['artist'] = curr_track['item']['artists'][0]['name']  # only get first artist (if multiple)
    
    track_features = sp.audio_features([song_info['uri']])
    song_info['tempo'] = track_features[0]['tempo']  # additional potential useful parameters to get include 'danceability', 'energy', 'liveness', 'loudness'
    return song_info


"""
Functions and lambdas to adjust current playback state
    Params: sp --> spotipy client
    Returns: None
"""
def toggle_playback(sp):
    curr_track = sp.current_playback()
    if curr_track['is_playing']:
        sp.pause_playback()
    else:
        sp.start_playback()

# lambda wrappers to match syntax of other functions: function(sp)
next_track = lambda sp : sp.next_track()
previous_track = lambda sp: sp.previous_track()
rewind = lambda sp : sp.seek_track(0)


if __name__ == '__main__':
    main()
