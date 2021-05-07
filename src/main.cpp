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

static const int buttonPin = 0; // TODO: Add button to confirm shooting.

static Turret turret(turretPin, ultrasonicTrigPin, ultrasonicEchoPin);
static Shooter shooter(shooterPin);

void setup()
{
  Serial.begin(9600);
  Serial.println("Working! :)");

  turret.reset(); // Turn the turret to the min angle.
  shooter.reset();

  delay(500);

  turret.setAngle(0);
  // delay(200);
  // turret.setAngle(100);
  // delay(500);
  // shooter.shoot();
  // delay(200);
};

static bool prevIsOnTarget = false;

static float startTargetAngle = 0;
static float startTargetDistance = 0;
static float endTargetDistance = 0;
static float endTargetAngle = 0;

static bool fullyFoundTarget = false;

static float centerOfTarget = 0;

static int turretDAngle = 1;                 // TODO: Add real value.
static unsigned long dTimeToTurnTurret = 25; // TODO: add real value (in millis)
static unsigned long lastTimeTurretTurned = 0;

// TODO: Add LED logic.

void loop()
{
  if (fullyFoundTarget)
  {
    turret.setAngle(centerOfTarget);
    delay(800);
    shooter.shoot();
    fullyFoundTarget = false;
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

  if (currentAngle >= turret.maxAngle || currentAngle <= turret.minAngle)
    turretDAngle *= -1;
};