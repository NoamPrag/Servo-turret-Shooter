#include <Servo.h>
#include <Arduino.h>
#include <Ultrasonic/Ultrasonic.h>

class Turret : Servo
{
private:
    Ultrasonic ultrasonicSensor; // TODO: make const?

    const float readyToShootTolerance;
    const float isOnTargetDistanceTolerance;

    const float minAngle;
    const float maxAngle;

    static const float minTargetLength; // Will be used for determining whether we were on a target.

    float distance, prevDistance = 0;
    float angle, prevAngle = 0;

    float getPredictedDistance(const float nextDAngle);

public:
    Turret(const int servoPin, const int trigPin, const int echoPin);

    void reset();

    float getAngle();

    void setAngle(const float angle);

    void turn(const float dAngle);

    bool isOnTarget();

    float getCenterOfTarget(
        const float startAngle,
        const float startDistance,
        const float endAngle,
        const float endDistance);

    bool isReadyToShoot(const float centerOfTarget);

    float readDistance();
};