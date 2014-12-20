#include "state.h"

#include <iostream>    
#include <sstream>      

#include <GL/gl.h> 
#include <GL/glu.h> 
#include <GL/glut.h> 

using namespace std; 

state::state(int n) : numPlayers(n) { 
  init(); 
}

state::state() : state(3) { } 

void state::resetPuck() { 
  puck = circle(Puck, vec2(0,0), puckRadius); 
  puck.m = 0.3; 
}

void state::init() { 
  gameStarted = false; 
  cs.clear();
  ws.clear();
  iws.clear(); 
  gws.clear();
  score.clear(); 

  resetPuck();
  p1 = vec2(0,0);
  wall::genInitial(numPlayers, fieldRadius, paddleRadius, gateSize, cs, ws, iws, gws);
  for (int i = 0; i<numPlayers; i++) { 
    score.push_back(initialScore); 
  }
  playerPaddle = numPlayers - 1; 
}

void state::keyboard (unsigned char a, int b, int c) { 

  switch (a) {
  case 'p':
  case 'P':
    gameStarted = !gameStarted; 
    break; 
  case 'n':
  case 'N': 
    newGame(); 
    break; 
  case '1':
  case '2':  
  case '3':  // Set the difficulty and make a new game
    difficulty = (int)a - 49; // '1' == chr(49)
    newGame(); 
    break;
  case 'q':
  case 'Q':
  case 27:
    exit(0);
    break;
  }
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
  if (!gameStarted) return; 
  float dx = (a - p1.x) / width;
  float dy = (p1.y - b) / height;

  if (lmbPressed) {
    cs[playerPaddle].v.x += 0.09 * dx;
    cs[playerPaddle].v.y += 0.09 * dy;
  }

  p1.x = a;
  p1.y = b;
}

void state::passiveMouseMoved (int b, int c) {
  p1.x = b;
  p1.y = c;
}

void state::mousePressed (int button, int state, int x, int y) {
  if (!gameStarted) return; 
  if (button == GLUT_LEFT_BUTTON) {
    lmbPressed = state == GLUT_DOWN; 
  } 
}

void state::specialKey (int key, int b, int c) { }

int state::collideWithWalls1 (circle & cr, vector<wall> & ws, float m) {
  for (int i = 0; i < ws.size(); i++) { 
    vec2 o;
    bool b = ws[i].collision(cr.c, cr.r, o);

    if (b) {
      cr.step(-m);

      vec2 vel(cr.v.x, cr.v.y);
      vel = vel.reflectedIn(ws[i].p0, ws[i].p1);
      cr.v = vel;

      cr.step(m);
      return i;
      break; 
    } 
  }
  return -1; 
}

void state::collideWithWalls (vector<circle> & cs, vector<wall> & ws, float m) {
  for (int j = 0; j < cs.size(); j++) {
    collideWithWalls1(cs[j], ws, m); 
  }
}



const float diffArr [] = { 0.005, 0.01, 0.02 }; 

void state::step(float m) { 
  for (int i = 0; i < cs.size(); i++) {
    cs[i].step(m);
    if (i != playerPaddle) stepAI(m, diffArr[difficulty], i, cs[i]); 
  }

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
}


void state::step() { 
  // Compute the time since the last invocation of step
  int t = glutGet(GLUT_ELAPSED_TIME);
  int dt_ = t - time;
  float dt = 0.001 * (float)dt_; // The time in seconds. 
  time = t; 

  if (!gameStarted) return; 
  
  float m = 50 * dt; 
  int steps = 4; 
  for (int i = 0; i < steps; i++) { 
    step(m / (float)steps); 
  }
  
  vector<wall> gwsC (gws); 
  int si = collideWithWalls1(puck, gwsC, m);
  if (si != -1) { 
    resetPuck();
    score[si] -= 1; 
    if (score[si] <= 0) init(); 
  }
 
  for (circle & c : cs) { 
    c.v = c.v.scale(0.9); 
  }
  puck.v.scale(0.9); 

}

void state::reshape(int w, int h) {
  glutReshapeWindow(width, height);
}

// Values for the lights. 
const float ambientLight[] =  { 0.2 , 0.2 , 0.2 , 1 };
const float diffuseLight[] =  { 0.6 , 0.6 , 0.6 , 1 }; 
const float specularLight[] = { 0.0 , 0.0 , 0.0 , 1 };
const float emissionLight[] = { 0.0 , 0.0 , 0.0 , 1 };
// const float position[] = { 0, 0 , - 40, 1};
const float position[] = {0,0, -1, 1};

