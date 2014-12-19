#include "utils.h"
#include "math.h"
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std; 

float randF () {
  float a = rand();
  float b = RAND_MAX;
  return a/b; 
}

float randF (float a, float b) {
  if (b<=a) return a;
  else return (randF() * (b-a) + a) ;  
}

int randI (int a, int b) {
  if (b<=a) return a;
  else return (rand() % (b-a) + a) ;  
}

int min (int a, int b) { if (a < b) { return a; } else { return b; } }
int max (int a, int b) { if (a > b) { return a; } else { return b; } }

const char* drawModeName (DrawMode m) { 
  switch (m) { 
  case Wire: return "Wire";
  case Surface: return "Surface";
  case WireAndSurface: return "Wire and surface";
  case HeightMap: return "Height map"; 
  }
  return 0; 
}

int mod (int a, int b) { 
  int r = a % b;
  if (r < 0) r += b;
  return r;
}
