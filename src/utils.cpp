#include "utils.h"
#include "math.h"
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std; 

float randF () {
  float a = rand();
  float b = RAND_MAX;
  return a/b; 
}

float randF (float a, float b) {
  if (b<=a) return a;
  else return (randF() * (b-a) + a) ;  
}

int randI (int a, int b) {
  if (b<=a) return a;
  else return (rand() % (b-a) + a) ;  
}

int min (int a, int b) { if (a < b) { return a; } else { return b; } }
int max (int a, int b) { if (a > b) { return a; } else { return b; } }


int mod (int a, int b) { 
  int r = a % b;
  if (r < 0) r += b;
  return r;
}

// load a 256x256 RGB .RAW file as a texture
// Source: http://www.nullterminator.net/gltexture.html
GLuint loadTextureRAW( const char * filename, bool wrap )
{
    GLuint texture;
    int width, height;
    BYTE * data;
    FILE * file;

    // open texture data
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;

    // allocate buffer
    width = 256;
    height = 256;
    data = new BYTE [width * height * 3 ];

    // read texture data
    fread( data, width * height * 3, 1, file );
    fclose( file );

    // allocate a texture name
    glGenTextures( 1, &texture );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     wrap ? GL_REPEAT : GL_CLAMP );

    // build our texture mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                       GL_RGB, GL_UNSIGNED_BYTE, data );

    // free buffer
    delete data; 

    return texture;
}
