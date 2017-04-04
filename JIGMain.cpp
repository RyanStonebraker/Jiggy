//
//  JIGMain.cpp
//  Jiggy!
//
//  Created by Collin Lasley on 4/4/17.
//
//

#if __APPLE__
    #include <Carbon/Carbon.h>
    #include <OpenGL/OpenGL.h>
    #include <OpenGL/gl.h>
#endif

#include "KFAData.h"
#include "JIGMain.h"
#include "KFAGeometry.h"

void HandleKeypresses(void)
{
#if __APPLE__
    static bool shouldChangeColor = NO;
    int horzVelocity = 0, vertVelocity = 0, rotation = 0;
    
    if (pressedKeys[kVK_ANSI_W]) {
        vertVelocity += 10;
    }
    if (pressedKeys[kVK_ANSI_A]) {
        horzVelocity -= 10;
    }
    if (pressedKeys[kVK_ANSI_S]) {
        vertVelocity -= 10;
    }
    if (pressedKeys[kVK_ANSI_D]) {
        horzVelocity += 10;
    }
    if (pressedKeys[kVK_ANSI_C]) {
        shouldChangeColor = !shouldChangeColor;
    }
    if (pressedKeys[kVK_ANSI_Comma]) {
        rotation -= 5;
    }
    if (pressedKeys[kVK_ANSI_Period]) {
        rotation += 5;
    }
    
    UpdateGeometry(shouldChangeColor, horzVelocity, vertVelocity, (float)rotation);
    
    if (pressedKeys[kVK_ANSI_I]) {
        OGL_AdjustCamera((float[]){KFA_ZOOM_SPEED, KFA_ZOOM_SPEED, KFA_ZOOM_SPEED}, KFA_CAMERA_ZOOM);
    }
    if (pressedKeys[kVK_ANSI_K]) {
        OGL_AdjustCamera((float[]){-KFA_ZOOM_SPEED, -KFA_ZOOM_SPEED, -KFA_ZOOM_SPEED}, KFA_CAMERA_ZOOM);
    }
#elif _WIN32
    
#endif
}

void glInit(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    OGL_SetOrthographicMatrix(COORD_GL_LOWERBOUND_X, COORD_GL_UPPERBOUND_X, COORD_GL_UPPERBOUND_Y, COORD_GL_LOWERBOUND_Y, COORD_GL_LOWERBOUND_Z, COORD_GL_UPPERBOUND_Z);
    
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE); glEnable(GL_COLOR_MATERIAL);
    
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    OGL_InitVertexArrays();
}

void jiggyInit(void)
{
    glInit();
    
    InitGeometry();
}

void jiggyRenderFrame(void)
{
    HandleKeypresses();
    OGL_ApplyCameraTransformations();
    OGL_UpdateVertexArrays();
}
