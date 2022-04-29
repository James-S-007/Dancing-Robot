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

<img width="831" alt="image" src="https://user-images.githubusercontent.com/71736743/165875672-98920392-0796-4739-9783-75d82ce16e7a.png">

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

### Gaant Chart
Below is the charted progression of our project.
![final gaant chart](https://user-images.githubusercontent.com/78691589/165658820-d672c42c-3ec0-4d4e-9a79-ef439e9d8f82.JPG)

### Libraries Used
| Library | Installation |
| ------- | ------------ |
| uLCD (mbed) | zip |
| rtos (mbed) | zip |
| Motordriver (mbed) | zip |
| spotipy | pip install spotipy |

### SpotifyClient
The SpotifyClient class allows the Raspberry Pi to obtain data from Spotify for the current user via Spotify's web API

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

### mbed to Pi Communication

#### `mbed_comms.py`
| Item | Description |
| ---- | ----------- |
| Summary | Prints the song inf
| Params | None |
| Returns | None |


### RTOS

#### `display_thread()`
| Item | Description |
| ---- | ----------- |
| Summary | Prints the song information onto the LCD in real time |
| Params | None |
| Returns | None |

#### `bt_thread()`
| Item | Description |
| ---- | ----------- |
| Summary | Allows Blufruit App to control Spotify |
| Params | None |
| Returns | None |

#### `pi_thread()`
| Item | Description |
| ---- | ----------- |
| Summary | Sends and recieves information between the Raspberry Pi and the mbed |
| Params | None |
| Returns | None |

#### `RGB_thread()`
| Item | Description |
| ---- | ----------- |
| Summary | Reads the BPM of the song and sets a mood related light |
| Params | None |
| Returns | None |

#### `all_dances()`
| Item | Description |
| ---- | ----------- |
| Summary | Houses the dance routines that the robot cycles through |
| Params | None |
| Returns | None |


## Demo

embed video of it working with explanation

## Finished Device

![7c839bd67e3d4aca91828d1f599186ab](https://user-images.githubusercontent.com/71736743/165880641-44749a30-6aed-4387-9dbc-1ab5e4ac281e.jpeg)
![bf836c9607b74d178ffb65ff0115e933](https://user-images.githubusercontent.com/71736743/165880654-f3606139-18f3-4465-9115-ef3decb4f857.jpeg)
![26826890665d4b68a456a633f6ba58cc](https://user-images.githubusercontent.com/71736743/165880635-7b73b97c-126b-4b1a-bdf0-25be11e461e3.jpeg)
