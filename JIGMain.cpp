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
#elif _WIN32
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#define KB_MOST_SIGNIFICANT_BIT 0x8000
	#include <windows.h>
	#pragma comment(lib,"user32.lib")
#endif

#include "KFAData.h"
#include "JIGMain.h"
#include "KFAGeometry.h"
#include "JIGRect.h"
#include "JIGArcSlice.h"

std::vector<std::unique_ptr<JIG::Shape>>global_LevelShapes;
#if __APPLE__
void HandleKeypresses(void)
{
    static bool shouldChangeColor = NO;
    int horizVelocity = 0, vertVelocity = 0, rotation = 0;
    
    if (pressedKeys[kVK_ANSI_W]) {
        vertVelocity += 10;
    }
    if (pressedKeys[kVK_ANSI_A]) {
        horizVelocity -= 10;
    }
    if (pressedKeys[kVK_ANSI_S]) {
        vertVelocity -= 10;
    }
    if (pressedKeys[kVK_ANSI_D]) {
        horizVelocity += 10;
    }
    if (pressedKeys[kVK_ANSI_C]) {
        shouldChangeColor = !shouldChangeColor;
    }
    if (pressedKeys[kVK_ANSI_Z]) {
        rotation -= 5;
    }
    if (pressedKeys[kVK_ANSI_X]) {
        rotation += 5;
    }

    
    global_LevelShapes[2]->updateGeometry(horizVelocity, vertVelocity, rotation);
    
    if (pressedKeys[kVK_ANSI_I]) {
        OGL_AdjustCamera((float[]){KFA_ZOOM_SPEED, KFA_ZOOM_SPEED, KFA_ZOOM_SPEED}, KFA_CAMERA_ZOOM);
    }
    if (pressedKeys[kVK_ANSI_K]) {
        OGL_AdjustCamera((float[]){-KFA_ZOOM_SPEED, -KFA_ZOOM_SPEED, -KFA_ZOOM_SPEED}, KFA_CAMERA_ZOOM);
    }
}
#elif _WIN32

void HandleKeypresses(void)
{
	int horizVelocity = 0, vertVelocity = 0, rotation = 0;

	if (pressedKeys['W']) {
		vertVelocity += 10;
	}
	if (pressedKeys['A']) {
		horizVelocity -= 10;
	}
	if (pressedKeys['S']) {
		vertVelocity -= 10;
	}
	if (pressedKeys['D']) {
		horizVelocity += 10;
	}
	if (pressedKeys[',']) {
		rotation -= 5;
	}
	if (pressedKeys['.']) {
		rotation += 5;
	}

	global_LevelShapes[0]->updateGeometry(horizVelocity, vertVelocity, rotation);
}

#endif

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
#if _WIN32
	OGL_InitWGL();
#endif
    glInit();
    
    InitGeometry();
    jiggyInitTestLevel();
}

void jiggyRenderFrame(void)
{
#if __APPLE__
    HandleKeypresses();
#endif
    OGL_ApplyCameraTransformations();
    OGL_UpdateVertexArrays();
}

void jiggyInitTestLevel()
{
    global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(0, 0, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(1.0f, 1.0f, 1.0f, 1.0f))));
	global_LevelShapes[0]->submitForRender();
    
    global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(100, 100, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(0.8f, 1.0f, 1.0f, 1.0f))));
    global_LevelShapes[1]->submitForRender();
    
    global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(-100, 100, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(0.8f, 0.7f, 1.0f, 1.0f))));
    global_LevelShapes[2]->submitForRender();
    
    global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(0, 300, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(0.3f, 1.0f, 0.6f, 1.0f))));
    global_LevelShapes[3]->submitForRender();
    
    global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(0, 200, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(0.4f, 0.5f, 0.3f, 1.0f))));
    global_LevelShapes[4]->submitForRender();
    
    global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(0, 100, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(0.1f, 0.8f, 0.7f, 1.0f))));
    global_LevelShapes[5]->submitForRender();
    
    //std::unique_ptr<JIG::ArcSlice> aPtr = std::make_unique<JIG::ArcSlice>(JIG::ArcSlice(JIGMakePoint(0, 0, 200), 40.0f, 50.0f, 0.0f, JIGMakeColor(0.0f, 0.0f, 0.0f, 1.0f), -1));
//    global_LevelShapes.push_back(std::make_unique<JIG::Shape>(JIG::ArcSlice(JIGMakePoint(0, 0, 200), 200.0f, 360.0f, 0.0f, JIGMakeColor(1.0f, 0.85f, 0.35f, 1.0f))));
    //global_LevelShapes[0]->submitForRender();
}

void jiggyLevelUpdate(void)
{
    
}
