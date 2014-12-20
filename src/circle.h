#pragma once 

#include <functional>
#include "vec2.h"

enum CircleType { Puck, Paddle } ; 

class circle {
public:
  circle(CircleType);
  circle(CircleType, vec2, float);
  circle(CircleType, vec2, float, float);

  vec2 c;
  float r;
  float m; 
  vec2 v = vec2(0,0); 
  CircleType ty; 

  void init();
  void draw(); 
  void step(float);
  static bool collision (circle&, circle&); 
  static void performCollision (circle&, circle&, float);

};
