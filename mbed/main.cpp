#include "mbed.h"
#include "uLCD_4DGL.h"
#include "rtos.h"

#define NULL_CHAR 'z'

Serial  pi(USBTX, USBRX);
Serial blue(p28,p27);
uLCD_4DGL uLCD(p9, p10, p11); // create a global uLCD object
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

Mutex buf_mtx;

volatile int tempo = 0;  // bpm
volatile char song_ctrl = NULL_CHAR;  // symbols for controlling spotify
volatile bool new_song_info = false;
volatile int idx = 0;

char buf[200];
char song_name[100];
char artist[100];

void display_thread(void const *argument){
    while(1) {
        led4 = 1;
        while(pi.readable()) {
            uLCD.putc(pi.getc());
        }
        led4 = 0;
        /*if (new_song_info) {
            // track name
            uLCD.cls();
            uLCD.locate(1, 1);
            buf_mtx.lock();
            uLCD.printf("Song Name: %s", song_name);
            buf_mtx.unlock();

            // artist name
            uLCD.locate(1, 6);
            buf_mtx.lock();
            uLCD.printf("Artist: %s", artist);
            buf_mtx.unlock();

            // tempo
            // uLCD.locate(1, 10);
            // uLCD.printf("Tempo: %d", );
            
            buf_mtx.lock();
            memset(buf, 0, sizeof(buf));
            // memset(song_name, 0, sizeof(song_name));
            // memset(artist, 0, sizeof(artist));
            buf_mtx.unlock();
            
            new_song_info = false;
            led1 = 0;
        }*/

        Thread::wait(500); // update every 2 seconds
    }
}
   

void bt_thread(void const *argument) {
    while(1) {
        char bnum = 0;
        char bhit = 0;
        if (blue.readable()) {
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
        
    Thread::wait(1000);    
    
    }
}

void pi_thread(void const *argument){
    while (1) {    
        if (pi.readable()) {
            led2 = 1;
            
            char c = pi.getc();
            led3 = 1;
            buf_mtx.lock();
            while (pi.readable() && c != '?' && idx < 200 - 2) {
                buf[idx++] = c;
                c = pi.getc();
            }
            buf_mtx.unlock();

            if (c == '?') {
                new_song_info = true;
                buf_mtx.lock();
                buf[idx] = 0;
                buf_mtx.unlock();
                idx = 0;
            } else {
                new_song_info = false;
            }
            
            led3 = 0;
            // sscanf(buf, "SONG:%[^\n]ARTIST:%[^\n]", song_name, artist);
            buf_mtx.lock();
            sscanf(buf, "%s %s", song_name, artist);
            buf_mtx.unlock();
            // new_song_info = true;
            led2 = 0;
        }

        if (song_ctrl != NULL_CHAR) {
            pi.putc(song_ctrl);
            song_ctrl = NULL_CHAR;
        }
    
    Thread::wait(50);
    }
}



int main() {
    pi.baud(115200);
    Thread thread1(display_thread);
    Thread thread2(bt_thread);
    // Thread thread3(pi_thread);
    while (1) {
        Thread::wait(1000);
    }  
}
