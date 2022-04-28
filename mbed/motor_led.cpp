#include "motordriver.h"
#include "mbed.h"
#include "rtos.h"
#include <time.h>
#include <iostream>

Motor A(p22, p6, p5, 1); // pwm, fwd, rev, can brake 
Motor B(p21, p7, p8, 1); // pwm, fwd, rev, can brake


volatile int songBPM = 120;

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

//Setup RGB led using PWM pins and class
RGBLed myRGBled(p23,p24,p25); //RGB PWM pins

void RGB_thread(void const *argument){
    srand((unsigned)time(NULL));
    float newRand;
    while(1) {
      //get the BPM from the pi to use as mood setting
      if (songBPM < 80){ //r+b and slower, magenta
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(newRand,0.0,1.0);
      }
      else if (80<songBPM && songBPM<=90){ //reggae, blue
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(0.0,newRand,1.0);
      }
      else if (90<songBPM && songBPM<=120){ //hiphop, cyan
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(0.0,1.0,newRand);
      }
      else if (120<songBPM && songBPM<=125){ //jazz, green
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(newRand,1.0,0.0);
      }
      else if (125<songBPM && songBPM<=140){ //rock, yellow
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


void allDances(void const *argument){
    float bpm = 120;
    float s = (bpm / 1000) * 5;
    
    srand((unsigned)time(NULL));
    
    while(1){
        int randNum = (rand() % 3) + 1;
        
        if (randNum == 1){
            A.speed(0.0); 
            B.speed(0.0);
            A.speed(s); //forward
            B.speed(-s);
            wait(1);
            A.speed(0.0); 
            B.speed(0.0); 
            A.speed(-s); //reverse
            B.speed(s);
            wait(1);
        }
        else if (randNum == 2){
            A.speed(0.0); 
            B.speed(0.0);
            A.stop(0.0); 
            B.speed(s); //left turn
            wait(1);
            A.speed(0.0); 
            B.speed(0.0);
            B.stop(0.0); 
            A.speed(-s); //right turn
            wait(1); 
            A.speed(0.0); 
            B.speed(0.0);
            A.speed(s); //twirl 
            B.speed(s); 
            wait(1);
        }
        else if (randNum == 3){
            A.speed(0.0); 
            B.speed(0.0);
            A.speed(s); //reverse
            B.speed(-s);
            wait(1);
            A.speed(0.0); 
            B.speed(0.0);
            A.stop(0.0); 
            B.speed(s); //left turn
            wait(1);
            A.speed(0.0); 
            B.speed(0.0);
            B.stop(0.0); 
            A.speed(-s); //right turn
            wait(1); 
        }
        Thread::wait(1000);
    }
}

int main(){
    Thread t2(RGB_thread);
    Thread t3(allDances);

    
    while (1) {
        Thread::wait(1000);
    } 
}
