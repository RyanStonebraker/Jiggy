//
//  KFAOpenGLView.h
//  GeometricAnimator
//
//  Created by Collin Lasley on 3/5/17.
//  Copyright (c) 2017 Collin Lasley. All rights reserved.
//

#import <Cocoa/Cocoa.h>

extern BOOL pressedKeys[128];

void DrawGeometry(NSRect windowFrame);

void HandleKeypresses(void);

static CVReturn DisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext);

@interface CSPOpenGLView : NSOpenGLView
{
    CVDisplayLinkRef displayLink;
}

- (id)init;

- (id)initWithFrame:(NSRect)frameRect;

- (void)prepareOpenGL;

- (BOOL)acceptsFirstResponder;

- (CVReturn)getFrameForTime:(const CVTimeStamp *)outputTime;

- (void)keyDown:(NSEvent *)theEvent;

- (void)keyUp:(NSEvent *)theEvent;

@end
