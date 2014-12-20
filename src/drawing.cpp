#include "drawing.h"
#include "vec2.h"
#include "utils.h"
#include "math.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void drawLineSegment(vec2 a, vec2 b) { 
  glBegin(GL_LINE_STRIP); 
  glVertex3f(a.x, a.y, 0);
  glVertex3f(b.x, b.y, 0);
  glEnd();

}

void drawCircle(vec2 c, float r) { 
  glBegin(GL_POLYGON);
  for (int i = 0; i < 32; i++) { 
    float alpha = i*PI*2/32; 
    glVertex3f(r*cosf(alpha) + c.x, r*sinf(alpha) + c.y, 0); 
  }
  glEnd();
}

