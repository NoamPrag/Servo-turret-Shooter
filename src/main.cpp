#include <Arduino.h>

#include <Turret.h>
#include <Shooter.h>

#include <ColorfulLED.h>

static const Color orbit = {0, 0, 200};
static const Color searchingTarget = {255, 200, 0};
static const Color searchingTarget2 = {0, 255, 0};

static const int turretPin = 9;
static const int shooterPin = 11;
static const int ultrasonicTrigPin = 10;
static const int ultrasonicEchoPin = 2;

static const int redLEDPin = 3;
static const int greenLEDPin = 6;
static const int blueLEDPin = 5;

static const int buttonPin = 0;

static Turret turret(turretPin, ultrasonicTrigPin, ultrasonicEchoPin);
static Shooter shooter(shooterPin);
static ColorfulLED led(redLEDPin, greenLEDPin, blueLEDPin);

void setup()
{
  led.setColor(RED);
  turret.reset();
  shooter.reset();
};

static bool prevIsOnTarget = false;

static float startTargetAngle = 0;
static float startTargetDistance = 0;
static float endTargetDistance = 0;
static float endTargetAngle = 0;

static bool fullyFoundTarget = false;

static float centerOfTarget = 0;

static int turretDAngle = 1;
static unsigned long dTimeToTurnTurret = 25;
static unsigned long lastTimeTurretTurned = 0;

void loop()
{
  if (fullyFoundTarget)
  {
    turret.setAngle(centerOfTarget);
    delay(800);
    shooter.shoot(); // Wait a bit before shooting in order to let the turret reach its desired angle.

    // Starting the search for the next target.
    fullyFoundTarget = false;
    prevIsOnTarget = false;
  }

  const unsigned long currentTime = millis();

  if (currentTime - lastTimeTurretTurned < dTimeToTurnTurret)
    return; // return if it's not time to turn yet.

  // Turn turret dAngle degrees
  turret.turn(turretDAngle);
  lastTimeTurretTurned = currentTime;

  const int currentAngle = turret.getAngle();

  // Measure distance.
  const float measuredDistance = turret.readDistance();

  // If dropping edge of being on target -> go to center and shoot; else -> keep searching.
  const bool isOnTarget = turret.isOnTarget();

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
    fullyFoundTarget = true;
    centerOfTarget = turret.getCenterOfTarget(startTargetAngle, startTargetDistance, endTargetAngle, endTargetDistance);
  }

  prevIsOnTarget = isOnTarget;

  // Flip direction if has reached the end of range.
  if (currentAngle >= turret.maxAngle || currentAngle <= turret.minAngle)
    turretDAngle *= -1;
};