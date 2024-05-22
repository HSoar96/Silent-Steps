#ifndef TRIANGULATION_DEFINED
#define TRIANGULATION_DEFINED
#include <globals.h>

// Distance between mics is 0.3M, speed of sound at 21 deg is 344M/s
// T = D/S = 8.7209x10-4 Seconds
// 872 microSeconds.
#define TIME_BETWEEN_MICS 872
#define MAXTIME 2*TIME_BETWEEN_MICS
#define DISTANCE_BETWEEN_MICS 0.3
#define THRESHOLD 500
#define DELAY 1000
#define DELAYTIME 20000

int Listen();

double CalculateDistance();

double CalculateBearing();

void GetTriggeredOrder();

// Have the mics been triggered.
extern bool aTriggered;
extern bool bTriggered;
extern bool cTriggered;

// Time it took for sound to travel to each mic.
extern uint32_t aTime;
extern uint32_t bTime;
extern uint32_t cTime;

extern uint32_t firstTime;
extern uint32_t secondTime;

// Variables for the order of micrphones.
extern int firstMic;
extern int secondMic;
extern int thirdMic;

extern double bearing;
#endif