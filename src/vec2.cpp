#include "vec2.h" // 
#include "math.h" //
#include "utils.h" //
#include <stdio.h>//

vec2::vec2 (float x_, float y_) {
  this->x = x_; this->y = y_;
} 

vec2 vec2::operator+(const vec2& v) {
  vec2 r;
  r.x = this->x + v.x;
  r.y = this->y + v.y;
  return r;
}

vec2 vec2::operator-(const vec2& v) {
  vec2 r;
  r.x = this->x - v.x;
  r.y = this->y - v.y;
  return r;
}


vec2 vec2::projectedOn (vec2 v) { 
  return v.scale(dot(*this, v) / dot(v,v)); 
}


vec2 vec2::scale (float s) {
  return vec2(s*x, s*y); 
}

float vec2::magnitude2() {
  return x*x + y*y;
}

float vec2::magnitude() {
  return sqrtf(this->magnitude2());
}

vec2 vec2::normalize() {
  return scale(1/this->magnitude()); 
}

float dot(vec2& v0, vec2& v1) {
  return (v0.x * v1.x + v0.y * v1.y);
}

float angle(vec2& u, vec2& v) {
  return acosf(dot(u,v) / (u.magnitude() * v.magnitude())); 
} 

void vec2::print() {
  printf("x:%f; y:%f", x, y); 
}

vec2 randVec2(vec2 l, vec2 u) {
  return vec2(randF(l.x, u.x),
	      randF(l.y, u.y));
	      
}

void vec2::ap(std::function<void(float, float)> fn) { 
  fn(x,y); 
}


vec2 vec2::reflectedIn (vec2 a, vec2 b) {
  vec2 d = a - b;
  vec2 q(-d.y, d.x); 
  return reflectedIn(q);
}

vec2 vec2::reflectedIn (vec2 n) { 
  vec2 d(x,y); 
  vec2 d2 = d.scale(2);
  return d - (n.scale(dot(d2, n) / n.magnitude2()));
}



