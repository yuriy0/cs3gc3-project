
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

  float m = 1;
  xPos += m * xVel;
  yPos += m * yVel;


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


  // Reflection test
  /*
  vec2 l0(-0.4, 0);
  vec2 l1( 0.4, 0);

  vec2 refl = p1.reflectedIn(l0, l1); 

  drawLineSegment(l0, l1);
  drawLineSegment(refl, vec2(0,0));
  drawLineSegment(p1, vec2(0,0));
  */

  // Reflection test 2
  vec2 l0(p1.x, p1.y);
  vec2 l1(-p1.x, -p1.y);
  vec2 q(0.2, 0.3);

  vec2 refl = q.reflectedIn(l0, l1); 

  drawLineSegment(l0, l1);
  drawLineSegment(refl, vec2(0,0));
  drawLineSegment(q, vec2(0,0));
  
  

  // glBegin(GL_LINES);
  
  // glVertex3f(p0.x, p0.y, 0);
  // glVertex3f(p1.x, p1.y, 0);

  // glVertex3f(p0.x, p0.y, 0);
  // glVertex3f(c.x, c.y, 0);

  // glVertex3f(p0.x, p0.y - 0.01, 0);
  // glVertex3f(mv.x, mv.y - 0.01, 0);

  // glEnd();


  // vec2 c(0.4, 0);
  // vec2 p0(0, 0); 
  // vec2 mv_ (p1.x, 0); 

  // float q = dot(c, p1) / p1.magnitude2(); 
  // vec2 mv = c.scale(1/q);

// vec2 projectionOn (vec2 b, vec2 a) { 
//   float q = dot(a,b) / a.magnitude2();
//   return a.scale(q); 
// }

  // vec2 mv = projectionOn(p1, vec2(0.5, 0)); 
  
  // // printf ("actual = %f , attempted = %f \n", mv_.x, mv.x); 


  // vec2 q0(0.5, 0);
  // vec2 q1(0.3, 0.2);
  // vec2 mv = projectionOn(q0, q1); 
  



  // vec2 c(xPos,yPos);

  // for (wall* w : ws) { 
  //   w->draw(); 
  // }

  // int i = 0;
  // for (wall* w : ws) { 
  //   vec2 o;

  //   bool b = w->collision(c, r, o);

  //   printf ("\n %d: ", i); 
      
  //   if (b) {
  //     vec2 vel(xVel, yVel);
  //     vel = vel.reflect(w->p0, w->p1);
  //     xVel = vel.x;
  //     yVel = vel.y;
  //     break;
  //   }
  //   i++;
  // }
  
  // drawPaddle (c, r); 

  // glutSolidTeapot(1); 

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




