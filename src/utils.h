#pragma once 

#include <GL/gl.h> 
#include <GL/glu.h> 
#include <GL/glut.h> 
#include <stdio.h>

/** Various RNG helper functions */
float randF () ;
float randF (float a, float b) ;
int randI (int a, int b) ;

int min(int a, int b);
int max(int a, int b); 

GLuint loadTextureRAW( const char * , bool );

int mod (int, int);  

#define PI 3.141592653589793

