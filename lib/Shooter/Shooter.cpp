#include <Shooter.h>

static const int shooterReleaseAngle = 0;
static const int shooterShootAngle = 90;

Shooter::Shooter(const unsigned int pin)
    : releaseAngle(shooterReleaseAngle),
      shootAngle(shooterShootAngle),
      servoPin(pin){};

void Shooter::shoot()
{
    this->write(shootAngle); // Pull the trigger.

    delay(700); // Wait a bit.

    this->write(releaseAngle); // Turn back to the default angle.

    delay(700); // Wait some more.
};

void Shooter::reset()
{
    this->attach(this->servoPin); // Attach the servo to its pin.

    write(releaseAngle); // Set the servo to its released angle.

    delay(1000); // Wait a second.
};