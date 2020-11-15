#include <Servo.h>
#include <Arduino.h>

class Turret : Servo
{
private:
    const int pingPin, echoPin;

    float length, prevLength = 0;
    float angle, prevAngle = 0;

    float getAngle();
    void setAngle(const float angle);

    float getPredictedLength(const float nextDAngle);
    bool isOnTarget();

public:
    Turret(const int servoPin, const int pingPin, const int echoPin);
};