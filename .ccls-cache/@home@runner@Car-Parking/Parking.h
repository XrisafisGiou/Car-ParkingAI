#ifndef PARKING_H
#define PARKING_H
#include <string>
#include <sstream>
#include <vector>
#include "Car.h"

using namespace std;

class Parking
{
    public:
        Parking(int width, int height);
        Parking(){};
        void setFree(int i, int j, bool f);
        bool isFree(int x,int y);
        void setCar(Car c);
        Parking operator= (Parking o);
        bool operator==(const Parking& o) const ;
        string toString ();
        friend bool operator< (const Parking& a,const Parking& o);
        bool goUp(Parking &n,int carIndex);
        bool goDown(Parking &n,int carIndex);
        bool goLeft(Parking &n,int carIndex);
        bool goRight(Parking &n,int carIndex);
        vector <Parking *> expand();
        int getDepth();
        vector < string > getSolution();
        void setActionName(string s) {actionName=s;}
        string getActionName()const {return actionName;}
        void setPrevious (Parking *p) {prev=p;}
        Parking *getPrevious()const {return prev;}
    private:
        int width, height;
        vector< vector<bool> > free;
        vector< Car > cars;
        string actionName;
        Parking *prev;
};

#endif