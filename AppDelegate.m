//
//  AppDelegate.m
//  GeometricAnimator
//
//  Created by Collin Lasley on 3/5/17.
//  Copyright © 2017 Collin Lasley. All rights reserved.
//

#import "AppDelegate.h"
#import "KFAOpenGLView.h"

@interface AppDelegate ()

@property (retain) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
    glWindow = [[NSWindow alloc] initWithContentRect:NSMakeRect(100, 100, 640, 480) styleMask:NSTitledWindowMask | NSMiniaturizableWindowMask | NSClosableWindowMask backing:NSBackingStoreBuffered defer:YES screen:[NSScreen mainScreen]];
    
    KFAOpenGLView *glView = [[KFAOpenGLView alloc] initWithFrame:[glWindow contentRectForFrameRect:[glWindow frame]]];
    [glWindow setTitle:@"Render Preview"];
    [glWindow setContentView:glView];
    [glWindow makeFirstResponder:glView];
    [glWindow setOpaque:YES];
    [glWindow makeKeyAndOrderFront:nil];
    [glView release];
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


@end
