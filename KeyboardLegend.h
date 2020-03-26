#include <Windows.h>

class KeyboardLegend {

    public:
        
        KeyboardLegend() {

            in.type = INPUT_KEYBOARD;
            in.ki.wScan = 0;
            in.ki.time = 0;
            in.ki.dwExtraInfo = 0;
        }

        void PressKey(int key) {

            in.ki.wVk = key;
            in.ki.dwFlags = 0;
            SendInput(1, &in, sizeof(INPUT));

            in.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &in, sizeof(INPUT));
        }

    private:

        INPUT in;
};