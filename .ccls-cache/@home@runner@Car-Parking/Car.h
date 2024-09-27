#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <vector>
using namespace std;

class Car
{
  private:
    int posX,posY;
    int orientation;  //1 for North/South 2 for West/East
  public:
    Car(int X, int Y, int orientation);
    int getOrientation();
    int getX();
    int getY();
    void setX(int X);
    void setY(int Y);
};

#endif