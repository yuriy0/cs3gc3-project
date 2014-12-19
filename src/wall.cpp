
#include "wall.h"
#include "drawing.h"
#include "stdio.h"

wall::wall(vec2 p0_, vec2 p1_) : p0(p0_), p1(p1_) { }
wall::wall(float a, float b, float c, float d) : p0(a,b), p1(c,d) { } 

void wall::draw() { 
  drawLineSegment(p0, p1); 
}

bool wall::collision (vec2 c, float r, vec2 & o) { 
  vec2 p0_c = c - p0; 
  vec2 p0_p1 = p1 - p0;

  vec2 p0_m = p0_p1.projectedOn(p0_c); 
  float p0_mM = p0_m.magnitude(); 

  if (p0_mM > r) { 
    printf ("Too far "); 
    return false; 
  }

  if (p0_m.x < 0       || p0_m.y < 0      ) { 
    printf ("Left of line "); 
    return false; 
  }


  if (p0_m.x > p0_p1.x || p0_m.y > p0_p1.y) { 
    printf ("Right of line "); 
    return false; 
  }
  

  o = p0_m + p0; 
  return true; 
}

// class wall { 
// public:
//   vec2 p0, p1; 
//   void draw(); 
//   bool collision (vec2, float); 
// }
