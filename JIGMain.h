//
//  JIGMain.h
//  Jiggy!
//
//  Created by Collin Lasley on 4/4/17.
//
//

#if __APPLE__
    extern bool pressedKeys[128];
#elif _WIN32
	extern bool pressedKeys[0x100];
#endif

#if __APPLE__
	void HandleKeypresses(void);
#elif _WIN32
	void HandleKeypresses(void);
#endif

#include <vector>
#include <memory>
#include "JIGShape.h"

extern std::vector<std::unique_ptr<JIG::Shape>>global_LevelShapes;

void glInit(void);

void jiggyInit(void);

void jiggyInitTestLevel();

void jiggyRenderFrame(void);

void jiggyLevelUpdate(void);

