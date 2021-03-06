#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cassert>
#include <simplecpp>

class taxiway : public Line, public Resource{
public:
  int traversalT;
  double stepsize;
  taxiway(float xa, float ya, float xb, float yb, int trT)
    : Line(xa,ya,xb,yb), traversalT(trT),
    stepsize(sqrt(pow(xa-xb,2)+pow(ya-yb,2))/traversalT) {}
};

const int nGates = 10, nSegments = 6+3*nGates;
const int toGates = 5+nGates, fromGates = 5+2*nGates, halfRW = 5 + 3*nGates;

const int preLanding = -1, landing = 0, rightTaxiway = 1,
  leftTaxiway = toGates-2, takeOff = toGates-1; 

class planeShape : public Polygon{
 public:
  planeShape(){
    double pts[14][2] = {{10, 0}, 
			 {0,3}, {-8,15}, {-5,3}, {-10,3},{-13,6},
			 {-13,-6},{-10,-3},{-5,-3},{-8,-15},{0,-3},{10,0}};
    reset(canvas_width()/2,canvas_height()/2, pts, 13);
    setScale(2.8);
    setFill();
    setColor(COLOR("blue"));
    //    penDown();
  }
};




class plane : public planeShape {
  int id;                // identifying number for plane
  int arrivalT;          // arrival time
  int serviceT;          // how long the aircraft waits at the gate
  int segment;           // index of taxiway segment the aircraft is on
  int timeToSegmentEnd;  // how far from the end of the segment
  int gate;              // id of allocated gate
  vector<taxiway*> &taxiways;
public:
  plane(int i, int at, int st, vector<taxiway*> &tw) 
    : id(i), arrivalT(at), serviceT(st), taxiways(tw) {
    segment = preLanding; // currently before the landing runway.
    timeToSegmentEnd = 0;
    hide();
    penUp();
    gate = -10*nGates;   // indicates gate not allocated
    sim::post(arrivalT, [=](){prepareToEnterSegment();});
  }
  void prepareToEnterSegment();
  void land();
  void enter(int newsegment);
  void moveOnSegment();
  void requestGate();
  void turnToGate();
  void atGate();
  void backOnTaxiway();
  void prepareToTakeOff();
  void depart();
  void ordinarySegment();
};

