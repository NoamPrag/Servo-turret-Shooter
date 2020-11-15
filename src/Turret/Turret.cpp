#include <./Turret/Turret.h>

Turret::Turret(const int pin, const int trigPin, const int echoPin) : ultrasonicSensor(trigPin, echoPin)
{
    this->attach(pin);
};

void Turret::setAngle(const float angle)
{
    this->write(angle);
};

float Turret::getAngle()
{
    return read();
}

float cosineLaw(const float s1, const float s2, const float a)
{
    return (s1 * s1) + (s2 * s2) - 2 * s1 * s2 * cos(a);
};

float sasOtherSide(const float s1, const float s2, const float a)
{
    return sqrt(cosineLaw(s1, s2, a));
};

float Turret::getPredictedLength(const float nextDAngle)
{
    const float absDAngle = abs(angle - prevAngle);

    // cosine law
    const float dDistanceOnTarget = sasOtherSide(prevLength, length, absDAngle);

    // sine law
    const float shooterAngleToTarget = asin(sin(absDAngle) * prevLength / dDistanceOnTarget);

    const float nextAngleToTarget = shooterAngleToTarget - nextDAngle;

    // another sine law
    return length * sin(shooterAngleToTarget) / sin(nextAngleToTarget);
};