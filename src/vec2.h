#pragma once

#include <functional>

/** A point in R^2. */
class vec2 {
 public:
  float x; float y; 
 
  // Create the point from its components.
  vec2(float, float); 
  
  // The point (0,0)
  vec2() {} ; 

  // Standard vector operations.
  // Pointwise sum.
  vec2 operator+(const vec2&); 

  // Pointwise difference.
  vec2 operator-(const vec2&);

  // Scale by the given amount.
  vec2 scale (float); 

  // The magnitude of the vector squared.
  float magnitude2(); 

  // The magnitude.
  float magnitude(); 

  // The vector which points in the same direction as this but has magnitude 1. 
  vec2 normalize();

  void print(); 
  
  void ap(std::function<void(float, float)>); 

  vec2 reflectedIn (vec2, vec2); 
  vec2 reflectedIn (vec2); 

  vec2 projectedOn (vec2); 

} ; 

// Dot product.
float dot(vec2&, vec2&);

// The smallest angle between two vectors.
float angle(vec2&, vec2&); 

// Random vector in the box whose upper left 
// corner is v1 and bottom right corner is v0. 
vec2 randVec2(vec2 v0, vec2 v1); 


