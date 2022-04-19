# Dancing-Robot

## TODO
Pseudo Code
```cpp

volatile char send_cmd  // cmd to send to pi, set by BT
volatile bool new_song_info  // set by serial line from RPI to mbed, set False by LCD
volatile int bpm  // set by serial line from RPI to mbed, consumed by motors and LEDS

Thread checking serial line with RPi
	if readable ___
		get info
		bpm = __;
		song_name = ___;
		new_song_info = true;
		
	if send_cmd != some_null_character
		send_cmd over BT
		set send_cmd to null_character
Thread checking bluetooth
	send_cmd = ___
Thread commanding motor speed
Thread commanding leds

Thread updating lcd
	if new_song_info
		update information
		new_song_info = false



lcd	
	need song name and such
	volatile bool new_song_info
	
motors and leds
	need bpm
	volatile int bpm
	
```