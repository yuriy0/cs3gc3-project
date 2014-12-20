#pragma once 

#include "utils.h"
#include <stdio.h> 
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "wall.h"
#include "math.h"
#include "drawing.h"
#include "circle.h"

#include <GL/gl.h> 
#include <GL/glu.h> 
#include <GL/glut.h> 

using namespace std;

const float puckRadius = 0.03;
const float puckMass = 0.3;

const float paddleRadius = 0.05; 
const float paddleMass = 1;

const float fieldRadius = 0.8;
const float frictionCoefficient = 0.09; 
const float gateSize = 0.2; 

class state { 
public:

  state(); 
  state(int); 
  
  vector<circle> cs;
  vector<wall> ws;
  vector<wall> iws; 
  vector<wall> gws;
  vector<int> score; 
  
  int numPlayers; 
  
  circle puck; // (vec2(0,0), puckRadius); 

  vec2 p1; // (0,0); 
  
  bool lmbPressed = false; 
  
  int width; int height; 

  // OpenGL handlers 
  void keyboard (unsigned char, int, int);
  void mouseMoved (int, int);
  void passiveMouseMoved (int, int);
  void mousePressed (int, int, int, int);
  void specialKey (int, int, int);
  void display();
  
  
  bool collideWithWalls (vector<circle> &, vector<wall> &, float); 
  void stepAI (float, float, int, circle &);
  void resetPuck();
  

};
