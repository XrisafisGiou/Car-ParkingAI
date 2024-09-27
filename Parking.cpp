#include "Parking.h"

Parking::Parking(int width, int height)
{
    this->width = width;
    this->height = height;
    free.resize(width, vector<bool>(height, true));
    for (int i=0;i<width;i++)
        for (int j=0;j<height;j++)
            free[i][j]=true;
    setActionName("");
    setPrevious(nullptr);
}

int Parking::getDepth()
{
    int counter =0;
    Parking *p = this;
    while (p->prev!=nullptr)
    {
        p=p->prev;
        counter++;
    }
    return counter;
}

vector < string > Parking::getSolution()
{
    vector < string > solution;
    Parking *p = this;
    while (p->prev!=nullptr)
    {
        solution.push_back(p->getActionName() + "\n");
        p=p->prev;
    }
    return solution;
}
void Parking::setFree(int i, int j, bool f)
{
    free[i][j]=f;
}

bool Parking::isFree(int x,int y)
{
    return free[x][y];
}

void Parking::setCar(Car c)
{
  cars.push_back(c);
  int X = c.getX();
  int Y = c.getY();
  free[X][Y] = false;
}

bool Parking::operator==(const Parking& s) const
{
  if (this == &s) {
    return true; 
  }
  if (width == s.width && height == s.height)
  {
    for (int i = 0; i < width; i++) 
    {
      for (int j = 0; j < height; j++) 
      {
        if (free[i][j] != s.free[i][j]) 
        {
          return false; 
        }
      }
    }
    return true;
  }
  return false;
}
Parking Parking::operator= (Parking o)
{
    prev = o.prev;
    actionName = o.actionName;
    width = o.width;
    height = o.height;
    for (int i = 0; i < width; i++) 
    {
      for (int j = 0; j < height; j++) 
      {
        free[i][j] = o.free[i][j];
      }
    }
    return *this;
}
string Parking::toString() 
{
    stringstream ot;
    for (int j = height-1; j >= 0; j--) 
    {
      for (int i = 0; i < width; i++)  
      {
        if (free[i][j])
          ot << "O ";
        else
        {
           bool carFound = false;
           int orientation;
           for (int k = 0; k < cars.size(); k++)
           {
             if (cars[k].getX() == i && cars[k].getY() == j)
             {
               orientation = cars[k].getOrientation();
               carFound = true;
               break;
             }
          }
          if (carFound)
          {
            if (orientation == 1)
            {
              ot << "1 ";
            }
            else
            {
              ot << "2 ";
            }
          }
          else
            ot << "X ";
        }
      }
      ot << endl;
    }  
    return ot.str();
}

bool Parking::goUp(Parking &n,int carIndex)
{
    n=*this;
    int x_og = n.cars[carIndex].getX();      //keep original position of car
    int y_og = n.cars[carIndex].getY();
    while (n.cars[carIndex].getY() < height)
    {
        if (n.cars[carIndex].getY() == height-1)   //if car is at the edge of the parking
        {
          n.setFree(n.cars[carIndex].getX(), n.cars[carIndex].getY(),true);
          n.cars.erase(n.cars.begin() + carIndex);
          n.setActionName("Move car from ("+ to_string(x_og) + "," + to_string(y_og) + ") up");
          n.setPrevious(this);
          return true;
        }
        if (isFree(n.cars[carIndex].getX(),n.cars[carIndex].getY()+1)) //check next position
        {
          n.setFree(n.cars[carIndex].getX(), n.cars[carIndex].getY(),true);
          n.cars[carIndex].setY(n.cars[carIndex].getY()+1);
          n.setFree(n.cars[carIndex].getX(), n.cars[carIndex].getY(),false);
        }
        else
        {
          n.cars[carIndex].setY(y_og);  //return to original
          return false;
        }
    }
    return false;
}

