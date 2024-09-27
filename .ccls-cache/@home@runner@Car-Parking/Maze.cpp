#include "Maze.h"
Maze::Maze()
{
    for (int i=0;i<WIDTH;i++)
        for (int j=0;j<HEIGHT;j++)
            free[i][j]=true;
    setActionName("");
    setPrevious(nullptr);
}
Maze::Maze(int X, int Y, bool lights)
{
    robX=X;
    robY=Y;
    this->lights = lights;
    lights=true;

    for (int i=0;i<WIDTH;i++)
        for (int j=0;j<HEIGHT;j++)
            free[i][j]=true;
    setActionName("");
    setPrevious(nullptr);

}

int Maze::getDepth()
{
    int counter =0;
    Maze *p = this;
    while (p->prev!=nullptr)
    {
        p=p->prev;
        counter++;
    }
    return counter;
    //return path.size();
}
void Maze::setFree(int i, int j, bool f)
{
    free[i][j]=f;
}
int Maze::getY()
{
    return robY;
}
int Maze::getX()
{
    return robX;
}
bool Maze::isFree(int x,int y)
{
    return free[x][y];
}
void Maze::setX(int x)
{
    robX=x;
}
void Maze::setY(int y)
{
    robY=y;
}
bool Maze::operator==(const Maze& s) const
{
    return (robX==s.robX && robY==s.robY && lights==s.lights);
}
Maze Maze::operator= (Maze o)
{
    lights = o.lights;
    robX = o.robX;
    robY = o.robY;
    prev = o.prev;
    actionName = o.actionName;
    return *this;
}
string Maze::toString () const
{
    stringstream ot;
    ot << robX<<"-"<<robY<<"-";
    if (lights)
        ot<<"true";
    else
        ot<<"false";
    return ot.str();
}
bool operator< (const Maze& a,const Maze& o)
{
    return (a.toString() < o.toString());
}

bool Maze::turnOn(Maze &n)
{
    if (!lights)
    {
        n=*this;
        n.lights=true;
        n.setActionName("SwitchOn");
        n.setPrevious(this);
        return true;
    }
    return false;
}

bool Maze::turnOff (Maze &n)
{
    if (lights)
    {
        n=*this;
        n.lights=false;
        n.setActionName("SwitchOff");
        n.setPrevious(this);
        return true;
    }
    return false;
}
bool Maze::goUp(Maze &n)
{
    if (getY()>0 && isFree(getX(),getY()-1))
    {
        n=*this;
        n.setY(n.getY()-1);
        n.setActionName("Up");
        n.setPrevious(this);
        return true;
    }
    return false;
}

bool Maze::goDown(Maze &n)
{
    if (getY()<HEIGHT-1 && isFree(getX(),getY()+1))
    {
        n=*this;
        n.setY(n.getY()+1);
        n.setActionName("Down");
        n.setPrevious(this);
        return true;
    }
    return false;
}
bool Maze::goLeft(Maze &n)
{
    if (getX()>0 && isFree(getX()-1,getY()))
    {
        n=*this;
        n.setX(n.getX()-1);
        n.setActionName("Left");
        n.setPrevious(this);
        return true;
    }
    return false;
}
bool Maze::goRight(Maze &n)
{
    if (getX()<WIDTH-1 && isFree(getX()+1,getY()))
    {
        n=*this;
        n.setX(n.getX()+1);
        n.setActionName("Right");
        n.setPrevious(this);

//        n.path.push_back("Right");
        return true;
    }
    return false;
}

vector <Maze *> Maze::expand()
{
    vector <Maze *> children;
    Maze *child;
    child = new Maze(*this);
    if (goUp(*child))
        children.push_back(child);
    else
        delete child;
    child = new Maze(*this);
    if (goDown(*child))
        children.push_back(child);
    else
        delete child;
    child = new Maze(*this);
    if (goLeft(*child))
        children.push_back(child);
    else
        delete child;
    child = new Maze(*this);
    if (goRight(*child))
        children.push_back(child);
    else
        delete child;
    child = new Maze(*this);
    if (turnOn(*child))
        children.push_back(child);
    else
        delete child;
    child = new Maze(*this);
    if (turnOff(*child))
        children.push_back(child);
    else
        delete child;
    return children;
}
int Maze::heuristic (Maze *goal)
{
    int dist = abs(goal->robX-robX) + abs(goal->robY-robY);
    if (lights!=goal->lights)
        dist++;
    return dist;
};

void Maze::setHvalue(double h)
{
    Hvalue = h;
}

double Maze::getHvalue()
{
    return Hvalue;
}

ostream & operator<<(ostream &stream,const Maze &a)
{
    string s="";

    s= a.getActionName();
    Maze *p=a.getPrevious();

    while (p!=nullptr)
    {
        s = p->getActionName()+" "+s;
        p = p->getPrevious();
    }
    stream <<s;
    return stream;
}

