#include "mbed.h"
#include "uLCD_4DGL.h"
#include "PinDetect.h"
#include "rtos.h"

#define NULL_CHAR 'z'

Serial  pi(USBTX, USBRX);
//BusOut myled(LED1,LED2,LED3,LED4);
Serial blue(p28,p27);
uLCD_4DGL uLCD(p9, p10, p11); // create a global uLCD object
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

volatile int tempo = 0;  // bpm
volatile char song_ctrl = NULL_CHAR;  // symbols for controlling spotify
volatile bool new_song_info = false;
// string curr_track; // current track name

void display_thread(void const *argument){
    while(1) {
        if (new_song_info) {
            led1!=led1;
            // track name
            uLCD.locate(1, 2);
            uLCD.text_height(2);
            uLCD.text_width(2);

            // artist name

            // tempo
            uLCD.locate(1, 3);
            uLCD.text_height(1);
            uLCD.text_width(1);

            new_song_info = false;
        }

        Thread::wait(2000); // update every 2 seconds
    }
}
   

void bt_thread(void const *argument) {
    while(1) {
        char bnum = 0;
        char bhit = 0;
        if (blue.readable()) {
            led2!=led2;
            if (blue.getc()=='!') {
                if (blue.getc()=='B') { //button data packet
                    bnum = blue.getc(); //button number
                    bhit = blue.getc(); //1=hit, 0=release
                    if (blue.getc() == char(~('!' + 'B' + bnum + bhit))) { //checksum OK?
                        // myled = bnum - '0'; //current button number will appear on LEDs
                        switch (bnum) {
                            case '5':  // button 5 up arrow - next song
                                if (bhit=='1') {
                                    song_ctrl = 'n'; // n means next song
                                } else {
                                    song_ctrl = NULL_CHAR; // return variable to having no value when button is released
                                };
                                break;
                            case '6':  // button 6 down arrow - previous song
                                if (bhit=='1') {
                                    song_ctrl = 'p'; // p means previous song
                                } else {
                                    song_ctrl = NULL_CHAR;
                                };
                                break;
                            case '7':  // button 7 left arrow - rewind
                                if (bhit=='1') {
                                    song_ctrl = '<'; // < means rewind
                                } else {
                                    song_ctrl = NULL_CHAR;
                                };
                                break;
                            case '8':  // button 8 right arrow - forward
                                if (bhit=='1') {
                                    song_ctrl = '>'; // > means forward
                                } else {
                                    song_ctrl = NULL_CHAR;
                                };
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }
    }

    Thread::wait(1000);
}

void pi_thread(void const *argument){
        while (1) {    
        if(pi.readable()) {
            led3!=led3;
            while (pi.readable()) {
                pi.getc();
            }
            // new_song_info = true;
        }
        if (song_ctrl != NULL_CHAR) {
            led41=led4;
            pi.putc(song_ctrl);
            song_ctrl = NULL_CHAR;
        }
    }

    Thread::wait(1000);
}



int main() {
    pi.baud(9600);
    Thread thread1(display_thread);
    Thread thread2(bt_thread);
    Thread thread3(pi_thread);
    while (1) {
        Thread::wait(1000);
    }  
}
