#include <Shooter/Shooter.h>

Shooter::Shooter(const int pin)
{
    this->attach(pin);
};

void Shooter::shoot()
{
    this->write(shootAngle); // Pull the trigger

    delay(500); // Wait half a second

    this->write(releaseAngle); // Turn back to the default angle
};