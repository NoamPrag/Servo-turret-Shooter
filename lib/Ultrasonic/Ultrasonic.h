#include <Arduino.h>

class Ultrasonic
{
private:
    static const float speedOfSound_CMPerMicros;
    static const float speedOfSoundDividedByTwo;

    static const int microsecondsToPulse;
    static const int microsecondsToWaitBeforePulse;

    const int trigPin, echoPin;

    const void pulse(const int microseconds) const;
    const long getDuration() const;
    static const float microsecondsToCM(const long microseconds);

public:
    Ultrasonic(const int trigPin, const int echoPin);

    const float measureDistance() const;
};