void state::setupLight (int n) { 
  // According the openGL implementation, GL_LIGHTi = GL_LIGHT0 + i.
  glEnable(GL_LIGHT0 + n); 

  // Set all the light parameters.
  glLightfv(GL_LIGHT0 + n, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0 + n, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0 + n, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0 + n, GL_EMISSION, emissionLight);

  glPushMatrix(); 
  glLightfv(GL_LIGHT0 + n, GL_POSITION, position);
  glPopMatrix(); 
}

void state::display() { 
  // clear buffers
  glClearColor(0.6,0.6,0.7,1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  float sq = fmin(height, width); 
  glViewport (0, 0, sq, sq);      

  
  glColor3f(0, 0, 0);
  glDisable(GL_LIGHTING);
  // Text for score etc 
  float yPos = 0.95;
  float xPos = 0.7;
  glPushMatrix();
  glLoadIdentity();

  for (int i = 0; i < numPlayers; i++) {
    glRasterPos2f(xPos, yPos); yPos -= 0.05;
    ostringstream s;
    s << i << " : " << score[i];  
    string str = s.str();

    for (int j = 0; j < str.length() ; j++) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[j]);
    }
  }
  glPopMatrix();


  // Text for difficulty
  glPushMatrix();
  glLoadIdentity();
  glRasterPos2f(xPos, yPos);

  string str; 
  switch (difficulty) {
  case 0: str = "Easy"; break;
  case 1: str = "Medium"; break;
  default: str = "Hard"; break;
  }
    
  for (int i = 0; i < str.length() ; i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
  }
  yPos -= 0.05; 
  glPopMatrix();

  // Text for pause
  if (!gameStarted) {
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2f(xPos, yPos);

    string str = "Paused";
    
    for (int i = 0; i < str.length() ; i++) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
    }
    glPopMatrix();
  }

  // Draw the colour ramp scale 
  // Clear the projection matrix
  glMatrixMode (GL_PROJECTION);                     
  glLoadIdentity ();              

  // reset model view 
  glMatrixMode (GL_MODELVIEW);                     
  glLoadIdentity ();       
  
  float q = 0.5;
  glScalef(q, q, q); 

  // Enable the lights.
  setupLight(1);
  
  gluPerspective(50, 1, 0.1, 100); 

  // Set the camera to look at the origin
  gluLookAt(0, 0,  1,
  	    0, 0,  0,
  	    0, 1,  0);


  glTranslatef(0, 0.1, 0); 


  glRotatef(-30, 1, 0, 0);


  glEnable(GL_LIGHTING);

  glBindTexture( GL_TEXTURE_2D, texture );
  glEnable(GL_TEXTURE_2D);

  glColor3f(1, 1, 1);
  glBegin( GL_POLYGON );
  for (int i = 0; i < 2*numPlayers; i++) {
    float al = i * PI / numPlayers; 
    float xc = fieldRadius * cosf(al);
    float yc = fieldRadius * sinf(al);
    glTexCoord3d(-xc, yc, -0.05); glVertex3d(xc, yc, -0.05); 
  }
  glEnd();

  glDisable(GL_TEXTURE_2D);


  // Tell openGL to use the normals we specify as materials. 
  glColorMaterial(GL_FRONT_AND_BACK, 
		  GL_AMBIENT
		  // GL_AMBIENT_AND_DIFFUSE
		  );

  // Enable the above. 
  glEnable(GL_COLOR_MATERIAL);


  glColor3f(1, 1, 1);
  for (wall & w : ws) { w.draw(); }

  glColor3f(0.3, 0.3, 0.3);
  // for (wall & iw : iws) { iw.draw(); }
  for (wall & iw : iws) { 
    drawLineSegment(iw.p0, iw.p1); 
  }
  for (wall & gw : gws) { gw.draw(); }

  for (int j = 0; j < cs.size(); j++) {
    if (j == playerPaddle) { glColor3f (1, 0, 0); } 
    else { glColor3f (0, 0, 1); }
    cs[j].draw();
  }
  // for (circle & c : cs) { c.draw(); }

  glColor3f (1, 0.5, 0);

  puck.draw(); 

  glutSwapBuffers();
  glutPostRedisplay ();
}


void state::menuHandler(int i) { 
  switch (i) { 
  case 0: startGame(); break;
  case 1: pauseGame(); break;
  case 2: newGame(); break;
  }
}

void state::startGame() {
  gameStarted = true;
}

void state::pauseGame() { 
  gameStarted = false; 
}

void state::newGame() { 
  gameStarted = false; 
  init(); 
}
