# ECE 4180 -- Spotify Spinner
This webpage will explain the design and functionality of a "dancing" robot.

## Team
Grayson Eady            -- Section B -- Electrical Engineering

Joyce Karanouh-Schuler  -- Section B -- Electrical Engineering

Brook Lancaster         -- Section B -- Electrical Engineering

James Springer          -- Section B -- Electrical Engineering

## Project Goal
This project programs a simple robot to "dance" in beat with any given song played on Spotify. The robot has dual DC motors powering its wheels, allowing it to complete a sequence of unique movements. The speed of those movements are scaled to the beats per minute (BPM) of the song being played on a user's Spotify account, which can be controlled by a different device via bluetooth.

## Hardware

___

insert block/circuit diagram diagram

### Parts List

|Part| Description |
|--|--|
| Arm Mbed LPC1768 | controls the robot's movements, displays song info on LCD screen, controls the RGB LED, and communicates with the Bluetooth board |
| Raspberry pi 4 | utilizes the Spotify API to get song info from the user's phone |
| Robot Shadow Chassis | houses the robot's hardware |
| 2 DC Motors | allow the robot to move or "dance" by powering the wheels |
| Dual H-Bridge | control/drive the motors |
| 2 Wheels | allow the robot to move |
| Breadboard | houses the connections between the Mbed and the other boards and components |
| Jumper Wires | connect the various components on the breadboard |
| Resistors | limit current to the RGB LED |
| Bluetooth Capable Smartphone | for sending song data and commands to the raspberry pi by way of the bluetooth board and Mbed |
| Battery Holder and 4 AA Batteries | provide power to the motors and H-bridge |
| 5v Barrel Jack Adaptor | connects the breadboard power rails to the battery holder |
| LCD Screen | display song info |
| anker External Battery Bank | powers the Mbed and raspberry pi |
| RGB LED | changes colors and flashes to the music |

## Software

___

![final gaant chart](https://user-images.githubusercontent.com/78691589/165658820-d672c42c-3ec0-4d4e-9a79-ef439e9d8f82.JPG)

### Libraries Used
| Library | Installation |
| ------- | ------------ |
| uLCD (mbed) | zip |
| rtos (mbed) | zip |
| Motordriver (mbed) | zip |
| spotipy | pip install spotipy |

### SpotifyClient Methods

#### `get_current_song()`
| Item | Description |
| ---- | ----------- |
| Summary | Gets relavant info of currently playing track from Spotify's Web API |
| Params | None |
| Returns | Dictionary of parameters for current song |

##### Return Dictionary
| Dictionary Key | Description |
| -------------- | ----------- |
| 'uri' | Unique resource identifier of song used by Spotify's API |
| 'name' | Name of the song |
| 'artist' | Name of the artist |
| 'tempo' | Tempo of the currently playing Song |

#### `toggle_playback()`
| Item | Description |
| ---- | ----------- |
| Summary | Pauses currently playing song if playing and resumes if currently paused |
| Params | None |
| Returns | None |

#### `next_track()`
| Item | Description |
| ---- | ----------- |
| Summary | Skips to next track in playlist |
| Params | None |
| Returns | None |

#### `previous_track()`
| Item | Description |
| ---- | ----------- |
| Summary | Goes to previous track in playlist |
| Params | None |
| Returns | None |

#### `rewind()`
| Item | Description |
| ---- | ----------- |
| Summary | Seeks to beginning of currently playing track |
| Params | None |
| Returns | None |

### mbed

Insert description of mbed methods

### RTOS
- The threads allow each action to occur simultaneously

### Spotify API
- The Spotify Client is how the Raspberry Pi obtains the songs' data in real time

### Raspberry Pi/mbed Communication
- The robot's mbed and Raspberry Pi are able to send and recieve information from each other, such as the songs' data

### DANCE!
- [explaination of dance code]


## Demo

___

embed video of it working with explanation
