#include <./Turret/Turret.h>

// TODO: Add real values for tolerances.
Turret::Turret(const int pin, const int trigPin, const int echoPin)
    : ultrasonicSensor(trigPin, echoPin),
      readyToShootTolerance(0),
      isOnTargetDistanceTolerance(0),
      minAngle(0),
      maxAngle(180)
{
    this->attach(pin);
};

void Turret::setAngle(const float angle)
{
    write(angle);

    prevAngle = this->angle;
    this->angle = angle;
};

void Turret::turn(const float dAngle)
{
    setAngle(angle + dAngle);
};

void Turret::reset()
{
    write(minAngle);

    prevAngle = angle = getAngle();
    prevDistance = distance = readDistance();
};

const float Turret::getAngle()
{
    return this->read();
};

static const float cosineLaw(const float s1, const float s2, const float a)
{
    return (s1 * s1) + (s2 * s2) - 2 * s1 * s2 * cos(a);
};

static const float sasOtherSide(const float s1, const float s2, const float a)
{
    return sqrt(cosineLaw(s1, s2, a));
};

float Turret::getPredictedDistance(const float nextDAngle)
{
    const float absDAngle = abs(angle - prevAngle);

    // cosine law
    const float dDistanceOnTarget = sasOtherSide(prevDistance, distance, absDAngle);

    // sine law
    const float shooterAngleToTarget = asin(sin(absDAngle) * prevDistance / dDistanceOnTarget);

    const float nextAngleToTarget = shooterAngleToTarget - nextDAngle;

    // another sine law
    return distance * sin(shooterAngleToTarget) / sin(nextAngleToTarget);
};

float Turret::getCenterOfTarget(
    const float startAngle,
    const float startDistance,
    const float endAngle,
    const float endDistance)
{
    const float angleDifference = endAngle - startAngle;

    const float targetLength = sasOtherSide(startDistance, endDistance, angleDifference);

    const float halfTargetLength = targetLength / 2;

    // Law of sines
    const float startAngleToTarget = asin(sin(angleDifference) * endDistance / targetLength);

    const float medianLength = sasOtherSide(startDistance, halfTargetLength, startAngleToTarget);

    // another law of sines
    const float angleToMedian = asin(sin(startAngleToTarget) * halfTargetLength / medianLength);

    return startAngle + angleToMedian;
};

bool Turret::isOnTarget()
{
    return abs(distance - getPredictedDistance(angle - prevAngle)) <= isOnTargetDistanceTolerance;
};

bool Turret::isReadyToShoot(const float centerOfTarget)
{
    return abs(angle - centerOfTarget) <= readyToShootTolerance;
};

float Turret::readDistance()
{
    return ultrasonicSensor.measureDistance();
};