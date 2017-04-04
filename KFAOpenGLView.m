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
#import <Carbon/Carbon.h>
#import <CoreFoundation/CoreFoundation.h>
#include <math.h>

#import "KFAOpenGLView.h"
#include "KFAData.h"
#include "KFAGLSupport.h"
#include "KFAGeometry.h"
#include "JIGMain.h"

BOOL pressedKeys[128];

#pragma mark Objective-C Implementation
@implementation KFAOpenGLView

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
    
    jiggyInit();
    
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
    CVReturn result = [(KFAOpenGLView *)displayLinkContext getFrameForTime:outputTime];
    
    return result;
}

- (CVReturn)getFrameForTime:(const CVTimeStamp *)outputTime
{
    @autoreleasepool {
        [[self openGLContext] makeCurrentContext];
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        jiggyRenderFrame();
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
