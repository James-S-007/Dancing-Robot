#include "mbed.h"
#include "uLCD_4DGL.h"
#include "rtos.h"
#include "motordriver.h"

#define NULL_CHAR 'z'

//Class to control an RGB LED using three PWM pins
class RGBLed
{
public:
    RGBLed(PinName redpin, PinName greenpin, PinName bluepin);
    void write(float red,float green, float blue);
private:
    PwmOut _redpin;
    PwmOut _greenpin;
    PwmOut _bluepin;
};

RGBLed::RGBLed (PinName redpin, PinName greenpin, PinName bluepin)
    : _redpin(redpin), _greenpin(greenpin), _bluepin(bluepin)
{
    //50Hz PWM clock default a bit too low, go to 2000Hz (less flicker)
    _redpin.period(0.0005);
}

void RGBLed::write(float red,float green, float blue)
{
    _redpin = red;
    _greenpin = green;
    _bluepin = blue;
}


Serial  pi(USBTX, USBRX);
Serial blue(p28,p27);
uLCD_4DGL uLCD(p9, p10, p11); // create a global uLCD object
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
Motor A(p22, p6, p5, 1); // pwm, fwd, rev, can brake 
Motor B(p21, p7, p8, 1); // pwm, fwd, rev, can brake
RGBLed myRGBled(p23,p24,p25); //RGB PWM pins


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
        if (new_song_info) {
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
            uLCD.locate(1, 10);
            uLCD.printf("Tempo: %d", tempo);
            
            new_song_info = false;
            led1 = 0;
        }

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
            char c = pi.getc();
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
                sscanf(buf, "%u %[^\n] %[^\n]", &tempo, song_name, artist);
                buf_mtx.unlock();
                idx = 0;
            } else {
                buf[idx++] = c;
                new_song_info = false;
            }
            
            // sscanf(buf, "SONG:%[^\n]ARTIST:%[^\n]", song_name, artist);
            
            // new_song_info = true;
        }

        if (song_ctrl != NULL_CHAR) {
            pi.putc(song_ctrl);
            song_ctrl = NULL_CHAR;
        }
    
    Thread::wait(50);

    }
}

void RGB_thread(void const *argument){
    srand((unsigned)time(NULL));
    float newRand;
    while(1) {
      //get the tempo from the pi to use as mood setting
      if (tempo < 80){ //r+b and slower, magenta
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(newRand,0.0,1.0);
      }
      else if (80<tempo && tempo<=90){ //reggae, blue
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(0.0,newRand,1.0);
      }
      else if (90<tempo && tempo<=120){ //hiphop, cyan
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(0.0,1.0,newRand);
      }
      else if (120<tempo && tempo<=125){ //jazz, green
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(newRand,1.0,0.0);
      }
      else if (125<tempo && tempo<=140){ //rock, yellow
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(1.0,newRand,0.0);
      }
      else { //metal and faster, red
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(1.0,0.0,newRand);
      }
      Thread::wait(1000);
    }
}


void all_dances(void const *argument){
    srand((unsigned)time(NULL));
    
    while(1) {
        float s;
        int randNum = (rand() % 3) + 1;
        
        if (randNum == 1){
            A.speed(0.0); 
            B.speed(0.0);
            s = (float(tempo) / 1000) * 5;
            A.speed(s); //forward
            B.speed(-s);
            Thread::wait(1000);
            A.speed(0.0); 
            B.speed(0.0); 
            s = (float(tempo) / 1000) * 5;
            A.speed(-s); //reverse
            B.speed(s);
            Thread::wait(1000);
        }
        else if (randNum == 2){
            A.speed(0.0); 
            B.speed(0.0);
            A.stop(0.0); 
            s = (float(tempo) / 1000) * 5;
            B.speed(s); //left turn
            Thread::wait(1000);
            A.speed(0.0); 
            B.speed(0.0);
            B.stop(0.0); 
            s = (float(tempo) / 1000) * 5;
            A.speed(-s); //right turn
            Thread::wait(1000);
            A.speed(0.0); 
            B.speed(0.0);
            s = (float(tempo) / 1000) * 5;
            A.speed(s); //twirl 
            B.speed(s); 
            Thread::wait(1000);
        }
        else if (randNum == 3){
            A.speed(0.0); 
            B.speed(0.0);
            s = (float(tempo) / 1000) * 5;
            A.speed(s); //reverse
            B.speed(-s);
            Thread::wait(1000);
            A.speed(0.0); 
            B.speed(0.0);
            A.stop(0.0); 
            s = (float(tempo) / 1000) * 5;
            B.speed(s); //left turn
            Thread::wait(1000);
            A.speed(0.0); 
            B.speed(0.0);
            B.stop(0.0); 
            s = (float(tempo) / 1000) * 5;
            A.speed(-s); //right turn
            Thread::wait(1000);
        }
        // Thread::wait(1000);
    }
}



int main() {
    pi.baud(115200);
    Thread t1(display_thread);
    Thread t2(bt_thread);
    Thread t3(pi_thread);
    Thread t4(RGB_thread);
    Thread t5(all_dances);
    while(1) {
        Thread::wait(1000);
    }  
}
