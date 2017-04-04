//
//  JIGMain.h
//  Jiggy!
//
//  Created by Collin Lasley on 4/4/17.
//
//

#if __APPLE__
    extern BOOL pressedKeys[128];
#endif

void HandleKeypresses(void);

void glInit(void);

void jiggyInit(void);

void jiggyRenderFrame(void);
