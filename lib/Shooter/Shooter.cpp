#include <Shooter/Shooter.h>

// TODO: Add real values for angles.
Shooter::Shooter(const int pin) : releaseAngle(0), shootAngle(0)
{
    this->attach(pin);
};

void Shooter::shoot()
{
    this->write(shootAngle); // Pull the trigger

    delay(500); // Wait half a second

    this->write(releaseAngle); // Turn back to the default angle
};

void Shooter::reset()
{
    this->write(releaseAngle);
}