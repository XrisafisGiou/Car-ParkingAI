#ifndef MAZE_H
#define MAZE_H
#define WIDTH  100
#define HEIGHT  100
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Maze
{
    public:
        Maze();
        Maze(int X, int Y, bool lights);
        void setFree(int i, int j, bool f);
        int getY();
        int getX();
        bool isFree(int x,int y);
        void setX(int x);
        void setY(int y);
        Maze operator= (Maze o);
        bool operator==(const Maze& o) const ;
        string toString () const;
        friend bool operator< (const Maze& a,const Maze& o);
        bool turnOn(Maze &n);
        bool turnOff (Maze &n);
        bool goUp(Maze &n);
        bool goDown(Maze &n);
        bool goLeft(Maze &n);
        bool goRight(Maze &n);
        vector <Maze *> expand();
        int getDepth();
        void setHvalue(double);
        double getHvalue();
        int heuristic (Maze *);
        void setActionName(string s) {actionName=s;}
        string getActionName()const {return actionName;}
        void setPrevious (Maze *p) {prev=p;}
        Maze *getPrevious()const {return prev;}
        unsigned long getKey()
        {
            unsigned long k = robX*1000000+robY*1000;
            if (lights) k+=1;
                return k;
        }
        friend ostream & operator<<(ostream &, const Maze &);
    protected:

    private:
        int robX,robY;
        bool free[WIDTH][HEIGHT];
        double Hvalue;
        string actionName;
        Maze *prev;
        bool lights;
};

class myComparator
{
public:
    int operator() (Maze *p1 , Maze *p2) const
    {
        return p1->getHvalue()>p2->getHvalue();
    }
};

#endif // MAZE_H
