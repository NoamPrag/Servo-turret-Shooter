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

    static const float maxDistanceToDeclareTarget;

    float distance = 0, prevDistance = 0;
    int angle = 0, prevAngle = 0;

    const float getPredictedDistance(const float nextDAngle) const;

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

    const int getAngle() const;

    const float readDistance() const;

    const bool isOnTarget() const;

    const float getCenterOfTarget(
        const float startAngle,
        const float startDistance,
        const float endAngle,
        const float endDistance) const;

    const bool isReadyToShoot(const float centerOfTarget) const;
};