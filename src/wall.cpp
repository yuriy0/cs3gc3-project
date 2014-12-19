#include "wall.h"
#include "drawing.h"
#include "stdio.h"
#include <GL/gl.h> 
#include <GL/glu.h> 
#include <GL/glut.h> 

wall::wall(vec2 p0_, vec2 p1_) : p0(p0_), p1(p1_) { }
wall::wall(float a, float b, float c, float d) : p0(a,b), p1(c,d) { } 

void wall::draw() { 
  drawLineSegment(p0, p1); 
}


bool wall::collision (vec2 c, float r, vec2 & o) { 
  vec2 p0_c = c - p0;                    // Vector from center to endpoint
  vec2 p0_p1 = p1 - p0;                  // Vector from endpoint to endpoint
  vec2 p0_m = p0_c.projectedOn(p0_p1);   // Projection of centre onto the line
  float lenL = p0_p1.magnitude();        // Length of the line
  vec2 m_l = (p0 + p1).scale(0.5);       // Midpoint of the line
  vec2 m = p0_m + p0;                    // "Intersection" point
  vec2 c_m = m - c;                      // Vector from centre to intersection
  float dist = c_m.magnitude();          // Distance from centre to line

  // printf ("to center = %f, %f   ", p0_m.x, p0_m.y); 
  // printf ("line = %f, %f \n",  p0_p1.x,  p0_p1.y); 

  // glColor3f(0, 0, 1); 
  // drawLineSegment(c, p0);
  // drawLineSegment(p1 + vec2(0.01, 0.01), p0 + vec2(0.01, 0.01));

  // glColor3f(1, 0, 0); 
  // drawLineSegment(m, c); 

  // glColor3f(0, 1, 0); 
  // drawLineSegment(m - vec2(0.01, 0.01), p0 - vec2(0.01, 0.01)); 

  // glColor3f(1, 1, 1); 

  // If the distance is more than the radius, there is no collision
  bool tooFar = dist > r;                        

  // If the distance from the intersection to the midpoint is more
  // than half the length, the intersection is outside the line
  // segment, so there is no collision
  bool outSide = (m_l - m).magnitude() > lenL/2; 

  if (tooFar ||outSide) { return false; }
  else {
    o = m; 
    return true; 
  }
}
