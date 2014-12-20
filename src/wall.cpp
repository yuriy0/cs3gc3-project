#include "wall.h"
#include "drawing.h"
#include "circle.h"
#include "stdio.h"
#include "math.h"
#include "utils.h"
#include <GL/gl.h> 
#include <GL/glu.h> 
#include <GL/glut.h> 
#include <vector>

using namespace std;

wall::wall(vec2 p0_, vec2 p1_) : p0(p0_), p1(p1_) { }
wall::wall(float a, float b, float c, float d) : p0(a,b), p1(c,d) { } 

void wall::draw() { 
  vec2 m = (p0 + p1).scale(0.5); 

  vec2 ux = vec2(1, 0);
  vec2 diff = p0 - p1;
  float al = angle(ux, diff); 

  if (diff.x > 0) { 
    if (diff.y > 0) { 
      al = al;
    } else { 
      al = -al;
    }
  } else {
    if (diff.y > 0) { 
      al = al;
    } else { 
      al = -al;
    }
  }

  glPushMatrix();
  glTranslatef( m.x, m.y, 0); 

  glRotatef( 180 * al / PI, 0, 0, 1);

  glScalef( diff.magnitude() , 0.01, 0.1 );

  glutSolidCube(1);
  glPopMatrix(); 
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


void wall::genInitial (int i, float rField, float rPaddle, float goalSize, 
		       vector<circle> & cs, vector<wall> & ws, vector<wall> & iws, vector<wall> & gws) { 
  vec2 points[2*i+1]; 
  float gR = 0.5*goalSize; 

  // Compute the angles 
  for (int k = 0; k < 2*i+1; k++) { 
    float al = PI*k/i;
    points[k] = vec2(rField * cosf(al), rField * sinf(al)); 
  }

  // Compute the data. 
  for (int k = 0; k < i; k++) {
    vec2 p0 = points[2*k  ];
    vec2 p1 = points[2*k+1];
    vec2 p2 = points[2*k+2];
    vec2 m0 = (p0 + p1).scale(0.5); 
    vec2 m1 = (p1 + p2).scale(0.5);
    vec2 g0 = p0 + (p1 - p0).scale(0.5 - gR);
    vec2 g1 = p0 + (p1 - p0).scale(0.5 + gR);

    wall solidWall (p1, p2) ; 
    wall toMiddle (m1, vec2(0,0)); 
    circle circ (Paddle, m0.scale(0.8), rPaddle); 

    wall side1(p0,g0); 
    wall side2(g1,p1);

    wall gateWall (g0, g1);

    cs.push_back(circ);

    iws.push_back(toMiddle);
    gws.push_back(gateWall);
    ws.push_back(side1);
    ws.push_back(side2); 
    ws.push_back(solidWall);
  }
}
