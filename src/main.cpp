#include <Arduino.h>
#include <Servo.h>

#include <Turret.h>
#include <Shooter.h>

#include <ColorfulLED.h>

static const Color orbit = {0, 0, 200};

static const int turretPin = 0;
static const int shooterPin = 0;
static const int ultrasonicTrigPin = 0;
static const int ultrasonicEchoPin = 0;

static const int redLEDPin = 0;
static const int greenLEDPin = 0;
static const int blueLEDPin = 0;

static const int buttonPin = 0; // TODO: Add button to confirm shooting.

static Turret turret(turretPin, ultrasonicTrigPin, ultrasonicEchoPin);
static Shooter shooter(shooterPin);

void setup()
{
  Serial.begin(9600);
  Serial.print("Working! :)");
  Serial.end();

  turret.reset(); // Turn the turret to the min angle.
  shooter.reset();
};

static bool prevIsOnTarget = false;

static float startTargetAngle = 0;
static float startTargetDistance = 0;
static float endTargetDistance = 0;
static float endTargetAngle = 0;

static bool isShooting = false;

static float centerOfTarget = 0;

static float turretDAngle = 1;                // TODO: Add real value.
static unsigned long dTimeToTurnTurret = 100; // TODO: add real value (in millis)
static unsigned long lastTimeTurretTurned = 0;

// TODO: Add LED logic.

void loop()
{
  if (isShooting)
  {
    turret.setAngle(centerOfTarget);

    if (turret.isReadyToShoot(centerOfTarget))
    {
      shooter.shoot();
      isShooting = false;
    }
  }

  const unsigned long currentTime = millis();
  if (currentTime - lastTimeTurretTurned < dTimeToTurnTurret)
  {
    return;
  }

  // Turn turret dAngle degrees.
  turret.turn(turretDAngle);
  lastTimeTurretTurned = currentTime;

  // Measure distance.
  const float measuredDistance = turret.readDistance();

  // If dropping edge of being on target -> go to center and shoot; else -> keep searching.
  const bool isOnTarget = turret.isOnTarget();

  const float currentAngle = turret.getAngle();

  if (isOnTarget)
  {
    if (!prevIsOnTarget) // Rising edge
    {
      startTargetAngle = currentAngle;
      startTargetDistance = measuredDistance;
    }

    // gets updated all the time until loses target.
    endTargetDistance = measuredDistance;
    endTargetAngle = currentAngle;
  }
  else if (prevIsOnTarget) // Dropping edge
  {
    isShooting = true;
    centerOfTarget = turret.getCenterOfTarget(startTargetAngle, startTargetDistance, endTargetAngle, endTargetDistance);
  }

  prevIsOnTarget = isOnTarget;

  if (currentAngle >= turret.maxAngle || currentAngle <= turret.minAngle)
  {
    turretDAngle *= -1;
  }
};