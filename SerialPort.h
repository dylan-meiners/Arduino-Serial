#include <Windows.h>
#include <string>
#include <iostream>
#include <tchar.h>
#include <stdio.h>

class SerialPort {

    public:

        SerialPort(const LPCSTR COMPortToSet, const bool readingToSet, const bool writingToSet) {

            m_COMPortPath = COMPortToSet;
            m_canRead = readingToSet;
            m_canWrite = writingToSet;

            DWORD desiredAccess;

            if (!readingToSet || !writingToSet) {

                if (readingToSet) {

                    desiredAccess = GENERIC_READ;
                }
                else {

                    desiredAccess = GENERIC_WRITE;
                }
            }
            else {

                desiredAccess = GENERIC_READ | GENERIC_WRITE;
            }

            m_hComm = CreateFile(COMPortToSet, desiredAccess, 0, NULL, OPEN_EXISTING, 0, NULL);
            if (m_hComm == INVALID_HANDLE_VALUE) {

                std::cout << "Error in opening serial port on " << COMPortToSet << std::endl;
            }
            else {

                std::cout << "Successfully  opened serial port on " << COMPortToSet << std::endl;
            }

            SecureZeroMemory(&m_dcb, sizeof(DCB));
            m_dcb.DCBlength = sizeof(DCB);

            bool success = GetCommState(m_hComm, &m_dcb);

            if (!success) {

                std::cout << "GetCommState failed with error " << GetLastError() << std::endl;
            }

            PrintCommState();
            
            m_dcb.BaudRate = CBR_57600;
            m_dcb.ByteSize = 8;
            m_dcb.StopBits = ONESTOPBIT;
            m_dcb.Parity = NOPARITY;
            success = SetCommState(m_hComm, &m_dcb);

            if (!success) {

                std::cout << "SetCommState failed with error " << GetLastError() << std::endl;
            }

            PrintCommState();

            m_timeouts.ReadIntervalTimeout = 50;
            m_timeouts.ReadTotalTimeoutConstant = 50;
            m_timeouts.ReadTotalTimeoutMultiplier = 10;
            m_timeouts.WriteTotalTimeoutConstant = 50;
            m_timeouts.WriteTotalTimeoutMultiplier = 10;
        }

        bool Close() {

            return CloseHandle(m_hComm);
        }

        bool WriteBytes(const unsigned char *bytesToWrite, const unsigned int size) {

            DWORD numOfBytesToWrite = size;
            std::cout << numOfBytesToWrite << std::endl;
            DWORD numOfBytesWritten = 0;

            return WriteFile(m_hComm, bytesToWrite, numOfBytesToWrite, &numOfBytesWritten, NULL);
        }

        void PrintCommState() {

            _tprintf(TEXT("\nBaudRate = %d\nByteSize = %d\nParity = %d\nStopBits = %d\n\n"),
                     m_dcb.BaudRate,
                     m_dcb.ByteSize,
                     m_dcb.Parity,
                     m_dcb.StopBits);
        }

    private:

        HANDLE m_hComm;
        LPCSTR m_COMPortPath;
        DCB m_dcb;
        COMMTIMEOUTS m_timeouts;
        bool m_canRead;
        bool m_canWrite;
};