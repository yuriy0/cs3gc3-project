#include "drawing.h"
#include "circle.h"
#include "math.h"
#include <functional>
#include "utils.h"

#include <GL/gl.h> 
#include <GL/glu.h> 
#include <GL/glut.h> 

using namespace std; 

circle::circle (CircleType ty_, vec2 c_, float r_) : c(c_), r(r_), m(1), ty(ty_) { 
  init();
}

circle::circle (CircleType ty_, vec2 c_, float r_, float m_) : c(c_), r(r_), m(m_), ty(ty_) { 
  init();
}

circle::circle (CircleType ty_) : ty(ty_) { 
  init();
} 

void circle::draw () { 
  glPushMatrix();
  glTranslatef(c.x, c.y, 0);

  if (ty == Paddle) { 
    glPushMatrix();
    glTranslatef(0, 0, 0.5*r);
    glScalef(0.5, 0.5, 1); 
    glutSolidSphere(r, 20, 20);
    glPopMatrix(); 
  }

  glutSolidSphere(r, 20, 20);

  glPopMatrix(); 
}

void circle::init() {  
}


bool circle::collision (circle& a, circle& b) {
  float dist2 = (a.c - b.c).magnitude2(); 
  float r = a.r + b.r; 
  float r2 = r*r; 
  
  return dist2 < r2;
}


void circle::step(float delta) { 
  c = c + v.scale(delta);
}

// http://farside.ph.utexas.edu/teaching/301/lectures/node76.html
void circle::performCollision (circle& a, circle& b, float delta) {
  a.v.scale(delta);
  b.v.scale(delta);

  vec2 colPlane = a.c - b.c; 
  vec2 colPlaneO(-colPlane.y, colPlane.x); 

  vec2 aVP = a.v.projectedOn(colPlane); 
  vec2 aVC = a.v.projectedOn(colPlaneO);

  vec2 bVP = b.v.projectedOn(colPlane); 
  vec2 bVC = b.v.projectedOn(colPlaneO);

  float mSum = a.m + b.m;
  float mDiff = (a.m - b.m) / mSum; 
  float aMr = 2 * a.m / mSum;
  float bMr = 2 * b.m / mSum; 

  vec2 aVPF = aVP.scale(mDiff) + bVP.scale(bMr  );
  vec2 bVPF = aVP.scale(aMr  ) - bVP.scale(mDiff);

  a.v = aVC + aVPF;
  b.v = bVC + bVPF; 

  a.v.scale(1 / delta);
  b.v.scale(1 / delta);
}    


