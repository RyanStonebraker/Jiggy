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
#include <OpenGL/OpenGL.h>

void InitGeometry(void);

void UpdateGeometry(BOOL switchColors, int horizontalVelocity, int verticalVelocity, float rotation);

void SubmitRectangleForRender(KFAGeometryRectangle *theRect, signed int vaID);

KFAGeometryRectangularPrism* CreateNewRectangularPrism(KFAPoint startPoint, float length, float *angle, KFAColorRGBA color, float width, float height);

KFAGeometryRectangle* CreateNewRectangle(KFAPoint startPoint, float width, float height, float rotationAngle, KFAColorRGBA color);

size_t GeometricTypeToDataBlock(void *input, void **output, KFAGeometryType type);

#endif
