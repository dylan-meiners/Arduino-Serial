#include <Windows.h>

#include "SerialPort.h"
#include "KeyboardLegend.h"

using namespace std;

/*void RunLEDTest() {

    while (true) {
        
        for (int i = 0; i < 128; i++) {

            bytesToWrite[i] = 255;
            sp.WriteBytes(bytesToWrite, sizeof(bytesToWrite));
            Sleep(WRITE_SLEEP_TIME);
        }
        for (int i = 127; i >= 0; i--) {

            bytesToWrite[i] = 0;
            sp.WriteBytes(bytesToWrite, sizeof(bytesToWrite));
            Sleep(WRITE_SLEEP_TIME);
        }
    }
}*/

int main() {

    KeyboardLegend keyboard;
    SerialPort sp("COM4", true, true);

    unsigned char bytesToWrite[1] = {0};
    unsigned int buffer[256] = {0};
    unsigned int singleBuffer = 0;

    while (true) {

        sp.ReadTheLonelyByte(singleBuffer);
        cout << singleBuffer << endl;
        sp.WriteBytes(bytesToWrite, 1);
    }

    if(sp.Close()) {

        cout << "Successfully closed SerialPort" << endl;
    }
    else {

        cout << "Could not close SerialPort" << endl;
    }

    return 0;
}