#include "mbed.h"
#include "uLCD_4DGL.h"
#include "PinDetect.h"
#include "rtos.h"
#include "motordriver.h"

BusOut myled(LED1,LED2,LED3,LED4);
Serial blue(p28,p27);
uLCD_4DGL uLCD(p28, p27, p29); // create a global uLCD object

int tempo; // bpm
string curr_track; // current track name
char song_ctrl; // symbols for controlling spotify

void display_track_thread(void const *argument){
    while(1){
        // probably needs call here to retrieve current track from pi
        uLCD.locate(1, 2);
        uLCD.text_height(2);
        uLCD.text_width(2);
        uLCD.printf(curr_track); // print current track name
        Thread::wait(2000); // update every 2 seconds
    }
}
    
void display_tempo_thread(void const *argument){
    while(1){
        // probably needs call here to retrieve tempo from pi
        uLCD.locate(1, 3);
        uLCD.text_height(1);
        uLCD.text_width(1);
        uLCD.printf(tempo); // print tempo in BPM
        Thread::wait(2000); // update every 2 seconds
    }
}

int main()
{
    char bnum=0;
    char bhit=0;
    
    thread.start(display_track_thread);
    thread.start(display_tempo_thread);
    
        if (blue.getc()=='!') {
            if (blue.getc()=='B') { //button data packet
                bnum = blue.getc(); //button number
                bhit = blue.getc(); //1=hit, 0=release
                if (blue.getc()==char(~('!' + 'B' + bnum + bhit))) { //checksum OK?
                    myled = bnum - '0'; //current button number will appear on LEDs
                    switch (bnum) {
                        case '5': //button 5 up arrow - next song
                            if (bhit=='1') {
                                song_ctrl = 'n'; // n means next song
                            } else {
                                song_ctrl = null; // return variable to having no value when button is released
                            }
                            break;
                        case '6': //button 6 down arrow - previous song
                            if (bhit=='1') {
                                song_ctrl = 'p'; // p means previous song
                            } else {
                                song_ctrl = null;
                            }
                            break;
                        case '7': //button 7 left arrow - rewind
                            if (bhit=='1') {
                                song_ctrl = '<'; // < means rewind
                            } else {
                                song_ctrl = null;
                            }
                            break;
                        case '8': //button 8 right arrow - forward
                            if (bhit=='1') {
                                song_ctrl = '>'; // > means forward
                            } else {
                                song_ctrl = null;
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}
