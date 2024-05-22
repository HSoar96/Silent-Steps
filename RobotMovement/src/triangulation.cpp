#include <triangulation.h>
#include <ADC.h>


bool aTriggered = false;
bool bTriggered = false;
bool cTriggered = false;

uint32_t  aTime = 0;
uint32_t  bTime = 0;
uint32_t  cTime = 0;
uint32_t firstTime;
uint32_t secondTime;
double bearing = -1;

int firstMic = 0;
int secondMic = 0;
int thirdMic = 0;

double CalculateDistance()
{
    
}

double CalculateBearing()
{
    // Get the time difference betweent he first triggering and second,
    // then convert to seconds because speed of sound is in m/s.

    // Calculate TDOA.
    double timeDifSeconds = (secondTime - firstTime)/1000000.0;

    // Infrequently a value too large for TDOA is parsed. 
    if(timeDifSeconds > 100.0)
    {
        throw Error(DIRECTION_INVALID, "Invalid direction argument parsed.");
        return -1;
    }

    double distance = (timeDifSeconds * SPEED_OF_SOUND);

    double angle = (atan((sqrt((DISTANCE_BETWEEN_MICS * DISTANCE_BETWEEN_MICS)-(distance * distance)) / distance))) * RAD_TO_DEG - 30;
    if(angle < 0)
    {
        angle *= -1;
    }

    // TODO: This is messy as well fix this.
    // Work out sector and direction.
    if(firstMic == 1 && secondMic == 2)
    {
        bearing = 0 + angle;
    }
    else if(firstMic == 1 && secondMic == 3)
    {
        bearing = 360 - angle;
    }
    else if(firstMic == 2 && secondMic == 1)
    {
        bearing = 120 - angle;
    }
    else if(firstMic == 2 && secondMic == 3)
    {
        bearing = 120 + angle;
    }
    else if(firstMic == 3 && secondMic == 1)
    {
        bearing = 240 + angle;
    }
    else
    {
        bearing = 240 - angle;
    }

    return bearing;
}

void GetTriggeredOrder()
{
    // TODO: This is messy. Fix it.
    if (aTime < bTime && aTime < cTime) 
    {
        // micA triggered first
        firstMic = 1;
        firstTime = aTime;
    } 
    else if (bTime < cTime)
    {
        // micB triggered first
        firstMic = 2;
        firstTime = bTime;
    } 
    else 
    {
        // micC triggered first
        firstMic = 3;
        firstTime = cTime;
    }

    if (firstMic == 1)
    {
        if(bTime < cTime)
        {
            secondTime = bTime;
            secondMic = 2;
            thirdMic = 3;
        }
        else
        {
            secondTime = cTime;
            secondMic = 3;
            thirdMic = 2;
        }
    }
    else if (firstMic == 2)
    {
        if(aTime < cTime)
        {
            secondTime = aTime;
            secondMic = 1;
            thirdMic = 3;
        }
        else
        {
            secondTime = cTime;
            secondMic = 3;
            thirdMic = 1;
        }
    }
    else
    {
        if(aTime < bTime)
        {
            secondTime = aTime;
            secondMic = 1;
            thirdMic = 2;
        }
        else
        {
            secondTime = bTime;
            secondMic = 2;
            thirdMic = 1;
        }
    }
}

int Listen()
{
    // Read all the micrphones and check if they are above the threshold,
    // if they are log the current time in microseconds.
    // Second check is there to ensure it doesnt update at the clock speed.
    if (!aTriggered && analogRead(MIC_A) > THRESHOLD && micros() > aTime + DELAYTIME) 
    {
        aTime = micros();
        aTriggered = true;
    }
    if (!bTriggered && analogRead(MIC_B) > THRESHOLD && micros() > bTime + DELAYTIME) 
    {
        bTime = micros();
        bTriggered = true;
    }
    if (!cTriggered && analogRead(MIC_C) > THRESHOLD && micros() > cTime + DELAYTIME) 
    {
        cTime = micros();
        cTriggered = true;
    }

    // If the max time is reached reset all values.
    if ((micros() - aTime > MAXTIME && aTriggered) ||
        (micros() - bTime > MAXTIME && bTriggered) ||
        ( micros() - cTime > MAXTIME && cTriggered)) 
    {
        aTriggered = false;
        bTriggered = false;
        cTriggered = false;
    } 
    
    // If one of them isnt triggered return and loop again.
    if(aTriggered && bTriggered && cTriggered)
    {
        GetTriggeredOrder();
        int br = CalculateBearing();
        aTriggered = false;
        bTriggered = false;
        cTriggered = false;
        return br;
    }
    else
    {
        return -1;
    }
}