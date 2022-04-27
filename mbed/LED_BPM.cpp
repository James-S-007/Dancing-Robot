#include "mbed.h"
#include <time.h>
#include <iostream>

volatile int songBPM;

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
RGBLed myRGBled(p23,p22,p21); //RGB PWM pins

void RGB_thread(void const *argument){
    srand((unsigned)time(NULL));
    while(1) {
      //get the BPM from the pi to use as mood setting
      if (songBPM < 80){ //r+b and slower, magenta
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(newRand,0.0,1.0);
      }
      else if (80<songBPM<90){ //reggae, blue
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(0.0,newRand,1.0);
      }
      else if (90<songBPM<120){ //hiphop, cyan
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(0.0,1.0,newRand);
      }
      else if (120<songBPM<125){ //jazz, green
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(newRand,1.0,0.0);
      }
      else if (125<songBPM<140){ //rock, yellow
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(1.0,newRand,0.0);
      }
      else { //metal and faster, red
        newRand = (float) rand()/RAND_MAX;
        myRGBled.write(1.0,0.0,newRand);
      }
    }
}

//add code and thread statement to main.cpp
