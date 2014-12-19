#pragma once 

/** Various RNG helper functions */
float randF () ;
float randF (float a, float b) ;
int randI (int a, int b) ;

int min(int a, int b);
int max(int a, int b); 

enum DrawMode { Wire, Surface, WireAndSurface, HeightMap }; 

const char* drawModeName (DrawMode); 

int mod (int, int);  

#define PI 3.141592653589793

