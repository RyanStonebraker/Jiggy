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

#if __APPLE__
	void HandleKeypresses(void);
#elif _WIN32
	void HandleKeypresses(char c);
#endif

void glInit(void);

void jiggyInit(void);

void jiggyRenderFrame(void);
