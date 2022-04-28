# ECE 4180 -- Spotify Spinner
This webpage will explain the design and functionality of a "dancing" robot.

## Team
Grayson Eady            -- Section B -- Electrical Engineering

Joyce Karanouh-Schuler  -- Section B -- Electrical Engineering

Brook Lancaster         -- Section B -- Electrical Engineering

James Springer          -- Section B -- Electrical Engineering

## Project Goal
This project programs a simple robot to "dance" in beat with any given song played on Spotify. The robot has dual DC motors powering its wheels, allowing it to complete a sequence of unique movements. The speed of those movements are scaled to the beats per minute (BPM) of the song being played on a user's Spotify account, which can be controlled by a different device via bluetooth.

## Parts List
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

## Libraries Used
| Library | Installation |
| ------- | ------------ |
| uLCD (mbed) | zip |
| rtos (mbed) | zip |
| Motordriver (mbed) | zip |
| spotipy | pip install spotipy |

## Hardware
insert block/circuit diagram diagram

## Software
![final gaant chart](https://user-images.githubusercontent.com/78691589/165658820-d672c42c-3ec0-4d4e-9a79-ef439e9d8f82.JPG)

RTOS
- The threads allow each action to occur simultaneously

Spotify API
- The Spotify Client is how the Raspberry Pi obtains the songs' data in real time

Raspberry Pi/mbed Communication
- The robot's mbed and Raspberry Pi are able to send and recieve information from each other, such as the songs' data

DANCE!
- [explaination of dance code]


## Demo
embed video of it working with explanation
