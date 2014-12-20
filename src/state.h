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

const int initialScore = 20; 

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
  circle puck = circle(Puck, vec2(0,0), puckRadius); 
  vec2 p1; 
  bool lmbPressed = false; 
  int width = 700; 
  int height = 700;
  int playerPaddle = 0; 
  int time = 0;
  bool gameStarted = false; 
  GLuint texture; 

  // OpenGL handlers 
  void keyboard (unsigned char, int, int);
  void mouseMoved (int, int);
  void passiveMouseMoved (int, int);
  void mousePressed (int, int, int, int);
  void specialKey (int, int, int);
  void display();
  void reshape(int, int);
  void step();
  void step(float); 
  void init(); 
  
  
  int collideWithWalls1 (circle &, vector<wall> &, float); 
  void collideWithWalls (vector<circle> &, vector<wall> &, float); 
  void stepAI (float, float, int, circle &);
  void resetPuck();


  void setupLight (int);

  void startGame(); 
  void pauseGame(); 
  void newGame(); 
  void menuHandler(int);

};