bool Parking::goDown(Parking &n,int carIndex)
{
     n=*this;
     int x_og = n.cars[carIndex].getX();
     int y_og = n.cars[carIndex].getY();
     while (n.cars[carIndex].getY() >= 0)
     {
        if (n.cars[carIndex].getY() == 0)
        {
          n.setFree(n.cars[carIndex].getX(), n.cars[carIndex].getY(),true);
          n.cars.erase(n.cars.begin() + carIndex);
          n.setActionName("Move car from ("+ to_string(x_og) + "," + to_string(y_og) + ") down");
          n.setPrevious(this);
          return true;
        }
        if (isFree(n.cars[carIndex].getX(),n.cars[carIndex].getY()-1))
        {
          n.setFree(n.cars[carIndex].getX(), n.cars[carIndex].getY(),true);
          n.cars[carIndex].setY(n.cars[carIndex].getY()-1);
          n.setFree(n.cars[carIndex].getX(), n.cars[carIndex].getY(),false);
        }
        else
        {
          n.cars[carIndex].setY(y_og);
          return false;
        }
    }
    return false;
}
bool Parking::goLeft(Parking &n,int carIndex)
{
     n=*this;
     int x_og = n.cars[carIndex].getX();
     int y_og = n.cars[carIndex].getY();
     while (n.cars[carIndex].getX() >= 0)
     {
        if (n.cars[carIndex].getX() == 0)
        {
          n.setFree(n.cars[carIndex].getX(), n.cars[carIndex].getY(),true);
          n.cars.erase(n.cars.begin() + carIndex);
          n.setActionName("Move car from ("+ to_string(x_og) + "," + to_string(y_og) + ") left");
          n.setPrevious(this);
          return true;
        }
        if (isFree(n.cars[carIndex].getX()-1,n.cars[carIndex].getY()))
        {
          n.setFree(n.cars[carIndex].getX(), n.cars[carIndex].getY(),true);
          n.cars[carIndex].setX(n.cars[carIndex].getX()-1);
          n.setFree(n.cars[carIndex].getX(), n.cars[carIndex].getY(),false);
        }
        else
        {
          n.cars[carIndex].setX(x_og);
          return false;
        }
    }
    return false;
}
bool Parking::goRight(Parking &n,int carIndex)
{
    n=*this;
    int x_og = n.cars[carIndex].getX();
    int y_og = n.cars[carIndex].getY();
    while (n.cars[carIndex].getX() < width)
    {
        if (n.cars[carIndex].getX() == width-1)
        {
          n.setFree(n.cars[carIndex].getX(), n.cars[carIndex].getY(),true);
          n.cars.erase(n.cars.begin() + carIndex);
          n.setActionName("Move car from ("+ to_string(x_og) + "," + to_string(y_og) + ") right");
          n.setPrevious(this);
          return true;
        }
        if (isFree(n.cars[carIndex].getX()+1,n.cars[carIndex].getY()))
        {
          n.setFree(n.cars[carIndex].getX(), n.cars[carIndex].getY(),true);
          n.cars[carIndex].setX(n.cars[carIndex].getX()+1);
          n.setFree(n.cars[carIndex].getX(), n.cars[carIndex].getY(),false);
        }
        else
        {
          n.cars[carIndex].setX(x_og);
          return false;
        }
    }
    return false;
}

vector <Parking *> Parking::expand()
{
  vector <Parking *> children;
  for (int carIndex = 0; carIndex < cars.size();carIndex++)
  {
    Parking *child;
    int orientation = cars[carIndex].getOrientation();
    if (orientation == 1)
    {
      child = new Parking(*this);
      if (goUp(*child,carIndex))
      {
        children.push_back(child);
        return children;
      }
      else
        delete child;
      child = new Parking(*this);
      if (goDown(*child,carIndex))
      {
        children.push_back(child);
        return children;
      }
      else
        delete child;
    }
    else
    {
      child = new Parking(*this);
      if (goLeft(*child,carIndex))
      {
        children.push_back(child);
        return children;
      }
      else
        delete child;
      child = new Parking(*this);
      if (goRight(*child,carIndex))
      {
        children.push_back(child);
        return children;
      }
      else
        delete child;
    }
  }
  return children;
}