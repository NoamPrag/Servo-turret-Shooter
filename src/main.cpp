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

static const int buttonPin = 12; // TODO: Add button to confirm shooting.

static Turret turret(turretPin, ultrasonicTrigPin, ultrasonicEchoPin);
static Shooter shooter(shooterPin);

static ColorfulLED led(redLEDPin, greenLEDPin, blueLEDPin);

void setup()
{
  Serial.begin(9600);
  Serial.println("Working! :)");
  // Serial.end();

  // turret.reset(); // Turn the turret to the min angle.
  // shooter.reset();
  // turret.setAngle(0);

  led.setColor({200, 0, 0});
  delay(2000);

  pinMode(buttonPin, INPUT_PULLUP);
  // shooter.shoot();
};

static bool prevIsOnTarget = false;

static float startTargetAngle = 0;
static float startTargetDistance = 0;
static float endTargetDistance = 0;
static float endTargetAngle = 0;

static bool fullyFoundTarget = false;

static float centerOfTarget = 110;

static int turretDAngle = 1;
static unsigned long dTimeToTurnTurret = 15;
static unsigned long lastTimeTurretTurned = 0;

static bool hasShoot = false;

static bool buttonState = false;

static int endAngle = 110;
static int endToCenter = 20;

void loop()
{
  if (!buttonState)
  {
    led.blinkFade({0, 0, 30}, {30, 30, 0}, 400);
    buttonState = buttonState || !digitalRead(buttonPin);
    return;
  }

  if (fullyFoundTarget)
  {
    if (!hasShoot)
    {
      led.setColor({0, 60, 0});
      delay(400);
      shooter.shoot();
      hasShoot = true;
    }
    return;
  }

  led.blinkFade({90, 0, 0}, {0, 0, 90}, 400);

  // led.blink({80, 55, 0}, 150, 200);
  // if (!buttonState)
  // {
  //   buttonState |= !digitalRead(buttonPin);
  //   return;
  // }

  // if (fullyFoundTarget)
  // {
  //   if (!hasShoot)
  //   {
  //     led.setColor({0, 50, 0});
  //     // turret.setAngle(centerOfTarget);
  //     turret.setAngle(endAngle - endToCenter);
  //     delay(700);

  //     shooter.shoot();
  //     hasShoot = true;
  //     led.setColor({0, 0, 0});
  //   }
  //   delay(500);
  //   led.blink({80, 55, 0}, 150, 200);
  //   fullyFoundTarget = false;
  //   buttonState = false;
  //   hasShoot = false;
  //   endAngle += 60;
  //   endToCenter += 10;

  //   // bool buttonState = digitalRead(buttonPin);
  //   // while (!buttonState)
  //   // {
  //   //   buttonState = digitalRead(buttonPin);
  //   //   Serial.print("button: ");
  //   //   Serial.println(buttonState);
  //   // }
  // }
  // else
  // {
  //   led.blinkFade({80, 0, 0}, {0, 0, 65}, 550);
  // }

  const unsigned long currentTime = millis();

  if (currentTime - lastTimeTurretTurned < dTimeToTurnTurret)
    return; // return if it's not time to turn yet.

  // Turn turret dAngle degrees
  turret.turn(turretDAngle);
  lastTimeTurretTurned = currentTime;

  const int currentAngle = turret.getAngle();

  if (currentAngle >= endAngle)
  {
    fullyFoundTarget = true;
  }

  // Measure distance.
  // const float measuredDistance = turret.readDistance();

  if (currentAngle >= turret.maxAngle || currentAngle <= turret.minAngle)
    turretDAngle *= -1;

  // If dropping edge of being on target -> go to center and shoot; else -> keep searching.
  // const bool isOnTarget = turret.isOnTarget();

  /*

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

  */
};