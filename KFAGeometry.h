//
//  KFAGeometry.h
//  GeometricAnimator
//
//  Created by Collin Lasley on 3/8/17.
//  Copyright © 2017 Collin Lasley. All rights reserved.
//

#ifndef KFA_GEOMETRY_H_INCLUDED
#define KFA_GEOMETRY_H_INCLUDED

#include "KFAGLSupport.h"
#if __APPLE__
    #include <OpenGL/OpenGL.h>
#elif _WIN32

#endif

void InitGeometry(void);

void UpdateGeometry(bool switchColors, int horizontalVelocity, int verticalVelocity, float rotation);

void SubmitRectangleForRender(KFAGeometryRectangle *theRect, signed int vaID);

KFAGeometryRectangle* CreateNewRectangle(KFAPoint startPoint, float width, float height, float rotationAngle, KFAColorRGBA color);

KFAPoint JIGMakePoint(signed int x, signed int y, signed int z);

KFAColorRGBA JIGMakeColor(float r, float g, float b, float a);

size_t GeometricTypeToDataBlock(void *input, void **output, KFAGeometryType type);

#endif
