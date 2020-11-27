#include <Arduino.h>
#include <Servo.h>

#include <./Turret/Turret.h>
#include <./Shooter/Shooter.h>
#include <LED/LED.h>

const int turretPin = 0;
const int shooterPin = 0;
const int ultrasonicTrigPin = 0;
const int ultrasonicEchoPin = 0;

const int redLEDPin = 0;
const int greenLEDPin = 0;
const int blueLEDPin = 0;

const int buttonPin = 0; // TODO: Add button to confirm shooting.

const float turretDAngle = 0; // TODO: Add real value.

LED led(9);

Turret turret(turretPin, ultrasonicTrigPin, ultrasonicEchoPin);
Shooter shooter(shooterPin);

void setup()
{
  Serial.begin(9600);
  Serial.println("Working! :)");

  turret.reset(); // Turn the turret to the min angle.
};

bool prevIsOnTarget = false;

float startTargetAngle = 0;
float startTargetDistance = 0;
float endTargetDistance = 0;
float endTargetAngle = 0;

bool isShooting = false;

float centerOfTarget = 0;

// TODO: Add LED logic.

void loop()
{
  // Measure distance.
  const float measuredDistance = turret.readDistance();

  // 2) If dropping edge of being on target -> go to center and shoot. else -> keep searching.
  const float isOnTarget = turret.isOnTarget();

  const float currentAngle = turret.getAngle();

  if (isOnTarget)
  {
    if (!prevIsOnTarget) // Rising edge
      startTargetAngle = turret.getAngle();

    endTargetDistance = measuredDistance; // gets updated all the time until looses target.
    endTargetAngle = currentAngle;
  }

  else if (prevIsOnTarget) // Dropping edge
  {
    isShooting = true;
    centerOfTarget = turret.getCenterOfTarget(startTargetAngle, startTargetDistance, endTargetAngle, endTargetDistance);
  }

  if (isShooting)
  {

    turret.setAngle(centerOfTarget);

    if (turret.isReadyToShoot(centerOfTarget))
    {
      shooter.shoot();
      isShooting = false;
    }
  }
  else
    // Turn turret dAngle degrees.
    turret.turn(turretDAngle);
};