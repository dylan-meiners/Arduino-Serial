#include <Windows.h>

#include "SerialPort.h"
#include "KeyboardLegend.h"

using namespace std;

int main() {

    KeyboardLegend keyboard;
    SerialPort sp("COM4", true, true);
    
    //72 = 'H', 73 = 'I'
    unsigned char bytesToWrite[2] = {72, 73};

    cout << sp.WriteBytes(bytesToWrite, sizeof(bytesToWrite)) << endl;

    if(sp.Close()) {

        cout << "Successfully closed SerialPort" << endl;
    }
    else {

        cout << "Could not close SerialPort" << endl;
    }

    return 0;
}