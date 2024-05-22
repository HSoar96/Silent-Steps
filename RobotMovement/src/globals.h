#include <Arduino.h>
#include <error.h>

#define BAUD_RATE 115200

// Left Motor.
#define EN_1 A19
#define IN_1 36
#define IN_2 37
// Right Motor.
#define EN_2 A6
#define IN_3 19
#define IN_4 14

#define TURN_STEP 20
#define MAX_TURN_TIME 80
// Microphones
#define MIC_A A7
#define MIC_B A8
#define MIC_C A9

#define SPEED_OF_SOUND 346
