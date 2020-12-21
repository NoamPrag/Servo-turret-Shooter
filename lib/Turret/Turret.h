#include <Servo.h>
#include <Arduino.h>
#include <Ultrasonic.h>

class Turret : Servo
{
private:
    const unsigned int servoPin;
    const Ultrasonic ultrasonicSensor;

    const float readyToShootTolerance;
    const float isOnTargetDistanceTolerance;

    // Will be used for determining whether we were on a target.
    static const float minTargetLength;

    float distance = 0, prevDistance = 0;
    int angle = 0, prevAngle = 0;

    const float getPredictedDistance(const float nextDAngle);

public:
    Turret(
        const unsigned int servoPin,
        const unsigned int trigPin,
        const unsigned int echoPin);

    const int minAngle;
    const int maxAngle;

    void reset();

    void setAngle(const int angle);

    void turn(const int dAngle);

    const int getAngle();

    const float readDistance();

    const bool isOnTarget();

    const float getCenterOfTarget(
        const float startAngle,
        const float startDistance,
        const float endAngle,
        const float endDistance);

    const bool isReadyToShoot(const float centerOfTarget);
};