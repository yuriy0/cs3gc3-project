
#include "utils.h"
#include <stdio.h> 
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "state.h"

using namespace std;

state st;

int main(int argc, char** argv) {

  // OpenGL/glut setup
  glutInit(&argc, argv);		
  glutInitDisplayMode(GLUT_ALPHA | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_DEPTH );

  glutInitWindowSize(800, 800);
  glutInitWindowPosition(50, 50);
  
  glutCreateWindow("final project - Yuriy Toporovskyy");      

  glEnable(GL_DEPTH_TEST);  

  // Set up all callback functions.
  glutKeyboardFunc      ([] (unsigned char a, int b, int c) { st.keyboard(a,b,c);         });
  glutDisplayFunc       ([] ()                              { st.display();               });
  glutSpecialFunc       ([] (int a, int b, int c)           { st.specialKey(a,b,c);       });
  glutMouseFunc         ([] (int a, int b, int c, int d)    { st.mousePressed(a,b,c,d);   });
  glutMotionFunc        ([] (int a, int b)                  { st.mouseMoved(a,b);         }); 
  glutPassiveMotionFunc ([] (int a, int b)                  { st.passiveMouseMoved(a,b);  }); 
  glutReshapeFunc       ([] (int a, int b)                  { st.reshape(a,b);            }); 
  glutIdleFunc          ([] ()                              { st.step();                  });
  

  glutMainLoop();				
  return(0);
}




