#include <Servo.h>
#include <Arduino.h>

class Shooter : public Servo
{
private:
    const unsigned int servoPin;
    const int releaseAngle;
    const int shootAngle;

public:
    explicit Shooter(const unsigned int pin);

    void reset();

    void shoot();
};