#include "mbed.h"
//Pi mbed USB Slave function
// connect mbed to Pi USB
RawSerial  pi(USBTX, USBRX);

int main()
{
    pi.baud(9600);
    pi.attach(&dev_recv, Serial::RxIrq);
    pi.putc('0');
    while(1) {
        #bluetooth connection code
        #if (bluetooth connected) {
            #if (song changed) {
                #pi.putc(0); #tell raspi to start functions
            #}
        #}
        #else (try again for bluetooth) {
        #}
        
        #if (pi.getc()){
            #unpack list of song info
            #start updating LCD, LED, motor, etc.
        #}
            
    }
}

//https://os.mbed.com/users/hudakz/code/mbedPi//file/91392e1f8551/mbedPi.cpp/
