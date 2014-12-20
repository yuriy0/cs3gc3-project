
#include "utils.h"
#include <stdio.h> 
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "state.h"

using namespace std;

state st;

int main(int argc, char** argv) {

  // Read and print the readme file.
  FILE *file = fopen(README, "r");

  if (file) { 
    while(1) {
      int c = fgetc(file);
      if (feof(file)) break;
      printf("%c", c);
    }
  }

  // OpenGL/glut setup
  glutInit(&argc, argv);		
  glutInitDisplayMode(GLUT_ALPHA | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_DEPTH );

  glutInitWindowSize(800, 800);
  glutInitWindowPosition(50, 50);
  
  glutCreateWindow("CS3GC3 - Final project - Yuriy Toporovskyy, Mostapha Mohammed");      

  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE); 
  glEnable( GL_TEXTURE_2D );

  st.texture = loadTextureRAW("images/Ice.rgb", true); 


  // Set up all callback functions.
  glutKeyboardFunc      ([] (unsigned char a, int b, int c) { st.keyboard(a,b,c);         });
  glutDisplayFunc       ([] ()                              { st.display();               });
  glutSpecialFunc       ([] (int a, int b, int c)           { st.specialKey(a,b,c);       });
  glutMouseFunc         ([] (int a, int b, int c, int d)    { st.mousePressed(a,b,c,d);   });
  glutMotionFunc        ([] (int a, int b)                  { st.mouseMoved(a,b);         }); 
  glutPassiveMotionFunc ([] (int a, int b)                  { st.passiveMouseMoved(a,b);  }); 
  glutReshapeFunc       ([] (int a, int b)                  { st.reshape(a,b);            }); 
  glutIdleFunc          ([] ()                              { st.step();                  });
  
  
  // New game menu
  int diffMenu = glutCreateMenu ([] (int i) { st.difficulty = i; st.menuHandler(2); });
  glutAddMenuEntry("Easy", 0);
  glutAddMenuEntry("Medium", 1);
  glutAddMenuEntry("Hard", 2);
  
  // Main menu.
  glutCreateMenu ([] (int i) { st.menuHandler(i); });
  glutAddMenuEntry("Start game", 0);
  glutAddMenuEntry("Pause game", 1);
  glutAddSubMenu("New game ... ", diffMenu);

  glutAttachMenu(GLUT_RIGHT_BUTTON);


  glutMainLoop();				
  return(0);
}




