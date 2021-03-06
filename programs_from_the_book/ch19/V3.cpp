#include <simplecpp>
#include "V3.h"

V3::V3(double x1, double y1, double z1){
  x = x1;
  y = y1;
  z = z1;
}

V3 V3::operator+(V3 const &w)const { return V3(x+w.x, y+w.y, z+w.z); }
V3 V3::operator-(V3 const &w)const { return V3(x-w.x, y-w.y, z-w.z); }

V3 V3::operator*(double t){ return V3(x*t, y*t, z*t); }

double V3::length(){ return sqrt(x*x+y*y+z*z); }

double V3::getx(){return x;}
double V3::gety(){return y;}
double V3::getz(){return z;}

ostream & operator<<(ostream & ost, V3 v){
  ost << "(" << v.x << ", "<< v.y << ", "<< v.z << ")";
  return ost;
}




  
