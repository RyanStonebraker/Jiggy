//
//  KFAOpenGLView.m
//  GeometricAnimator
//
//  Created by Collin Lasley on 3/5/17.
//  Copyright (c) 2017 Collin Lasley. All rights reserved.
//

#import <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#import <Carbon/Carbon.h>
#import <CoreFoundation/CoreFoundation.h>
#include <math.h>

#import "KFAOpenGLView.h"
#include "KFAData.h"
#include "KFAGLSupport.h"
#include "KFAGeometry.h"

BOOL pressedKeys[128];

void HandleKeypresses(void)
{
    static BOOL shouldChangeColor = NO;
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
}

#pragma mark Objective-C Implementation
@implementation CSPOpenGLView

- (id)init
{
    return [self initWithFrame:NSMakeRect(100, 100, 640, 480)];
}

- (id)initWithFrame:(NSRect)frameRect;
{
    NSOpenGLPixelFormatAttribute attribs[] = {kCGLPFAAccelerated, kCGLPFADoubleBuffer, kCGLPFANoRecovery, kCGLPFADepthSize, 32, kCGLPFAColorSize, 24, 0};
    NSOpenGLPixelFormat *pf = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
    if (!pf) {
        [[NSException exceptionWithName:@"Pixel Format Failed Exception" reason:@"Failed to create OpenGL Pixel Format with requested attributes!" userInfo:nil] raise];
    }
    
    self = [super initWithFrame:frameRect pixelFormat:pf];
    if (self) {
        
    }
    [pf release];
    return self;
}

- (void)prepareOpenGL
{
    [super prepareOpenGL];
    [[self openGLContext] makeCurrentContext];
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //OGL_SetPerspective(65.0f, [self frame], COORD_GL_LOWERBOUND_Z, COORD_GL_UPPERBOUND_Z);
    OGL_SetOrthographicMatrix(COORD_GL_LOWERBOUND_X, COORD_GL_UPPERBOUND_X, COORD_GL_UPPERBOUND_Y, COORD_GL_LOWERBOUND_Y, COORD_GL_LOWERBOUND_Z, COORD_GL_UPPERBOUND_Z);
    
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE); glEnable(GL_COLOR_MATERIAL);
    
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //OGL_TrainCameraToPosition((KFAPoint){20, 20, -10}, (KFAPoint){0, 0, 0});
    
    OGL_InitVertexArrays();
    InitGeometry();
    
    //set up the displaylink
    GLint swapInt = 1;
    CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat] CGLPixelFormatObj];
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
    CVDisplayLinkSetOutputCallback(displayLink, &DisplayLinkCallback, self);
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
    CVDisplayLinkRetain(displayLink);
    CVDisplayLinkStart(displayLink);
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect:dirtyRect];
}

static CVReturn DisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext)
{
    CVReturn result = [(CSPOpenGLView *)displayLinkContext getFrameForTime:outputTime];
    
    return result;
}

- (CVReturn)getFrameForTime:(const CVTimeStamp *)outputTime
{
    @autoreleasepool {
        [[self openGLContext] makeCurrentContext];
        HandleKeypresses();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        OGL_ApplyCameraTransformations();
        OGL_UpdateVertexArrays();
        [[self openGLContext] flushBuffer];
        glPopMatrix();
    }
    return kCVReturnSuccess;
}

- (void)keyDown:(NSEvent *)theEvent
{
    unsigned short int keyCode = [theEvent keyCode];
    if (keyCode < 128)
        pressedKeys[keyCode] = YES;
}

- (void)keyUp:(NSEvent *)theEvent
{
    unsigned short int keyCode = [theEvent keyCode];
    if (keyCode < 128)
        pressedKeys[keyCode] = NO;
}

- (void)dealloc
{
    CVDisplayLinkRelease(displayLink);
    [super dealloc];
}

@end
