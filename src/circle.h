#pragma once 

#include "vec2.h"

class circle {
public:
  circle() { }
  circle(vec2, float);
  circle(vec2, float, float);

  vec2 c;
  float r;
  float m; 
  vec2 v = vec2(0,0); 

  void draw(); 
  void step(float);
  static bool collision (circle&, circle&); 
  static void performCollision (circle&, circle&, float);

};
