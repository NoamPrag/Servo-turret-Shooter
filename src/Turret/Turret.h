#include <Servo.h>
#include <Arduino.h>
#include <Ultrasonic/Ultrasonic.h>

class Turret : Servo
{
private:
    const Ultrasonic ultrasonicSensor;

    float length, prevLength = 0;
    float angle, prevAngle = 0;

    float getAngle();
    void setAngle(const float angle);

    float getPredictedLength(const float nextDAngle);
    bool isOnTarget();

    float getCenterOfTarget(const int startAngle, const int endAngle);
    bool isReadyToShoot();

public:
    Turret(const int servoPin, const int trigPin, const int echoPin);
};