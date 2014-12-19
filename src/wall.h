#pragma once

#include "vec2.h"

class wall { 
public:
  wall(vec2, vec2);
  wall(float, float, float, float);

  vec2 p0; vec2 p1; 
  void draw(); 
  bool collision (vec2, float, vec2 &); 
};
