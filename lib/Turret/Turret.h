#include <Servo.h>
#include <Arduino.h>
#include <Ultrasonic.h>

class Turret : Servo
{
private:
    const unsigned int servoPin;
    Ultrasonic ultrasonicSensor; // TODO: make const?

    const float readyToShootTolerance;
    const float isOnTargetDistanceTolerance;

    static const float minTargetLength; // Will be used for determining whether we were on a target.

    float distance = 0, prevDistance = 0;
    int angle = 0, prevAngle = 0;

    float getPredictedDistance(const float nextDAngle);

public:
    Turret(
        const unsigned int servoPin,
        const unsigned int trigPin,
        const unsigned int echoPin);

    const int minAngle;
    const int maxAngle;

    void reset();

    const int getAngle();

    void setAngle(const int angle);

    void turn(const int dAngle);

    bool isOnTarget();

    float getCenterOfTarget(
        const float startAngle,
        const float startDistance,
        const float endAngle,
        const float endDistance);

    bool isReadyToShoot(const float centerOfTarget);

    float readDistance();
};