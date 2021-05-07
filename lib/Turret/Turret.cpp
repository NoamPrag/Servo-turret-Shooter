#include <Turret.h>

static const int turretMinAngle = 0;
static const int turretMaxAngle = 180;

static const float readyToShootAngleTolerance = 2;
static const float isOnTargetDistanceTolerance = 20;

const float Turret::maxDistanceToDeclareTarget = 50;
const float Turret::minTargetLength = 5;

// TODO: Add real values for tolerances.
Turret::Turret(
    const unsigned int servoPin,
    const unsigned int trigPin,
    const unsigned int echoPin)
    : servoPin(servoPin),
      ultrasonicSensor(trigPin, echoPin),

      minAngle(turretMinAngle),
      maxAngle(turretMaxAngle),

      readyToShootTolerance(readyToShootAngleTolerance),
      isOnTargetDistanceTolerance(isOnTargetDistanceTolerance){};

void Turret::setAngle(const int angle)
{
    const int boundedAngle = max(minAngle, min(maxAngle, angle)); // bound angle to turret capabilities
    this->write(boundedAngle);                                    // write the angle to the servo.

    // update shooter state.
    prevAngle = this->angle;
    this->angle = boundedAngle;
};

void Turret::turn(const int dAngle)
{
    setAngle(angle + dAngle);
};

void Turret::reset()
{
    this->attach(this->servoPin); // attach the pin to the servo (this function must be called inside setup function).

    write(minAngle); // set the turret to its min angle to be ready to search for target.

    // update angle and distance state - prev and current to the current state.
    prevAngle = angle = minAngle;
    prevDistance = distance = readDistance();
};

const int Turret::getAngle()
{
    return this->angle;
};

static const float cosineLaw(const float s1, const float s2, const float a)
{
    // c^2 = a^2 + b^2 - 2ab * cos(alpha)
    return (s1 * s1) + (s2 * s2) - 2 * s1 * s2 * cos(a);
};

static const float sasOtherSide(const float s1, const float s2, const float a)
{
    // sqrt(c^2) == c
    return sqrt(cosineLaw(s1, s2, a));
};

const float Turret::getPredictedDistance(const float nextDAngle)
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

const float Turret::getCenterOfTarget(
    const float startAngle,
    const float startDistance,
    const float endAngle,
    const float endDistance)
{
    const float angleDifference = endAngle - startAngle;

    const float targetLength = sasOtherSide(startDistance, endDistance, angleDifference);

    const float halfTargetLength = targetLength / 2;

    // law of sines
    const float startAngleToTarget = asin(sin(angleDifference) * endDistance / targetLength);

    const float medianLength = sasOtherSide(startDistance, halfTargetLength, startAngleToTarget);

    // another law of sines
    const float angleToMedian = asin(sin(startAngleToTarget) * halfTargetLength / medianLength);

    return startAngle + angleToMedian;
};

const bool Turret::isOnTarget()
{
    // checking if the distance correlates to the predicted distance (plus tolerance).
    return distance <= maxDistanceToDeclareTarget && abs(distance - getPredictedDistance(angle - prevAngle)) <= isOnTargetDistanceTolerance;
};

const bool Turret::isReadyToShoot(const float centerOfTarget)
{
    // checking if we're on the target (plus tolerance).
    return abs(angle - centerOfTarget) <= readyToShootTolerance;
};

float Turret::readDistance()
{
    return ultrasonicSensor.measureDistance();
};