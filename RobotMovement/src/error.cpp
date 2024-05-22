#include <error.h>

void GetLastErrors()
{
  String errorMessages;

  // If serial is not begun begin it.
  if(Serial.available())
  {
    Serial.begin(BAUD_RATE);
  }

  for(int i = 0; i < EEPROM.length(); i++)
  {
    char c = EEPROM.read(i);
    if(c != 0)
    {
      errorMessages += c;
    }
  }

  Serial.print(errorMessages);
}

void ClearErrors()
{
  for(int i = 0; i < EEPROM.length(); i++)
  {
    EEPROM.write(i, 0);
  }
}

void HandleError(Error& e)
{
    // Print the error code to serial.
    GetLastErrors();
    // Flash the error code on the onboard LED.
    e.ThrowNewError();
    exit(0);
}

Error::Error(ErrorCodes error, String message)
{
    _code = error;
    _message = message;
    EEPROMWriteMessage(message, error);
}

// Writes the error code and message to the EEPROM so it can be read
// at program start and displayed over serial for more in depth debugging.
void Error::EEPROMWriteMessage(String message, int code)
{
    String errorMessage = "ERROR CODE:" + (String)code + "\nMESSAGE:" + message + "\n";

    // Unsigned int to keep compiler warning free.
    for(unsigned int i = 0; i < errorMessage.length(); i++)
    {
        // Ensures that the EEPROM is only written at valid bytes 
        // incase of a large error message.
        if(i < EEPROM.length())
        {
            // Only writes over cleared EEPROM to ensure no
            // errors are overwritten.
            if(EEPROM.read(i) == 0)
            {
                EEPROM.write(i, errorMessage.charAt(i));
            }
        }
    }
}

// Pauses the program and begins flashing an LED in accordance,
// With the Error code.
void Error::ThrowNewError()
{

  pinMode(ERROR_LED, OUTPUT);
    
  // Flash the LED in accordance with the error code.
  while(true)
  {
    digitalWrite(ERROR_LED, LOW);
    delay(2000);

    for(int i = 0; i < _code; i++)
    {
      digitalWrite(ERROR_LED, HIGH);
      delay(150);
      digitalWrite(ERROR_LED, LOW);
      delay(150);
    }
  }
}

unsigned int Error::GetErrorCode()
{
    return _code;
}

String Error::GetErrorMessage()
{
    return _message;
}