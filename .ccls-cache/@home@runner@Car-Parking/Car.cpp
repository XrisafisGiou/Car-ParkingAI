#include "Car.h"

Car::Car(int X, int Y, int orientation)
{
  posX = X;
  posY = Y;
  this->orientation = orientation;
}

int Car::getOrientation()
{
  return orientation;
}

int Car::getX()
{
  return posX;
}

int Car::getY()
{
  return posY;
}

void Car::setX(int X)
{
  posX = X;
}

void Car::setY(int Y)
{
  posY = Y;
}