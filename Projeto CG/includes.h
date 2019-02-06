
#define GL_SILENCE_DEPRECATION = true;

#ifdef __APPLE__
    #include "TargetConditionals.h"
    #ifdef TARGET_OS_MAC
        #include <OpenGL/gl.h>
        #include <OpenGl/glu.h>
        #include <GLUT/glut.h>
    #endif
 
#elif _WIN32
    #include <windows.h>
	#include <GL/glut.h>
	#include <GL/glu.h>

#elif __linux__
    #include <GL/freeglut.h>
    #include <GL/gl.h>
#endif