#include <Ultrasonic/Ultrasonic.h>

const float Ultrasonic::speedOfSound_CMPerMicros = 0.034;
const float Ultrasonic::speedOfSoundDividedByTwo = speedOfSound_CMPerMicros / 2;

const int Ultrasonic::microsecondsToPulse = 10;
const int Ultrasonic::microsecondsToWaitBeforePulse = 2;

Ultrasonic::Ultrasonic(const int trigPin, const int echoPin) : trigPin(trigPin), echoPin(echoPin)
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
};

const void Ultrasonic::pulse(const int microseconds)
{
    digitalWrite(trigPin, LOW);                       // first making sure that the trigPin is off.
    delayMicroseconds(microsecondsToWaitBeforePulse); // waiting before sending the output.

    digitalWrite(trigPin, HIGH);     // emitting some ultra-sound.
    delayMicroseconds(microseconds); // waiting until turning the sound off.

    digitalWrite(trigPin, LOW); // turning it back off again.
};

const long Ultrasonic::getDuration()
{
    return pulseIn(echoPin, HIGH); // listening for high frequencies and returning the duration.
};

const float Ultrasonic::microsecondsToCM(const long microseconds)
{
    // multiplying by the speed and sound and dividing by two because the sound waves have to go back.
    return microseconds * speedOfSoundDividedByTwo;
};

const float Ultrasonic::measureDistance()
{
    pulse(microsecondsToPulse);          // emitting some ultra-sound.
    const long duration = getDuration(); // listening and calculating the duration which the sound takes to reflect from the object.
    return microsecondsToCM(duration);   // converting the time to distance and returning it.
};