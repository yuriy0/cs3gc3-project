#pragma once

#include "vec2.h"
#include "circle.h"
#include <vector>

using namespace std;

class wall { 
public:
  wall() { }
  wall(vec2, vec2);
  wall(float, float, float, float);

  vec2 p0; vec2 p1; 
  void draw(); 
  bool collision (vec2, float, vec2 &); 

  static void genInitial (int, float, float, float, vector<circle>&, vector<wall>&, vector<wall>&, vector<wall>&); 
  
};
