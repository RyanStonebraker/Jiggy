//
//  JIGMain.cpp
//  Jiggy!
//
//  Created by Collin Lasley on 4/4/17.
//
// 950*2 width, 700*2 height

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
#include <stdlib.h>
#include <iostream>
#pragma comment(lib,"user32.lib")
#endif

#include "KFAData.h"
#include "JIGMain.h"
#include "KFAGeometry.h"
#include "JIGRect.h"
#include "JIGArcSlice.h"
#include "JIGCollisionDetector.h"
#include "levelLoader.h"
#include <random>
#include <string>

std::vector<std::unique_ptr<JIG::Shape>>global_LevelShapes;
std::vector<std::unique_ptr<JIG::Rectangle>>gameInfo;

std::string levelLocation = "/Users/Ryan/Documents/College-UAF/Classwork/CS202/jiggyProject/level1.txt";

JIG::LoadLevel testLevel(levelLocation); // location of level1.txt

int iterator = 0;
bool first = true;

/***************************************************/
//DEMO CODE - DON'T DELETE ON FINAL RELEASE
/***************************************************/
//start
std::vector<KFAPoint> demo;
//end
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
    if (pressedKeys[kVK_ANSI_C]) {
        rotation -= 5;
    }
    if (pressedKeys[kVK_ANSI_V]) {
        rotation += 5;
    }
    
    
    global_LevelShapes[iterator]->updateGeometry(horizVelocity, vertVelocity, rotation);
    
    if (pressedKeys[kVK_ANSI_I]) {
        OGL_AdjustCamera((float[]) { KFA_ZOOM_SPEED, KFA_ZOOM_SPEED, KFA_ZOOM_SPEED }, KFA_CAMERA_ZOOM);
    }
    if (pressedKeys[kVK_ANSI_K]) {
        OGL_AdjustCamera((float[]) { -KFA_ZOOM_SPEED, -KFA_ZOOM_SPEED, -KFA_ZOOM_SPEED }, KFA_CAMERA_ZOOM);
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
    if (pressedKeys['C']) {
        rotation -= 5;
    }
    if (pressedKeys['V']) {
        rotation += 5;
    }
    
    global_LevelShapes[iterator]->updateGeometry(horizVelocity, vertVelocity, rotation);
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
    static bool complete = false;
    static unsigned long long finishTime = -1;
    static int breakShape = 0;
    static unsigned long long frameCount = 0;
    ++frameCount;
    
    static std::random_device rd;
    /*** Start check if shape position has been achieved ***/
    
    //distance tracker
    
    /* Tristan is working on this */
    /*
     std::cout << "(" << demo[iterator].x - global_LevelShapes[iterator]->getxPos() << ", ";
     std::cout << demo[iterator].x - global_LevelShapes[iterator]->getyPos() << ")";
     //std::system("clear");
     */
    
    //range of accepted value
    
    
    if (breakShape < 250 && breakShape > 100)
    {
    
    for (int i = 0; i < global_LevelShapes.size(); i++) {
        
        std::mt19937 gen(rd());
        std::uniform_int_distribution <int> verDis(-30 + breakShape%20, 30 - breakShape%20);
        std::uniform_int_distribution <int> horDis(-40 + breakShape%30, 40 - breakShape%30);
        std::uniform_int_distribution <int> rotDis(-5, 5);
        
        int randVal = horDis(gen);
        int horVel = randVal;
        
        randVal = verDis(gen);
        int verVel = randVal;
        
        randVal = rotDis(gen);
        int rot = randVal;
        
        global_LevelShapes[i]->updateGeometry(horVel, verVel, rot);
        
    }
        ++breakShape;
    }
    if (breakShape <= 100)
        ++breakShape;
    
    int buffer = 50; // change this to adjust the pickyness of position
    
    if (breakShape >= 250) {
        std::cout << "xPos: " << global_LevelShapes[iterator]->getxPos() << "yPos: " << global_LevelShapes[iterator]->getyPos() << std::endl;
    
    if ((global_LevelShapes[iterator]->getxPos() <= demo[iterator].x + buffer && global_LevelShapes[iterator]->getxPos() >= demo[iterator].x - buffer) &&
        (global_LevelShapes[iterator]->getyPos() <= demo[iterator].y + buffer && global_LevelShapes[iterator]->getyPos() >= demo[iterator].y - buffer))
    {
        global_LevelShapes[iterator]->setxPos(demo[iterator].x);
        global_LevelShapes[iterator]->setyPos(demo[iterator].y);
        global_LevelShapes[iterator]->setRotPos(0);
        global_LevelShapes[iterator]->submitForRender();
        
        
        if (iterator < demo.size() - 1) {
            iterator++;
        }
        
        else {
            if (!complete)
            {
                for (unsigned int i = 0; i < global_LevelShapes.size(); i++) {
//                OGL_StartColorTransition(global_LevelShapes[i]->vertexArrayID, JIGMakeColor(0.0f, 0.0f, 0.85f, 1.0));
                testLevel.color(i) = JIGMakeColor(0.0f, 0.0f, 0.85f, 1.0);
                }
                testLevel.sendToGlobal();
                testLevel.submitGlobal();
                finishTime = frameCount;
                complete = true;
            }
        }
    }
        
        gameInfo[0]->setWidth(gameInfo[0]->getWidth() - frameCount/1000.0);
        gameInfo[0]->submitForRender();
        
        if (gameInfo[0]->getWidth() <= 1 && !complete)
        {
//            for (unsigned int i = 0; i < global_LevelShapes.size(); i++) {
//                KFAPoint tmpPt {global_LevelShapes[i]->getxPos(), global_LevelShapes[i]->getyPos(), 0};
//                testLevel.location(i) = tmpPt;
//                testLevel.color(i) = JIGMakeColor(0.85f, 0.0f, 0.0f, 1.0);
//            }
//            
//            testLevel.sendToGlobal();
//            testLevel.submitGlobal();
//
            gameInfo.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(0, 0, 0), 2*1900.0f, 2*1400.0f, 0.0f, JIGMakeColor(0.85f, 0.0f, 0.0f, 1.0f))));
            gameInfo[1]->submitForRender();
            complete = true;
        }
        
    }
    
    if (complete && frameCount > finishTime + 300) {
        exit(1);
    }
    /*** End check if shape position has been achieved ***/
    
    OGL_ApplyCameraTransformations();
    OGL_UpdateVertexArrays();
}

