#ifndef ERROR_DEFINED
#define ERROR_DEFINED
#define ERROR_LED 13
#define ERROR_BUTTON_HIGH 10
#define ERROR_BUTTON_LOW 9

#include <globals.h>
#include <EEPROM.h>

enum ErrorCodes
{
    DIRECTION_INVALID = 1,
    DURATION_OUT_OF_BOUNDS = 2,
    MOTOR_SETUP = 3,
    INVALID_TDOA = 4
};

void GetLastErrors();  
void ClearErrors();

class Error
{
    public:
        Error(ErrorCodes error, String message);
        void ThrowNewError();
        
        unsigned int GetErrorCode();
        String GetErrorMessage();
    private:
        unsigned int _code;
        String _message;

        void EEPROMWriteMessage(String, int);
};

void HandleError(Error& e);

#endif