
#include "state.h"

state::state(int n) : numPlayers(n) { 
  resetPuck();
  p1 = vec2(0,0);
  wall::genInitial(numPlayers, fieldRadius, paddleRadius, gateSize, cs, ws, iws, gws);
  for (int i = 0; i<numPlayers; i++) { 
    score.push_back(0); 
  }
}

state::state() : state(3) { } 

void state::resetPuck() { 
  puck = circle(vec2(0,0), puckRadius); 
  puck.m = 0.3; 
}

void state::keyboard (unsigned char a, int b, int c) { 
}

void state::stepAI (float m, float diff, int i, circle & c) { 
  int n = numPlayers; 
  vec2 towardsPuck = puck.c - c.c ;
  float dist = towardsPuck.magnitude(); 
  
  vec2 toAdd = vec2(0,0);

  if (dist < 0.4) { 
    toAdd = towardsPuck.scale((3 * diff * m) / (1 + dist)); 
  } else { 
    float al = 2*PI*(4*i+1)/(4.0*n);
    toAdd = vec2 (cosf(al), sinf(al));
    toAdd = toAdd.scale(0.55); 
    toAdd = (toAdd - c.c).scale(diff * m);
  }
  c.v = c.v + toAdd; 
}

void state::mouseMoved (int a, int b) {
  float dx = (a - p1.x) / (600);
  float dy = (p1.y - b) / (600);

  if (lmbPressed) {
    cs[0].v.x += 0.07 * dx;
    cs[0].v.y += 0.07 * dy;

  }
  p1.x = a;
  p1.y = b;
}

void state::passiveMouseMoved (int b, int c) {
  p1.x = b;
  p1.y = c;
}

void state::mousePressed (int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    lmbPressed = state == GLUT_DOWN; 
  } 

  // if (state == GLUT_DOWN) { 
  //   lmbPressed = true;
  // }

  // if(state != GLUT_DOWN) return;
 
  // float window_width = glutGet(GLUT_WINDOW_WIDTH);
  // float window_height = glutGet(GLUT_WINDOW_HEIGHT);
 
  // unsigned int index;
  // glReadPixels(x, window_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
 
  // printf ("Stencil at %d %d : %d \n", x, y, index); 
}

void state::specialKey (int key, int b, int c) {  
  // switch(key) {
  // case GLUT_KEY_UP:    
  //   cs[0].v.y += 0.001;
  //   break;
  // case GLUT_KEY_DOWN:  
  //   cs[0].v.y -= 0.001;
  //   break;
  // case GLUT_KEY_LEFT:  
  //   cs[0].v.x -= 0.001;
  //   break;
  // case GLUT_KEY_RIGHT: 
  //   cs[0].v.x += 0.001; 
  //   break;
  // default:
  //   return; 
  // }
}

bool state::collideWithWalls (vector<circle> & cs, vector<wall> & ws, float m) {
  boolean r = false;
  for (int j = 0; j < cs.size(); j++) { 
    for (int i = 0; i < ws.size(); i++) { 
      vec2 o;
      bool b = ws[i].collision(cs[j].c, cs[j].r, o);

      if (b) {
  	cs[j].step(-m);

  	vec2 vel(cs[j].v.x, cs[j].v.y);
  	vel = vel.reflectedIn(ws[i].p0, ws[i].p1);
  	cs[j].v = vel;

  	cs[j].step(m);
	r = true;
  	break; 
      } 
    }
  }
  return r; 
}

void state::display() { 

  float m = 1;
  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glViewport (0, 0, 600, 600);      

  // reset model view 
  glMatrixMode (GL_MODELVIEW);                     
  glLoadIdentity ();       
  
  // Draw the colour ramp scale 
  // Clear the projection matrix
  glMatrixMode (GL_PROJECTION);                     
  glLoadIdentity ();              

  for (wall & w : ws) { w.draw(); }

  glColor3f(0.3, 0.3, 0.3);
  for (wall & iw : iws) { iw.draw(); }
  for (wall & gw : gws) { gw.draw(); }
  glColor3f(1, 1, 1);

  cs[0].draw(); 
  cs[0].step(m);

  for (int i = 1; i < cs.size(); i++) {
    cs[i].draw(); 
    cs[i].step(m);
    stepAI(m, 0.005, i, cs[i]); 
  }

  puck.draw(); 
  puck.step(m); 


  cs.push_back(puck); 
  bool collided[cs.size()] ; 
  for (int i = 0; i < cs.size() + 1; i++) collided[i] = false;  

  // Collision with other pucks 
  for (int i = 0; i < cs.size(); i++) { 
    for (int j = 0; j < cs.size(); j++) { 

      if (i != j && !collided[i] && !collided[j] && circle::collision(cs[i], cs[j])) { 
  	cs[i].step(-m); cs[j].step(-m);

  	circle::performCollision(cs[i], cs[j], 1); 

  	cs[i].step(m); cs[j].step(m);
  	collided[i] = collided[j] = true; 

      } 
    }
  }

  collideWithWalls(cs,  ws, m);

  puck = cs[cs.size() - 1]; 
  cs.pop_back(); 

  collideWithWalls(cs, iws, m); 
  collideWithWalls(cs, gws, m); 
  
  vector<wall> gwsC (gws); 

  vector<circle> puck_; 
  puck_.push_back(puck);

  if (collideWithWalls(puck_, gws, m)) { 
    puck = circle(vec2(0,0), puckRadius);
    puck.m = 0.3; 
  }
  
  for (circle & c : cs) { 
    c.v = c.v.scale(0.9); 
  }
  puck.v.scale(0.9); 

  glutSwapBuffers();
  glutPostRedisplay ();
}