void jiggyInitTestLevel()
{
    
//    JIG::LoadLevel testLevel("/Users/Ryan/Documents/College-UAF/Classwork/CS202/jiggyProject/level1.txt"); // location of level1.txt
    
//    if (levelLocation == "/Users/Ryan/Documents/College-UAF/Classwork/CS202/jiggyProject/smileFace.txt") {
//            global_LevelShapes.push_back(std::make_unique<JIG::ArcSlice>(JIG::ArcSlice(JIGMakePoint(-350, 350, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(0.2f, 1.0f, 1.0f, 1.0f))));
//            global_LevelShapes.push_back(std::make_unique<JIG::ArcSlice>(JIG::ArcSlice(JIGMakePoint(350, 350, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(0.2f, 1.0f, 1.0f, 1.0f))));
//    global_LevelShapes[0]->submitForRender();
//    global_LevelShapes[1]->submitForRender();
//    }

    for (unsigned i =0; i < testLevel.size(); ++i)
    {
        demo.push_back(testLevel.location(i));
    }
    
    
    testLevel.sendToGlobal();
    testLevel.submitGlobal();
    
    
    gameInfo.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(0, 675, 0), 1900.0f, 100.0f, 0.0f, JIGMakeColor(0.2f, 0.8f, 0.3f, 1.0f))));
    gameInfo[0]->submitForRender();
    
    
    
    
    
//    global_LevelShapes.push_back(std::make_unique<JIG::ArcSlice>(JIG::ArcSlice(JIGMakePoint(0, 0, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(1.0f, 1.0f, 1.0f, 1.0f))));
//    global_LevelShapes.push_back(std::make_unique<JIG::ArcSlice>(JIG::ArcSlice(JIGMakePoint(0, 0, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(1.0f, 1.0f, 1.0f, 1.0f))));
//    
//    testLevel.submitGlobal();
    
//    global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(100, 100, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(0.8f, 1.0f, 1.0f, 1.0f))));
//    global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(-100, 100, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(0.8f, 0.7f, 1.0f, 1.0f))));
//    global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(0, 300, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(0.3f, 1.0f, 0.6f, 1.0f))));
//    global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(0, 200, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(0.4f, 0.5f, 0.3f, 1.0f))));
//    global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(0, 100, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(0.1f, 0.8f, 0.7f, 1.0f))));
    
    /*Mark Stuff
     global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(-150, 100, 200), 100.0f, 100.0f, 45.0f, JIGMakeColor(0.8f, 0.7f, 1.0f, 1.0f))));
     global_LevelShapes[1]->submitForRender();
     */
    
//    for (unsigned int i = 0; i < global_LevelShapes.size(); i++) {
//        
//        global_LevelShapes[i]->submitForRender();
//        
//    }
    
    //
    //	JIG::CollisionDetector col(global_LevelShapes[0], global_LevelShapes);
    //	if (col.isCollided())
    //	{
    //		global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(0, -200, -200), 100.0f, 100.0f, 0.0f, JIGMakeColor(0.1f, 0.8f, 0.7f, 1.0f))));
    //		global_LevelShapes[5]->submitForRender();
    //	}
    
    
    
    
    //std::unique_ptr<JIG::ArcSlice> aPtr = std::make_unique<JIG::ArcSlice>(JIG::ArcSlice(JIGMakePoint(0, 0, 200), 40.0f, 50.0f, 0.0f, JIGMakeColor(0.0f, 0.0f, 0.0f, 1.0f), -1));
    //    global_LevelShapes.push_back(std::make_unique<JIG::Shape>(JIG::ArcSlice(JIGMakePoint(0, 0, 200), 200.0f, 360.0f, 0.0f, JIGMakeColor(1.0f, 0.85f, 0.35f, 1.0f))));
    //global_LevelShapes[0]->submitForRender();
}

void jiggyLevelUpdate(void)
{
    
}
