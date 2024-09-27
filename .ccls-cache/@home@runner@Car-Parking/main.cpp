#include <iostream>
#include "Car.h"
#include "Parking.h"
#include <queue>
#include <algorithm>
#include <chrono>

Parking *BFS(Parking *initial,Parking *goal, long long &examined, long long &mem)
{
    queue<Parking *> agenda;
    vector <Parking> closed;

    agenda.push(initial);
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        Parking *s = agenda.front();
        agenda.pop();
        if (find(closed.begin(), closed.end(), *s)==closed.end())
        {
            examined++;
            if (*s==*goal)
                return s;
            closed.push_back(*s);
            vector<Parking *> children =s->expand();
            for (unsigned int i=0;i<children.size();i++)
            {
                if (find(closed.begin(), closed.end(), *children[i])==closed.end())
                    agenda.push(children[i]);
            }
        }
    }
    return nullptr;
}


void easy(Parking *&initial, Parking *&goal) 
{
  Parking *p = new Parking(4,3);
  p->setFree(0,1,false);
  p->setFree(2,0,false);
  p->setFree(3,2,false);
  Parking *g = new Parking(*p); 
  Car c1(1,1,2);
  Car c2(2,1,1);
  Car c3(2,2,2);
  p->setCar(c1);
  p->setCar(c2);
  p->setCar(c3);
  initial = p;
  goal = g;
}

void medium(Parking *&initial, Parking *&goal)
{
    Parking *p = new Parking(6,6);
    p->setFree(0,0,false);
    p->setFree(1,4,false);
    p->setFree(3,1,false);
    p->setFree(3,5,false);
    p->setFree(4,2,false);
    p->setFree(5,4,false);
    Parking *g = new Parking(*p);
    Car c1(1,1,1);
    Car c2(2,0,2);
    Car c3(2,4,1);
    Car c4(2,5,2);
    Car c5(4,0,1);
    Car c6(4,3,1);
    p->setCar(c1);
    p->setCar(c2);
    p->setCar(c3);
    p->setCar(c4);
    p->setCar(c5);
    p->setCar(c6);
    initial = p;
    goal = g;
}

void hard(Parking *&initial, Parking *&goal)
{
    Parking *p = new Parking(4,11);
    p->setFree(0,2,false);
    p->setFree(0,5,false);
    p->setFree(1,1,false);
    p->setFree(1,4,false);
    p->setFree(1,7,false);
    p->setFree(1,9,false);
    p->setFree(2,0,false);
    p->setFree(2,10,false);
    p->setFree(3,3,false);
    p->setFree(3,6,false);
    Parking *g = new Parking(*p);
    Car c1(0,0,2);
    Car c2(0,1,1);
    Car c3(0,6,1);
    Car c4(1,3,2);
    Car c5(2,8,2);
    Car c6(3,0,2);
    Car c7(3,1,1);
    Car c8(3,2,1);
    Car c9(3,8,1);
    Car c10(3,9,2);
    p->setCar(c1);
    p->setCar(c2);
    p->setCar(c3);
    p->setCar(c4);
    p->setCar(c5);
    p->setCar(c6);
    p->setCar(c7);
    p->setCar(c8);
    p->setCar(c9);
    p->setCar(c10);
    initial = p;
    goal = g;
}

int main() {
  long long mem,examined;
  Parking *initial;
  Parking *goal;
  
  int diff;
  cout << "Choose difficulty 1,2,3 :"<< endl;
  cin >> diff;
  if (diff == 1)
    easy(initial,goal);
  else if (diff == 2)
    medium(initial,goal);
  else if (diff == 3)
    hard(initial,goal);
  else
  {
    cout<<"Wrong Input";
    return 0;
  }
  
  Parking *bsol;
  cout<<"Initial:"<<endl<<initial->toString()<<endl;
  cout<<"Goal:"<<endl<<goal->toString()<<endl;

  auto start_time = chrono::high_resolution_clock::now();
  bsol = BFS(initial,goal,examined,mem);
  if (bsol!=nullptr)
    {
        for (int i = bsol->getSolution().size();i>=0;i--)
        {
          cout << bsol->getSolution()[i];
        } 
    }
    else
        cout<<"Problem unsolvable"<<endl;

  auto end_time = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
  cout << endl << "Time taken: " << duration.count() << " microseconds" << endl;
  
  return 0;
}