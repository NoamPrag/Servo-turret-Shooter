#include <Shooter.h>

Shooter::Shooter(const unsigned int pin)
    : releaseAngle(60),
      shootAngle(110),
      servoPin(pin){};

void Shooter::shoot()
{
    this->write(shootAngle); // Pull the trigger

    delay(500); // Wait half a second

    this->write(releaseAngle); // Turn back to the default angle

    delay(500); // Wait half a second again

    Serial.print("SHOOT!! :)");
};

void Shooter::reset()
{
    this->attach(this->servoPin);

    write(releaseAngle);

    delay(1000);

    Serial.println("Shooter Reset. :)");
};