
#include "utils.h"
#include <stdio.h> 
#include <time.h>
#include <stdlib.h>
#include "wall.h"
#include "math.h"
#include "drawing.h"

#include <GL/gl.h> 
#include <GL/glu.h> 
#include <GL/glut.h> 


float xPos, yPos; 
float xVel, yVel; 
float r = 0.05; 

wall * ws[6]; 


vec2 p1(0, 0); 

void keyboard (unsigned char a, int b, int c) { 
  p1.x = ((float)(b - 300))/300;
  p1.y = -((float)(c - 300))/300;
}


void specialKey (int key, int b, int c) {  
  switch(key) {
  case GLUT_KEY_UP:    
    yVel += 0.001;
    break;
  case GLUT_KEY_DOWN:  
    yVel -= 0.001;
    break;
  case GLUT_KEY_LEFT:  
    xVel -= 0.001;
    break;
  case GLUT_KEY_RIGHT: 
    xVel += 0.001; 
    break;
  default:
    return; 
  }
}


void display() { 
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

  // vector2f c(0.4, 0);
  // vector2f p0(0,0);
  // vector2f vec(p1.x, p1.y); 

  // vector2f mv = vec.projected(c); 


  // Projection test 
  /*
  vec2 c(0.4, 0);
  vec2 p0(0,0);
  vec2 vec(p1.x, p1.y); 

  vec2 mv = vec.projectedOn(c); 

  drawLineSegment(p0, c);
  drawLineSegment(p0, vec); 
  drawLineSegment(vec2(0,-0.01) , mv - vec2(0, 0.01)); 
  */


  float m = 1;
  xPos += m * xVel;
  yPos += m * yVel;

  vec2 c(xPos,yPos);

  for (wall * w : ws) { w->draw(); }

  for (int i = 0; i < 6; i++) { 

    vec2 o;

    wall w(ws[i]->p1, ws[i]->p0); 
    // wall w(ws[i]->p0, ws[i]->p1); 

    bool b = w.collision(c, r, o);

    if (b) {
      printf ("Collision. %f %f \n", xVel , yVel);
      
      xPos -= m * xVel;
      yPos -= m * yVel;

      vec2 vel(xVel, yVel);
      vel = vel.reflectedIn(w.p0, w.p1);
      xVel = vel.x;
      yVel = vel.y;

      xPos += m * xVel;
      yPos += m * yVel;
      break; 
    } 
  }

  drawPaddle (c, r); 


  glutSwapBuffers();
  glutPostRedisplay ();
}



int main(int argc, char** argv) {

  float m = 0.8; 
  for (int i = 0; i < 6; i++) { 
    float a = 2*PI*i/6;
    float b = 2*PI*(i+1)/6;
    
    ws[i] = new wall(m*cosf(a), 
		     m*sinf(a), 
		     m*cosf(b), 
		     m*sinf(b) 
		     );
  }

  // getchar();

  // OpenGL/glut setup
  glutInit(&argc, argv);		
  glutInitDisplayMode(GLUT_ALPHA | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_DEPTH);

  glutInitWindowSize(600, 600);
  glutInitWindowPosition(50, 50);
  
  glutCreateWindow("final project - Yuriy Toporovskyy, Mostapha Mohamed");      
  // glClearColor(0.1, 0.3, 0.3,0.0);

  // glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);  
  // glEnable(GL_COLOR_MATERIAL);

  // Set up all callback functions.
  // glutIdleFunc          ([] ()                              { st.step();                  });
  glutKeyboardFunc      (keyboard);
  glutDisplayFunc (display); 
  glutSpecialFunc (specialKey);

  // glutMotionFunc        ([] (int a, int b)                  { st.mouseMoved(a,b);         }); 
  // glutDisplayFunc       ([] ()                              { st.display();               });
  // glutPassiveMotionFunc ([] (int a, int b)                  { st.passiveMouseMoved(a,b);  }); 
  // glutReshapeFunc       ([] (int a, int b)                  { st.reshape(a,b);            });
  // glutMouseFunc         ([] (int a, int b, int c, int d)    { st.mousePressed(a,b,c,d);   });

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




