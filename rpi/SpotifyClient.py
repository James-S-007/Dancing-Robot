import spotipy
from spotipy.oauth2 import SpotifyOAuth

from config import CLIENT_ID, CLIENT_SECRET

REDIRECT_URI = 'https://localhost:8080/callback'
SCOPE = 'user-read-playback-state user-read-currently-playing user-modify-playback-state'
REFRESH_DUR = 3  # seconds to check for change in song

class SpotifyClient:
    def __init__(self):
        self.auth_manager = SpotifyOAuth(scope=SCOPE, client_id=CLIENT_ID, client_secret=CLIENT_SECRET, redirect_uri=REDIRECT_URI)
        self.sp = spotipy.Spotify(auth_manager=self.auth_manager)


    def get_current_song(self):
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
        curr_track = self.sp.current_playback()
        if curr_track:
            song_info['uri'] = curr_track['item']['uri']
            song_info['name'] = curr_track['item']['name']
            song_info['artist'] = curr_track['item']['artists'][0]['name']  # only get first artist (if multiple)
        
            track_features = self.sp.audio_features([song_info['uri']])
            song_info['tempo'] = track_features[0]['tempo']  # additional potential useful parameters to get include 'danceability', 'energy', 'liveness', 'loudness'
        return song_info


    """
    Functions and lambdas to adjust current playback state
        Params: sp --> spotipy client
        Returns: None
    """
    def toggle_playback(self):
        curr_track = self.sp.current_playback()
        if not curr_track:
            return  # no active device
        elif curr_track['is_playing']:
            self.sp.pause_playback()
        else:
            self.sp.start_playback()

    # function wrappers to match syntax of other member functions: function(sp)
    def next_track(self):
        self.sp.next_track()

    def previous_track(self):
        self.sp.previous_track()
        
    def rewind(self):
        self.sp.seek_track(0)

if __name__ == '__main__':
    sp_client = SpotifyClient()
    sp_client.get_current_song()
