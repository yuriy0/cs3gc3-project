
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

vector<circle> cs ;
vector<wall> ws;
vector<wall> iws; 
vector<wall> gws; 

circle puck(vec2(0,0), 0.03); 

vec2 p1(0,0); 

bool lmbPressed = false; 

void keyboard (unsigned char a, int b, int c) { 
  // p1.x = ((float)(b - 300))/300;
  // p1.y = -((float)(c - 300))/300;
}


void mouseMoved (int a, int b) {

  float dx = (a - p1.x) / (600);
  float dy = (p1.y - b) / (600);


  if (lmbPressed) {
    cs[0].v.x += 0.05 * dx;
    cs[0].v.y += 0.05 * dy;

  }

  p1.x = a;
  p1.y = b;
}

void passiveMouseMoved (int b, int c) {
  p1.x = b;
  p1.y = c;
}

void mouseFunc (int button, int state, int x, int y) {
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

void specialKey (int key, int b, int c) {  
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

void collideWithWalls (vector<circle> & cs, vector<wall> & ws, float m) { 
  for (int j = 0; j < cs.size(); j++) { 
    for (int i = 0; i < ws.size(); i++) { 
      vec2 o;
      wall w = ws[i];
      bool b = ws[i].collision(cs[j].c, cs[j].r, o);

      if (b) {
  	cs[j].step(-m);

  	vec2 vel(cs[j].v.x, cs[j].v.y);
  	vel = vel.reflectedIn(ws[i].p0, ws[i].p1);
  	cs[j].v = vel;

  	cs[j].step(m);
  	break; 
      } 
    }
  }
}

void display() { 

  float m = 1;

  glClearStencil(0);

  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  glEnable(GL_STENCIL_TEST);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

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

  glStencilFunc(GL_ALWAYS, 1, -1);
  cs[0].draw(); 
  cs[0].step(m);
  glStencilFunc(GL_ALWAYS, 0, -1);

  for (int i = 1; i < cs.size(); i++) {
    cs[i].draw(); 
    cs[i].step(m);
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
  
  // vector<circle> puck_; 
  // puck_.push_back(puck);

  // collideWithWalls(puck_, ws, m);
  

  for (circle & c : cs) { 
    c.v = c.v.scale(0.9); 
  }
  puck.v.scale(0.9); 

  glutSwapBuffers();
  glutPostRedisplay ();
}



int main(int argc, char** argv) {
  wall::genInitial(3, 0.8, 0.05, 0.2, cs, ws, iws, gws); 

  // cs.push_back(circle(vec2(0, 0)), 0.01); 

  // OpenGL/glut setup
  glutInit(&argc, argv);		
  glutInitDisplayMode(GLUT_ALPHA | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_DEPTH | GLUT_STENCIL);

  glutInitWindowSize(600, 600);
  glutInitWindowPosition(50, 50);
  
  glutCreateWindow("final project - Yuriy Toporovskyy, Mostapha Mohamed");      
  // glClearColor(0.1, 0.3, 0.3,0.0);

  // glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_STENCIL_TEST);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
  // glEnable(GL_COLOR_MATERIAL);

  // Set up all callback functions.
  // glutIdleFunc          ([] ()                              { st.step();                  });
  glutKeyboardFunc      (keyboard);
  glutDisplayFunc (display); 
  glutSpecialFunc (specialKey);
  glutMouseFunc (mouseFunc);
  glutMotionFunc (mouseMoved); 
  glutPassiveMotionFunc (passiveMouseMoved); 

  // glutMotionFunc        ([] (int a, int b)                  { st.mouseMoved(a,b);         }); 
  // glutDisplayFunc       ([] ()                              { st.display();               });
  // glutPassiveMotionFunc ([] (int a, int b)                  { st.passiveMouseMoved(a,b);  }); 
  // glutReshapeFunc       ([] (int a, int b)                  { st.reshape(a,b);            });

  // glutSpecialFunc       ([] (int a, int b, int c)           { st.specialKey(a,b,c);       });
  // glutIdleFunc          ([] ()                              { st.step();                  });
  // glutKeyboardFunc      ([] (unsigned char a, int b, int c) { st.keyboard(a,b,c);         });
  // glutMotionFunc        ([] (int a, int b)                  { st.mouseMoved(a,b);         }); 
  // glutDisplayFunc       ([] ()                              { st.display();               });
  // glutPassiveMotionFunc ([] (int a, int b)                  { st.passiveMouseMoved(a,b);  }); 
  // glutReshapeFunc       ([] (int a, int b)                  { st.reshape(a,b);            });
  // glutMouseFunc         ([] (int a, int b, int c, int d)    { st.mousePressed(a,b,c,d);   });
  // glutSpecialFunc       ([] (int a, int b, int c)           { st.specialKey(a,b,c);       });
  
  // // Initialize menus
  // // Menu containing generators.
  // int genMenu = glutCreateMenu 
  //   ([] (int i) { st.newMesh(&TerrainGenerator::generators[i]); });

  // for (int i = 0; i < (int)TerrainGenerator::generators.size(); i++) {
  //   glutAddMenuEntry(TerrainGenerator::generators[i].name.c_str(), i);
  // }

  // // Colour ramp menu
  // int colMenu = glutCreateMenu 
  //   ([] (int i) { st.colourRamp = i; });

  // for (int i = 0; i < (int)ColourRamp::colourRamps.size(); i++) {
  //   glutAddMenuEntry(ColourRamp::colourRamps[i].name.c_str(), i);
  // }

  // // Main menu.
  // glutCreateMenu ([] (int i)  { });
  // glutAddSubMenu("Add to mesh...", genMenu);
  // glutAddSubMenu("Select colour ramp...", colMenu);
  // glutAttachMenu(GLUT_RIGHT_BUTTON);

  // // Second window with heightmap 
  // glutInitWindowPosition(700, 50);

  // int heightMapWindow = glutCreateWindow (argv[0]);
  // glutSetWindowTitle("Heightmap");
  // glutDisplayFunc       ([] ()                              { st.displayHM();               });
  // glutReshapeFunc       ([] (int a, int b)                  { st.reshapeHM (a,b);           });
  // glutMotionFunc        ([] (int a, int b)                  { st.mouseMovedHM(a,b);         }); 
  // glutPassiveMotionFunc ([] (int a, int b)                  { st.passiveMouseMovedHM(a,b);  }); 
  // glutMouseFunc         ([] (int a, int b, int c, int d)    { st.mousePressedHM(a,b,c,d);   });


  glutMainLoop();				
  return(0);
}




